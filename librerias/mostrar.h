#include <stdio.h>
#include <stdlib.h>

#define NOMBRE_ARCHIVO "./data/data.bin"

void mostrar(struct password);

void leer()
{
   FILE *F;
   F = fopen(NOMBRE_ARCHIVO, "rb");
   if (F == NULL)
   {
      printf("Error de lectura");
   }
   fread(&newPassword, sizeof(password), 1, F);
   fclose(F);
   mostrar(newPassword);
}

void mostrar(struct password newPassword)
{
   printf("Sitio: %s\n", newPassword.sitio);
   printf("Usuario: %s\n", newPassword.usuario);
   printf("Contraseña: %s\n", newPassword.contenido);
   printf("Token: %d\n", newPassword.token);
}