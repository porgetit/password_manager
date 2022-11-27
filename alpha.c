#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>
#include <windows.h>
#include <string.h>
#define NOMBRE_ARCHIVO "./data/data.bin"
#define Len 1024
#define Wait 1125

typedef struct
{
   int ID;
   char sitio[1024];
   char usuario[256];
   char contenido[1024]; // contraseña
   int token;
   short visibilidad;
} password;

void init_data(password *registros, FILE *data, int *len)
{
   data = fopen(NOMBRE_ARCHIVO, "rb");

   if (data == NULL)
   {
      printf("Error de lectura 1: init_data()\n");
      printf("Creando el archivo...\n");
      Sleep(Wait);
      data = fopen(NOMBRE_ARCHIVO, "wb");
      fflush(data);
      fclose(data);
      init_data(registros, data, len);
   }
   else
   {
      int flag = 0;
      while (!feof(data))
      {
         fread(&registros[flag], sizeof(password), 1, data);
         flag++;
         *len += 1;
      }

      fclose(data);

      if ((sizeof(registros) / sizeof(password)) == 0)
      {
         printf("Error de lectura 2: init_data()\n");
      }

      printf("Registros inicializados con éxito...\n");
      Sleep(Wait);
   }
}

int main(void)
{
   FILE *data;
   password registros[Len];
   int len = 0;

   // Inicializamos el vector de registros
   init_data(registros, data, &len);
}