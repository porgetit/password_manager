#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>
#define NOMBRE_ARCHIVO "./data/data.bin"

typedef struct
{
   char sitio[1024];
   char usuario[256];
   char contenido[1024];
   int token;
   short visibilidad;
} password;

void crear_registro(password *, FILE *);
void escribir_registro(password *, FILE *);

void leer(password *, FILE *);
void imprimir_registro(password *, int);
void actualizar();
void eliminar();

int main(void)
{
   setlocale(LC_ALL, "");
   static password registro[1];
   FILE *file;
   // Menu
   short option = 0;

   do
   {
      printf("Opción 1: Crear una nueva contraseña\n");
      printf("Opción 2: Mostrar un listado de contraseñas\n");
      printf("Opción 3: Actualizar una contraseña\n");
      printf("Opción 4: Eliminar una contraseña\n");
      printf("Opción 5: Salir\n\n");
      printf("Seleccione una opción: ");
      scanf("%d", &option);
      fflush(stdin);

      switch (option)
      {
      case 1:
         crear_registro(registro, file);
         break;
      case 2:
         leer(registro, file);
         break;
      case 3:
         actualizar();
         break;
      case 4:
         eliminar();
         break;
      case 5:
         break;
      }
   } while (option != 5);
}

void crear_registro(password *registro, FILE *file)
{
   srand(time(NULL));

   printf("Crear un nuevo registro\n\n");

   printf("Introduzca los siguientes datos: \n");

   printf("Sitio: ");
   gets(registro[0].sitio);

   printf("Usuario: ");
   gets(registro[0].usuario);

   printf("Contenido: ");
   gets(registro[0].contenido);

   registro[0].token = rand() % 101 + 1;
   registro[0].visibilidad = 1;

   printf("%s\n%s\n%s\n%d\n%d\n", registro[0].sitio, registro[0].usuario, registro[0].contenido, registro[0].token, registro[0].visibilidad); // Agregar funcionalidad de confirmación y corrección

   escribir_registro(registro, file);
}

void escribir_registro(password *registro, FILE *file)
{
   file = fopen(NOMBRE_ARCHIVO, "ab");
   if (file == NULL)
   {
      printf("Error: no se puede acceder al archivo. (cod.ab)");
   }
   else
   {
      fwrite(&registro[0], sizeof(password), 1, file);
      printf("Registro guardado con éxito");
   }
   fflush(file);
   fclose(file);
}

void leer(password *registro, FILE *file)
{
   file = fopen(NOMBRE_ARCHIVO, "rb");
   static password temp[1];
   int flag = 1;

   if (file == NULL)
   {
      printf("Error: no se puede acceder al archivo. (cod.rd)");
   }
   else
   {
      while (fread(&temp[0], sizeof(password), 1, file) > 0)
      {
         fread(&temp[0], sizeof(password), 1, file);
         imprimir_registro(temp, flag);
         flag++;
      }
   }

   fclose(file);
}

void imprimir_registro(password *registro, int flag)
{
   printf("Registro #%d\n", flag); // Añadir numerador
   printf("Sitio: %s\n", registro[0].sitio);
   printf("Usuario: %s\n", registro[0].usuario);
   printf("Contraseña: %s\n", registro[0].contenido);
}

void actualizar()
{
   printf("Actualizar un registro");
}

void eliminar()
{
   printf("Eliminar un registro");
}