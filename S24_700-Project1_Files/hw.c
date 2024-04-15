#include <stdio.h>
#include <stdlib.h>
#include <math.h>

char *str1 = "Hello to Reverse Engineering";
char *str2 = "ctf{Updated_String}";

int main()
{
  int val, r;
  
  printf("String is: %s\n", str1);
  r = 10;
  val = pow(2, r);

  printf("Number is: %d\n", val);
  return 0;
}
