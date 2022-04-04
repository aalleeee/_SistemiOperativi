#include <stdio.h>

int main(int argc, char const *argv[])
{
  int i = 0;
  //printf("%i",argc);
  if(argc >= 2)
  {
    while (argv[1][i]!='\0')
    {
      i++;
    }
    
  }
  printf("Len: %i\n", i);
  return 0;
}
