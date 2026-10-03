#include <stdio.h>

int main(int argc, char** argv)
{
  int sick = 0;
  for(int i = 0; i < 10; i++)
    printf("sickness %d\n", i);
  
  if(sick)
    printf("inga\n");
  
  return(0);
}
