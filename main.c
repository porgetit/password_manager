#include <locale.h>
#include "./librerias/saludo.h"
#include "./librerias/menu.h"

struct password
{
   char *sitio;
   char *usuario;
   char *contenido;
   int token;
} newPassword;

int main(void)
{
   setlocale(LC_ALL, "");
   // Saludar
   saludo();
   // Menu
   menu();
}
