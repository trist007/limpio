#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define BUFSIZE 1024*1024

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

int main(int argc, char **argv)
{
  static char buffer[BUFSIZE];
  if (argc == 2)
    open_file(argv[1], buffer);
  
  printf("number of argc: %d\n", argc);
  
  printf("printing buffer %s\n", buffer);
    
  return(0);
}
