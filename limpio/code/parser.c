#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <ctype.h>
#include <string.h>

#define BUFSIZE 1024*1024
#define MAX_CHAR 256

int
open_file(const char *file, char* buffer)
{
  printf("opening file %s\n", file);
  FILE* fp;
  fopen_s(&fp, file, "r");
  
  if (!fp)
  {
    fprintf(stderr, "ERROR: unable to open file: %s\n", file);
    abort();
  }
  
  fseek(fp, 0, SEEK_END);
  long fileSize = ftell(fp);
  printf("&fileSize = %p\n%ld\n%lx\n", (void*)&fileSize, fileSize, fileSize);
  size_t fileSize_t = (size_t)fileSize;
  printf("&fileSize_t = %p\n%zu\n%zx\n", (void*)&fileSize_t, fileSize_t, fileSize_t);
  
  if (fileSize < 0)
  {
    fprintf(stderr, "ERROR: unable to ftell file\n");
    fclose(fp);
    abort();
  }
  fseek(fp, 0, SEEK_SET);
  
  printf("filesize = %ld\n", fileSize);
  
  if ((size_t)fileSize >= BUFSIZE)
  {
    fprintf(stderr, "ERROR buffer_size too small\n");
    fclose(fp);
    abort();
  }
  
  fread(buffer, 1, (size_t)fileSize, fp);
  buffer[fileSize] = '\0';
  fclose(fp);
  // memcpy(buffer, fp, (size_t)(fileSize));
  
  return(0);
}

void
fix_spacing(char* src, char* dst)
{
  char prev = '\0';
  
  while (*src)
  {
    int boundary = !(isalnum((unsigned char)prev) || prev == '_');
    
    if (boundary && strncmp(src, "for(", 4) == 0)
    {
      memcpy(dst, "for (", 5);
      dst += 5;
      src += 4;
      prev = '(';
    }
    else
    {
      prev = *src;
      *dst++ = *src++;
    }
  }
  
  *dst = '\0';
}

int main(int argc, char **argv)
{
  static char buffer[BUFSIZE];
  
  if (argc == 2)
  {
    open_file(argv[1], buffer);
  }
  else
  {
    fprintf(stderr, "ERROR: need a C file to parse\n");
    exit(1);
  }
  
  char output[MAX_CHAR];
  
  fix_spacing(buffer, output);
  
  printf("---------------OUTPUT--------------\n%s", output);
  
    
  return(0);
}
