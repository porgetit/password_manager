#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>
#include <windows.h>
#include <string.h>
#define NOMBRE_ARCHIVO "./data/data.bin"
#define Len 100
#define Wait 1125
#define BarLen 60

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
void print_record(password);
void lists_title(const char *);
short menu(const char **);

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
void actualizar_registros_menu(password *, FILE *, int);
void update_all_record(password *, FILE *, int);
void update_gob_record(password *, FILE *, int);

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

      const char *options[] = {"MENÚ PRINCIPAL",
                               "Ver registros",
                               "Crear registros",
                               "Actualizar registros",
                               "Eliminar registros",
                               "Reportes",
                               "Salir del programa",
                               "\0"};

      option = menu(options);

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
         actualizar_registros_menu(registros, data, len);
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

      const char *options[] = {
          "MENÚ VER REGISTROS",
          "Listar todos los registros",
          "Buscar un registro",
          "Fitlrar registros",
          "Volver al menú principal",
          "\0"};

      option = menu(options);

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

   lists_title("LISTADO DE REGISTROS");
   for (int flag = 0; flag < len; flag++)
   {
      print_record(registros[flag]);
      lightBar(BarLen);
      printf("\n");
   }
   boldBar(BarLen);

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
      break;
   default:
      printf("Error de menú 1: all_records()\n");
   }
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
            print_record(registros[flag]);
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

// Aún no pruebo esta función
void filter_records(password *registros, int len)
{
   short option;

   do
   {
      // Limpiamos pantalla
      // clear();

      const char *options[] = {
          "FILTROS",
          "Filtrar por sitio",
          "Filtrar por nombre",
          "Volver",
          "\0"};

      option = menu(options);

      switch (option)
      {
      case 0:
         break;
      case 1:
         // Limpiamos pantalla
         // clear();

         short option;

         do
         {
            char input[1024];
            password registros_tmp[Len];
            int index = 0;

            printf("¿Qué sitio desea filtrar?: \n");
            gets(input);

            for (int flag = 0; flag < len; flag++)
            {
               if (strcmp(input, registros[flag].sitio) == 0)
               {
                  registros_tmp[index] = registros[flag];
                  index++;
               }
            }

            if (index == 0)
            {
               printf("Error de busqueda 2: filter_records()\n");
               do
               {
                  printf("¿Desea aplicar otro filtro? (Si -> 1 | No -> 0): ");
                  scanf("%hd", &option);

                  switch (option)
                  {
                  case 0:
                     break;
                  case 1:
                     break;
                  default:
                     printf("Error de menú 1: filter_records()\n");
                  }
               } while (option != 0 || option != 1);
            }
            else
            {
               lists_title("REGISTROS ENCONTRADOS");
               for (int flag = 0; flag < index; flag++)
               {
                  print_record(registros_tmp[flag]);
               }
            }
         } while (option != 0);
         break;
      case 2:
         // Limpiamos pantalla
         // clear();

         option = 0;

         do
         {
            char input[1024];
            password registros_tmp[Len];
            int index = 0;

            printf("¿Qué usuario desea filtrar?: \n");
            gets(input);

            for (int flag = 0; flag < len; flag++)
            {
               if (strcmp(input, registros[flag].usuario) == 0)
               {
                  registros_tmp[index] = registros[flag];
                  index++;
               }
            }

            if (index == 0)
            {
               printf("Error de busqueda 2: filter_records()\n");
               do
               {
                  printf("¿Desea aplicar otro filtro? (Si -> 1 | No -> 0): ");
                  scanf("%hd", &option);

                  switch (option)
                  {
                  case 0:
                     break;
                  case 1:
                     break;
                  default:
                     printf("Error de menú 1: filter_records()\n");
                  }
               } while (option != 0 || option != 1);
            }
            else
            {
               lists_title("REGISTROS ENCONTRADOS");
               for (int flag = 0; flag < index; flag++)
               {
                  print_record(registros_tmp[flag]);
               }
            }
         } while (option != 0);
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

      const char *options[] = {
          "MENÚ CREAR REGISTROS",
          "Creación manual",
          "Creación asistida",
          "Volver al menú principal",
          "\0"};

      option = menu(options);

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
         boldBar(BarLen);
         printf("CREACIÓN MANUAL DE REGISTRO\n");
         boldBar(BarLen);
         lightBar(BarLen);

         printf("Sitio: ");
         gets(temp.sitio);

         printf("Nombre de usuario: ");
         gets(temp.usuario);

         printf("Contraseña: ");
         gets(temp.contenido);

         Sleep(Wait);
         // clear();

         lightBar(BarLen);
         printf("Sitio: %s\n", temp.sitio);

         lightBar(BarLen);
         printf("Nombre de usuario: %s\n", temp.usuario);

         lightBar(BarLen);
         printf("Contraseña: %s\n", temp.contenido);

         lightBar(BarLen);
         printf("¿Son correctos los datos? (Si -> 1 | No -> 0): ");
         scanf("%hd", &option);
         fflush(stdin);
         boldBar(BarLen);

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
         boldBar(BarLen);
         printf("CREACIÓN ASISTIDA DE REGISTRO\n");
         boldBar(BarLen);
         lightBar(BarLen);

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

         lightBar(BarLen);
         printf("Sitio: %s\n", temp.sitio);

         lightBar(BarLen);
         printf("Nombre de usuario: %s\n", temp.usuario);
         lightBar(BarLen);
         printf("Contraseña: %s\n", temp.contenido);

         lightBar(BarLen);
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

void actualizar_registros_menu(password *registros, FILE *data, int len)
{
   short option;

   do
   {
      // Limpiamos pantalla
      // clear();

      const char *options[] = {
          "MENÚ ACTUALIZAR REGISTROS",
          "Actualizar todos los datos de un registro",
          "Actualizar un solo dato de un registro",
          "Volver al menú principal",
          "\0"};

      option = menu(options);

      switch (option)
      {
      case 0:
         break;
      case 1:
         update_all_record(registros, data, len);
         break;
      case 2:
         update_gob_record(registros, data, len);
         break;
      default:
         printf("Error de menú 1: actualizar_registros_menu()\n");
      }
   } while (option != 0);
}

// Según yo, está terminada, pero aún no la pruebo
void update_all_record(password *registros, FILE *data, int len)
{
   short option, ID_temp, baton = 0;
   password temp;

   // Limpiamos pantalla
   // clear();

   lightBar(BarLen);
   printf("¿Qué registro desea actualizar? (ID): ");
   scanf("%hd", &ID_temp);
   fflush(stdin);
   lightBar(BarLen);

   for (int flag = 0; flag < len; flag++)
   {
      if (ID_temp == registros[flag].ID)
      {
         temp = registros[flag];
         baton = 1;
         break;
      }
   }

   if (baton == 0)
   {
      printf("Error de busqueda 1: update_all_record()\n");
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
            update_all_record(registros, data, len);
            break;
         default:
            printf("Error de menú 1: find_record()\n");
         }
      } while (option != 0);
   }
   else
   {
      do
      {
         printf("Sitio: ");
         gets(temp.sitio);

         printf("Nombre de usuario: ");
         gets(temp.usuario);

         printf("Contraseña: ");
         gets(temp.contenido);

         Sleep(Wait);
         // clear();

         lightBar(BarLen);
         printf("Sitio: %s\n", temp.sitio);

         lightBar(BarLen);
         printf("Nombre de usuario: %s\n", temp.usuario);

         lightBar(BarLen);
         printf("Contraseña: %s\n", temp.contenido);

         lightBar(BarLen);
         printf("¿Son correctos los datos? (Si -> 1 | No -> 0): ");
         scanf("%hd", &option);
         fflush(stdin);
         boldBar(BarLen);

         switch (option)
         {
         case 0:
            break;
         case 1:
            strcpy(registros[ID_temp].sitio, temp.sitio);
            strcpy(registros[ID_temp].usuario, temp.usuario);
            strcpy(registros[ID_temp].contenido, temp.contenido);
            registros[ID_temp].token = rand() % 101;

            save_data(registros, data, len); //
            break;
         default:
            printf("Error de menú 1: update_all_record()\n");
         }
      } while (option != 1);
   }
}

// Aún no trabajo en esta
void update_gob_record(password *registros, FILE *data, int len)
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

      const char *options[] = {
          "MENÚ ELIMINAR REGISTROS",
          "Borrar un registro",
          "Eliminar un registro",
          "Eliminar todos los registros",
          "Volver al menú principal",
          "\0"};

      option = menu(options);

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

// Aún no trabajo en esta
void erase_record(password *registros, FILE *data)
{
   printf("Borrado lógico de un registro.\n");
}

// Aún no trabajo en esta
void delete_record(password *registros, FILE *data)
{
   printf("Eliminación de un registro.\n");
}

// Aún no trabajo en esta
void reportes_menu(password *registros, FILE *data)
{
   printf("Reportes.\n");
}

void init_data(password *registros, FILE *data, int *len)
{
   // data = fopen("C:/Users/%USERNAME%/ProyectoFinalData/data.bin", "rb");
   data = fopen(NOMBRE_ARCHIVO, "rb");

   if (data == NULL)
   {
      printf("Error de lectura 1: init_data()\n");
      printf("Creando el archivo...\n");
      Sleep(Wait);
      data = fopen(NOMBRE_ARCHIVO, "wb");
      fclose(data);
      // system("type nul > C:\\Users\\%USERNAME%\\ProyectoFinalData\\data.bin");
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

// Esta mondá todavía no funciona
void delete_data()
{
   char clave[] = "0000", temp[5];

   boldBar(BarLen);
   printf("ELIMINAR TODOS LOS REGISTROS\n");
   boldBar(BarLen);

   lightBar(BarLen);
   printf("Clave de seguridad: ");
   gets(temp);

   Sleep(Wait);
   // clear();

   if (strcmp(clave, temp) == 0)
   {
      printf("Borrando archivo...\n");
      Sleep(Wait);
      system("del C:\\Users\\%USERNAME%\\ProyectoFinalData\\data.bin"); // Implementar variables de entorno para recolocar el fichero data.bin en Program Files del windows
      Sleep(5000);
      system("type nul > C:\\Users\\%USERNAME%\\ProyectoFinalData\\data.bin");
      // fflush(stdout);
   }
   else
   {
      printf("Clave incorrecta.\n");
      Sleep(Wait);
   }
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

void print_record(password input)
{
   printf("ID : %d -> ", input.ID);
   printf("Sitio: %s -> ", input.sitio);
   printf("Usuario: %s -> ", input.usuario);
   printf("Contraseña: %s\n", input.contenido);
}

void lists_title(const char *input)
{
   boldBar(BarLen);
   printf("\t");
   printf("%s", input);
   printf("\n");
   boldBar(BarLen);
}

short menu(const char **input)
{
   int length = 0;

   while (strcmp(input[length], "\0") != 0)
   {
      length++;
   }

   short option;

   boldBar(BarLen);
   printf("%s\n", input[0]);
   lightBar(BarLen);

   for (int flag = 1; flag < length - 1; flag++)
   {
      printf("\t>> %d: %s.\n", flag, input[flag]);
   }

   boldBar(BarLen);
   printf("\n\t>> 0: %s.\n", input[length - 1]);

   lightBar(BarLen);
   printf("Opción: ");
   scanf("%hd", &option);
   fflush(stdin);
   lightBar(BarLen);

   return option;
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
   Error de busqueda 2: No hay registros que coincidan con el filtro.
}

(Errores de creación)
{
   Error de creación 1: No se reconoce la opción de creación. Valores posibles: 0 o 1.
}
*/