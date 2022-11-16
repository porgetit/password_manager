#include <stdio.h>
#include <stdlib.h>

#define NOMBRE_ARCHIVO "./data/data.bin"

void setSitio();
void setUsuario();
void setContenido();
void setToken();
int save(struct password newPassword, const char *);

void crear()
{
   setSitio();
   setUsuario();
   setContenido();
   setToken();

   if (!save(newPassword, NOMBRE_ARCHIVO))
   {
      printf("Error de escritura");
   }
}

void setSitio()
{
   printf("Sitio: ");
   gets(newPassword.sitio);
}

void setUsuario()
{
   printf("Usuario: ");
   gets(newPassword.usuario);
}

void setContenido()
{
   printf("Contenido: ");
   gets(newPassword.contenido);
}

void setToken()
{
   newPassword.token = rand() % 11;
}

int save(struct password newPassword, const char *nombreArchivo)
{
   FILE *F;
   F = fopen(nombreArchivo, "wb");
   if (F == NULL)
   {
      return 0;
   }
   fwrite(&newPassword, sizeof(password), 1, F);
   fflush(F);
   fclose(F);
   return 1;
}

/* Recordar:
=> Implementar las validaciones de tipo y longitud de datos.
*/