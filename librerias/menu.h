#include <stdio.h>
#include "crear.h"
#include "mostrar.h"
#include "actualizar.h"
#include "eliminar.h"

void menu()
{
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
         crear();
         break;
      case 2:
         leer();
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