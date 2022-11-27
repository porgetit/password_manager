#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>
#include <windows.h>
#include <string.h>
#define NOMBRE_ARCHIVO "./data/data.bin"
#define Len 100
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

/* FUNCIONES ESTÉTICAS */
void bar(const char *, int);
void boldBar(int);
void lightBar(int);
void clear();

/* FUNCIONES DE MANIPULACIÓN DE DATOS EN DISCO */
void init_data(password *, FILE *, int *);
void save_data(password *, FILE *, int);
void delete_data();

/* FUNCIONES DE MANIPULACIÓN DE DATOS EN MEMORIA */
//    Funciones de impresión de datos
void ver_registros_menu(password *, int);
void all_records(password *, int);
void find_record(password *, int);
void filter_records(password *, int);

//    Funciones de creación de datos
void crear_registros_menu(password *, FILE *, int *);
void create_record(password *, FILE *, short, int *);
void rand_strings(char *, int);

//    Funciones de actualización de datos
void actualizar_registros_menu(password *, FILE *);
void update_all_record(password *, FILE *);
void update_gob_record(password *, FILE *);

//    Funciones de eliminación de datos
void eliminar_registros_menu(password *, FILE *);
void erase_record(password *, FILE *);
void delete_record(password *, FILE *);

/* FUNCIONES DE GENERACIÓN DE REPORTES */
void reportes_menu(password *, FILE *);

int main(void)
{
   // Establecemos parámetros globales
   setlocale(LC_ALL, "");
   srand(time(NULL));

   // Inicializamos los punteros, estructuras y variables
   FILE *data;
   password registros[Len];
   int len = 0;

   // Inicializamos el vector de registros
   init_data(registros, data, &len);

   // Menu de usuario
   short option;
   do
   {
      // Limpiamos pantalla
      // clear();

      boldBar(40);
      printf("MENÚ PRINCIPAL\n");

      lightBar(40);
      printf("\t>> 1: Ver registros.\n");
      printf("\t>> 2: Crear registros.\n");
      printf("\t>> 3: Actualizar registros.\n");
      printf("\t>> 4: Eliminar registros.\n");
      printf("\t>> 5: Reportes.\n");
      printf("\n\t>> 0: Salir del programa.\n");

      boldBar(40);
      lightBar(40);
      printf("Opción: ");
      scanf("%hd", &option);
      fflush(stdin);
      lightBar(40);

      switch (option)
      {
      case 0:
         // clear();
         printf("Saliendo...\n");
         Sleep(Wait);
         break;
      case 1:
         ver_registros_menu(registros, len);
         break;
      case 2:
         crear_registros_menu(registros, data, &len);
         break;
      case 3:
         actualizar_registros_menu(registros, data);
         break;
      case 4:
         eliminar_registros_menu(registros, data);
         break;
      case 5:
         reportes_menu(registros, data);
         break;
      default:
         printf("Error de menú 1: main()\n");
      }

   } while (option != 0);
}

void ver_registros_menu(password *registros, int len)
{
   short option;

   do
   {
      // Limpiamos pantalla
      // clear();

      boldBar(40);
      printf("MENÚ VER REGISTROS\n");

      lightBar(40);
      printf("\t>> 1: Listar todos los registros.\n");
      printf("\t>> 2: Buscar un registro.\n");
      printf("\t>> 3: Filtrar registros.\n");
      printf("\n\t>> 0: Volver al menú principal.\n");

      boldBar(40);
      lightBar(40);
      printf("Opción: ");
      scanf("%hd", &option);
      fflush(stdin);
      lightBar(40);

      switch (option)
      {
      case 0:
         break;
      case 1:
         all_records(registros, len); // Agregar: si no hay regristros, mostrar mensaje "SIN REGISTROS"
         break;
      case 2:
         find_record(registros, len); // Agregar: si no hay regristros, mostrar mensaje "SIN REGISTROS"
         break;
      case 3:
         filter_records(registros, len); // Agregar: si no hay regristros, mostrar mensaje "SIN REGISTROS"
         break;
      default:
         printf("Error de menú 1: ver_registros_menu()\n");
      }
   } while (option != 0);
}

void all_records(password *registros, int len)
{
   // Limpiamos pantalla
   // clear();

   short option;

   do
   {
      boldBar(80);
      printf("\t\tLISTADO DE REGISTROS\n");
      lightBar(80);
      lightBar(80);
      for (int flag = 0; flag < len; flag++)
      {
         printf("|\t%d\t|\t", registros[flag].ID);
         printf("%s\t|\t", registros[flag].sitio);
         printf("%s\t|\t", registros[flag].usuario);
         printf("%s\t|\n", registros[flag].contenido); // Implementar el cifrado que hizo Manito
         lightBar(80);
         printf("\n");
      }
      boldBar(80);

      printf("\n¿Desea exportar este reporte en PDF? (Si -> 1 / No -> 0):");
      scanf("%hd", &option);
      fflush(stdin);

      switch (option)
      {
      case 0:
         break;
      case 1:
         printf("Exportando...\n"); // Aquí es donde entran las funciones de reportes
         Sleep(Wait);
         option = 0;
         break;
      default:
         printf("Error de menú 1: all_records()\n");
      }

   } while (option != 0);
}

void find_record(password *registros, int len)
{
   // Limpiamos pantalla
   // clear();

   short option, ID_temp, baton = 0;

   do
   {
      printf("¿Qué registro desea ver? (ID): ");
      scanf("%hd", &ID_temp);
      fflush(stdin);

      for (int flag = 0; flag < len; flag++)
      {
         if (ID_temp == registros[flag].ID)
         {
            printf("|\t%d\t|\t", registros[flag].ID);
            printf("%s\t|\t", registros[flag].sitio);
            printf("%s\t|\t", registros[flag].usuario);
            printf("%s\t|\n", registros[flag].contenido);
            baton = 1;
            break;
         }
      }

      if (baton == 0)
      {
         printf("Error de busqueda 1: find_record()\n");
         Sleep(Wait);
         // clear();
         do
         {
            printf("¿Desea buscar otro registro? (Si -> 1 / No -> 0): ");
            scanf("%hd", &option);
            fflush(stdin);

            switch (option)
            {
            case 0:
               break;
            case 1:
               find_record(registros, len);
               break;
            default:
               printf("Error de menú 1: find_record()\n");
            }
         } while (option != 0);

         if (option == 0)
         {
            break;
         }
      }

      printf("\n¿Desea exportar este reporte en PDF? (Si -> 1 / No -> 0): ");
      scanf("%hd", &option);
      fflush(stdin);

      switch (option)
      {
      case 0:
         break;
      case 1:
         printf("Exportando...\n"); // Aquí es donde entran las funciones de reportes
         Sleep(Wait);
         option = 0;
         break;
      default:
         printf("Error de menú 1: find_record()\n");
      }

   } while (option != 0);
}

void filter_records(password *registros, int len)
{
   short option;

   do
   {
      // Limpiamos pantalla
      // clear();

      boldBar(40);
      printf("FILTROS\n");

      lightBar(40);
      printf("\t>> 1: Filtrar por sitio.\n");
      printf("\t>> 2: Filtrar por nombre de usuario.\n");
      printf("\n\t>> 0: Volver.\n");

      boldBar(40);
      lightBar(40);
      printf("Opción: ");
      scanf("%hd", &option);
      fflush(stdin);
      lightBar(40);

      switch (option)
      {
      case 0:
         break;
      case 1:
         printf("Filtrando por sitio\n"); // Agregar filtro
         break;
      case 2:
         printf("Filtrando por nombre de usuario\n"); // Agregar filtro
         break;
      default:
         printf("Error de menú 1: filter_records()\n");
      }
   } while (option != 0);
}

void crear_registros_menu(password *registros, FILE *data, int *len)
{
   short option;

   do
   {
      // Limpiamos pantalla
      // clear();

      boldBar(40);
      printf("MENÚ CREAR REGISTROS\n");

      lightBar(40);
      printf("\t>> 1: Creación manual.\n");
      printf("\t>> 2: Creación asistida.\n");
      printf("\n\t>> 0: Volver al menú principal.\n");

      boldBar(40);
      lightBar(40);
      printf("Opción: ");
      scanf("%hd", &option);
      fflush(stdin);
      lightBar(40);

      switch (option)
      {
      case 0:
         break;
      case 1:
         create_record(registros, data, 0, len); //
         break;
      case 2:
         create_record(registros, data, 1, len); //
         break;
      default:
         printf("Error de menú 1: crear_registros_menu()\n");
      }
   } while (option != 0);
}

void create_record(password *registros, FILE *data, short automatic, int *len)
{
   short option;
   password temp;

   // Limpiamos pantalla
   // clear();

   if (automatic == 0)
   {
      // Creación manual
      do
      {
         boldBar(80);
         printf("CREACIÓN MANUAL DE REGISTRO\n");
         boldBar(80);
         lightBar(80);

         printf("Sitio: ");
         gets(temp.sitio);

         printf("Nombre de usuario: ");
         gets(temp.usuario);

         printf("Contraseña: ");
         gets(temp.contenido);

         Sleep(Wait);
         // clear();

         lightBar(80);
         printf("Sitio: %s\n", temp.sitio);

         lightBar(80);
         printf("Nombre de usuario: %s\n", temp.usuario);

         lightBar(80);
         printf("Contraseña: %s\n", temp.contenido);

         lightBar(80);
         printf("¿Son correctos los datos? (Si -> 1 | No -> 0): ");
         scanf("%hd", &option);
         fflush(stdin);
         boldBar(80);

         switch (option)
         {
         case 0:
            break;
         case 1:
            registros[*len].ID = *len;
            strcpy(registros[*len].sitio, temp.sitio);
            strcpy(registros[*len].usuario, temp.usuario);
            strcpy(registros[*len].contenido, temp.contenido);
            registros[*len].token = rand() % 101;
            registros[*len].visibilidad = 1;
            *len += 1;

            save_data(registros, data, *len); //
            break;
         default:
            printf("Error de menú 1: create_record()\n");
         }
      } while (option != 1);
   }
   else if (automatic == 1)
   {
      int lenNombre, lenPass;

      // Creación asistida
      do
      {
         boldBar(80);
         printf("CREACIÓN ASISTIDA DE REGISTRO\n");
         boldBar(80);
         lightBar(80);

         printf("Sitio: ");
         gets(temp.sitio);

         printf("Largo del nombre de usuario (máximo 255): ");
         scanf("%d", &lenNombre);
         fflush(stdin);
         rand_strings(temp.usuario, lenNombre);

         printf("Largo de la contraseña (máximo 1000): ");
         scanf("%d", &lenPass);
         fflush(stdin);
         rand_strings(temp.contenido, lenPass);

         Sleep(Wait);
         // clear();

         lightBar(80);
         printf("Sitio: %s\n", temp.sitio);

         lightBar(80);
         printf("Nombre de usuario: %s\n", temp.usuario);
         lightBar(80);
         printf("Contraseña: %s\n", temp.contenido);

         lightBar(80);
         printf("¿Son correctos los datos? (Si -> 1 | No -> 0): ");
         scanf("%hd", &option);
         fflush(stdin);

         switch (option)
         {
         case 0:
            break;
         case 1:
            registros[*len].ID = *len;
            strcpy(registros[*len].sitio, temp.sitio);
            strcpy(registros[*len].usuario, temp.usuario);
            strcpy(registros[*len].contenido, temp.contenido);
            registros[*len].token = rand() % 101;
            registros[*len].visibilidad = 1;
            *len += 1;

            save_data(registros, data, *len); //
            break;
         default:
            printf("Error de menú 1: create_record()\n");
         }
      } while (option != 1);
   }
   else
   {
      printf("Error de creación 1: create_record()\n");
   }
}

void rand_strings(char *cadena, int len)
{
   char letras[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890";

   for (int i = 0; i < len; i++)
   {
      int index = rand() % 63;
      cadena[i] = letras[index];
   }
}

void actualizar_registros_menu(password *registros, FILE *data)
{
   short option;

   do
   {
      // Limpiamos pantalla
      // clear();

      boldBar(40);
      printf("MENÚ ACTUALIZAR REGISTROS\n");

      lightBar(40);
      printf("\t>> 1: Actualizar todos los datos de un registro.\n");
      printf("\t>> 2: Actualizar un solo dato de un registro.\n");
      printf("\n\t>> 0: Volver al menú principal.\n");

      boldBar(40);
      lightBar(40);
      printf("Opción: ");
      scanf("%hd", &option);
      fflush(stdin);
      lightBar(40);

      switch (option)
      {
      case 0:
         break;
      case 1:
         update_all_record(registros, data);
         break;
      case 2:
         update_gob_record(registros, data);
         break;
      default:
         printf("Error de menú 1: actualizar_registros_menu()\n");
      }
   } while (option != 0);
}

void update_all_record(password *registros, FILE *data)
{
   printf("Actualizar todos los datos de un registro.\n");
}

void update_gob_record(password *registros, FILE *data)
{
   printf("Actualizar un dato de un registro.\n");
}

void eliminar_registros_menu(password *registros, FILE *data)
{
   short option;

   do
   {
      // Limpiamos pantalla
      // clear();

      boldBar(40);
      printf("MENÚ ELIMINAR REGISTROS\n");

      lightBar(40);
      printf("\t>> 1: Borrar un registro.\n"); // Borrado lógico
      printf("\t>> 2: Eliminar un registro.\n");
      printf("\t>> 3: Eliminar todos los registros.\n");
      printf("\n\t>> 0: Volver al menú principal.\n");

      boldBar(40);
      lightBar(40);
      printf("Opción: ");
      scanf("%hd", &option);
      fflush(stdin);
      lightBar(40);

      switch (option)
      {
      case 0:
         break;
      case 1:
         erase_record(registros, data);
         break;
      case 2:
         delete_record(registros, data);
         break;
      case 3:
         delete_data();
         break;
      default:
         printf("Error de menú 1: eliminar_registros_menu()\n");
      }
   } while (option != 0);
}

void erase_record(password *registros, FILE *data)
{
   printf("Borrado lógico de un registro.\n");
}

void delete_record(password *registros, FILE *data)
{
   printf("Eliminación de un registro.\n");
}

void reportes_menu(password *registros, FILE *data)
{
   printf("Reportes.\n");
}

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
      }
      *len = flag - 1;

      fclose(data);

      if (*len == 0)
      {
         printf("Error de lectura 2: init_data()\n");
      }

      printf("Registros inicializados con éxito...\n");
      Sleep(Wait);
   }
}

void save_data(password *registros, FILE *data, int len)
{
   data = fopen(NOMBRE_ARCHIVO, "wb");

   if (data == NULL)
   {
      printf("Error de escritura 1: save_data()\n");
   }
   else
   {
      for (int flag = 0; flag < len; flag++)
      {
         fwrite(&registros[flag], sizeof(password), 1, data);
      }
      fflush(data);
      fclose(data);
      printf("Registros actualizados con éxito.\n");
   }
}

void delete_data()
{
   printf("ELIMINAR TODOS LOS REGISTROS.\n");
}

void boldBar(int length)
{
   bar("#", length);
}

void lightBar(int length)
{
   bar("-", length);
}

void bar(const char *character, int length)
{
   for (int flag = 0; flag < length; flag++)
   {
      printf(character);
   }
   printf("\n");
}

void clear()
{
   system("cls");
}

/*Listado de errores.
(Errores de lectura)
{
   Error de lectura 1: El fichero data.bin no existe.
   Error de lectura 2: El fichero data.bin está vacío o no contiene registros.
}

(Errores de escritura)
{
   Error de escritura 1: El fichero data.bin no existe.
}

(Errores de menú)
{
   Error de menú 1: La opción seleccionada por el usuario no es válida.
}

(Errores de búsqueda)
{
   Error de busqueda 1: El ID brindado no coincide con ningún registro.
}

(Errores de creación)
{
   Error de creación 1: No se reconoce la opción de creación. Valores posibles: 0 o 1.
}
*/