#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

const char *sys_username_recover()
{
   char username[] = "";
   FILE *file;
   file = fopen("./username.txt", w);

   return username;
}

int main(void)
{
   char system_username[] = {sys_username_recover()};
   printf("Nombre de usuario del sistema: %s", system_username);
}

// (char)system("echo %USERNAME%")