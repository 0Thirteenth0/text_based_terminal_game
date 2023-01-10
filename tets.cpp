#include <stdio.h>
#include <stdlib.h>

int main()
{
  printf("\x1b[2J"); // clear screen
  printf("\033[H"); // move cursor home
  printf("1111\n2222\n3333\n4444"); // add some text to screen for reference
  printf("\033[2;2H"); // move cursor to 2,2
  while (1); // keep program running
}