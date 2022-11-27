#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

void bar(const char *character, int length)
{
   for (int flag = 0; flag < length; flag++)
   {
      printf(character);
   }
   printf("\n");
}

void boldBar(int length)
{
   bar("#", length);
}

void lightBar(int length)
{
   bar("-", length);
}

int main(void)
{
   bar("g", 10);
   lightBar(10);
   boldBar(10);
}
