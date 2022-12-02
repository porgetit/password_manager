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
   char contenido[1024]; // contrase�a
   int token;
   short visibilidad;
} password;

/* FUNCIONES EST�TICAS */
void bar(const char *, int);
void boldBar(int);
void lightBar(int);
void clear();
void print_record(password);
void lists_title(const char *);
short menu(const char **);

/* FUNCIONES DE MANIPULACI�N DE DATOS EN DISCO */
void init_data(password *, FILE *, int *);
void save_data(password *, FILE *, int);
void delete_data(password *, FILE *, int *);

/* FUNCIONES DE MANIPULACI�N DE DATOS EN MEMORIA */
//    Funciones de impresi�n de datos
void ver_registros_menu(password *, int);
void all_records(password *, int);
void find_record(password *, int);
void filter_records(password *, int);

//    Funciones de creaci�n de datos
void crear_registros_menu(password *, FILE *, int *);
void create_record(password *, FILE *, short, int *);
void rand_strings(char *, int);

//    Funciones de actualizaci�n de datos
void actualizar_registros_menu(password *, FILE *, int);
void update_all_record(password *, FILE *, int);
void update_gob_record(password *, FILE *, int);

//    Funciones de eliminaci�n de datos
void eliminar_registros_menu(password *, FILE *, int *);
void erase_record(password *, FILE *, int);
void recover_record(password *, FILE *, int);

/* FUNCIONES DE GENERACI�N DE REPORTES */
void reportes_menu(password *, FILE *);
void exportar(password *, int);

int main(void)
{
   // Establecer el idioma a espa�ol
   setlocale(LC_ALL, "spanish");


   // Establecemos par�metros globales
   srand(time(NULL));

   // Inicializamos los punteros, estructuras y variables
   FILE *data;
   password registros[Len];
   int len = 0;

   // Inicializamos el vector de registros
   init_data(registros, data, &len);

   // Men� de usuario
   short option;
   do
   {
      // Limpiamos pantalla
      clear();

      const char *options[] = {"MEN� PRINCIPAL",
                               "Ver registros",
                               "Crear registros",
                               "Actualizar registros",
                               "Eliminar o recuperar registros",
                               //  "Reportes",
                               "Salir del programa",
                               "\0"};

      option = menu(options);

      switch (option)
      {
      case 0:
         clear();
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
         eliminar_registros_menu(registros, data, &len);
         break;
      // case 5:
      //    reportes_menu(registros, data);
      //    break;
      default:
         printf("Error de men� 1: main()\n");
      }

   } while (option != 0);
}

void ver_registros_menu(password *registros, int len)
{
   short option;

   do
   {
      // Limpiamos pantalla
      clear();

      const char *options[] = {
          "MEN� VER REGISTROS",
          "Listar todos los registros",
          "Buscar un registro",
          "Filtrar registros",
          "Volver al men� principal",
          "\0"};

      fflush(stdin);
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
         printf("Error de men� 1: ver_registros_menu()\n");
      }
   } while (option != 0);
}

void all_records(password *registros, int len)
{
   // Limpiamos pantalla
   clear();
   short option;
   password output[len];

   lists_title("LISTADO DE REGISTROS");
   for (int flag = 0; flag < len; flag++)
   {
      if (registros[flag].visibilidad == 1)
      {
         print_record(registros[flag]);
         output[flag] = registros[flag];
         lightBar(BarLen);
         printf("\n");
      }
   }
   boldBar(BarLen);

   printf("\n�Desea exportar este reporte en PDF? (Si -> 1 / No -> 0):");
   scanf("%hd", &option);
   fflush(stdin);

   switch (option)
   {
   case 0:
      break;
   case 1:
      printf("Exportando...\n"); // Aqui es donde entran las funciones de reportes
      Sleep(Wait);
      exportar(output, len);
      break;
   default:
      printf("Error de men� 1: all_records()\n");
   }
}

void find_record(password *registros, int len)
{
   // Limpiamos pantalla
   clear();

   short option, ID_temp, baton = 0;
   password output[1];

   do
   {
      printf("�Qu� registro desea ver? (ID): ");
      scanf("%hd", &ID_temp);
      fflush(stdin);

      for (int flag = 0; flag < len; flag++)
      {
         if (ID_temp == registros[flag].ID && registros[flag].visibilidad == 1)
         {
            lightBar(BarLen);
            print_record(registros[flag]);
            lightBar(BarLen);
            output[0] = registros[flag];
            baton = 1;
            break;
         }
      }

      if (baton == 0)
      {
         printf("Error de busqueda 1: find_record()\n");
         Sleep(Wait);
         clear();
         do
         {
            printf("�Desea buscar otro registro? (Si -> 1 / No -> 0): ");
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
               printf("Error de men� 1: find_record()\n");
            }
         } while (option != 0);

         if (option == 0)
         {
            break;
         }
      }

      printf("\n�Desea exportar este reporte en PDF? (Si -> 1 / No -> 0): ");
      scanf("%hd", &option);
      fflush(stdin);

      switch (option)
      {
      case 0:
         break;
      case 1:
         printf("Exportando...\n");
         Sleep(Wait);
         exportar(output, 1);
         option = 0;
         break;
      default:
         printf("Error de men� 1: find_record()\n");
      }

   } while (option != 0);
}

void filter_records(password *registros, int len)
{
   short option;
   password output[Len];
   do
   {
      // Limpiamos pantalla
      clear();

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
         clear();

         short option;

         do
         {
            char input[1024];
            password registros_tmp[Len];
            int index = 0;

            printf("�Qu� sitio desea filtrar?: ");
            gets(input);

            for (int flag = 0; flag < len; flag++)
            {
               if (strcmp(input, registros[flag].sitio) == 0 && registros[flag].visibilidad == 1)
               {
                  registros_tmp[index] = registros[flag];
                  index++;
               }
            }

            if (index == 0)
            {
               printf("Error de busqueda 2: filter_records()\n");
               printf("�Desea aplicar otro filtro? (Si -> 1 | No -> 0): ");
               scanf("%hd", &option);

               switch (option)
               {
               case 0:
                  break;
               case 1:
                  break;
               default:
                  printf("Error de men� 1: filter_records()\n");
               }

               if (option == 0)
               {
                  break;
               }
            }
            else
            {
               lists_title("REGISTROS ENCONTRADOS");
               for (int flag = 0; flag < index; flag++)
               {
                  if (registros_tmp[flag].visibilidad == 1)
                  {
                     print_record(registros_tmp[flag]);
                     output[flag] = registros_tmp[flag];
                     lightBar(BarLen);
                     printf("\n");
                  }
               }
               option = 0;
            }

            do
            {
               printf("\n�Desea exportar este reporte en PDF? (Si -> 1 / No -> 0): ");
               scanf("%hd", &option);
               fflush(stdin);

               switch (option)
               {
               case 0:
                  break;
               case 1:
                  printf("Exportando...\n");
                  Sleep(Wait);
                  exportar(output, len);
                  option = 0;
                  break;
               default:
                  printf("Error de men� 1: find_record()\n");
               }
            } while (option != 0);

         } while (option != 0);
         break;
      case 2:
         // Limpiamos pantalla
         clear();

         option = 0;

         do
         {
            char input[1024];
            password registros_tmp[Len];
            int index = 0;

            printf("�Qu� usuario desea filtrar?: ");
            gets(input);

            for (int flag = 0; flag < len; flag++)
            {
               if (strcmp(input, registros[flag].usuario) == 0 && registros[flag].visibilidad == 1)
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
                  printf("�Desea aplicar otro filtro? (Si -> 1 | No -> 0): ");
                  scanf("%hd", &option);

                  switch (option)
                  {
                  case 0:
                     break;
                  case 1:
                     break;
                  default:
                     printf("Error de men� 1: filter_records()\n");
                  }
               } while (option != 0 || option != 1);
            }
            else
            {
               lists_title("REGISTROS ENCONTRADOS");
               for (int flag = 0; flag < index; flag++)
               {
                  print_record(registros_tmp[flag]);
                  output[flag] = registros_tmp[flag];
                  lightBar(BarLen);
                  printf("\n");
               }
            }

            do
            {
               printf("\n�Desea exportar este reporte en PDF? (Si -> 1 / No -> 0): ");
               scanf("%hd", &option);
               fflush(stdin);

               switch (option)
               {
               case 0:
                  break;
               case 1:
                  printf("Exportando...\n");
                  Sleep(Wait);
                  exportar(output, len);
                  option = 0;
                  break;
               default:
                  printf("Error de men� 1: find_record()\n");
               }
            } while (option != 0);

         } while (option != 0);
         break;
      default:
         printf("Error de men� 1: filter_records()\n");
      }
   } while (option != 0);
}

void crear_registros_menu(password *registros, FILE *data, int *len)
{
   short option;

   do
   {
      // Limpiamos pantalla
      clear();

      const char *options[] = {
          "MEN� CREAR REGISTROS",
          "Creaci�n manual",
          "Creaci�n asistida",
          "Volver al men� principal",
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
         printf("Error de men� 1: crear_registros_menu()\n");
      }
   } while (option != 0);
}

void create_record(password *registros, FILE *data, short automatic, int *len)
{
   short option;
   password temp;

   // Limpiamos pantalla
   clear();

   if (automatic == 0)
   {
      // Creaci�n manual
      do
      {
         boldBar(BarLen);
         printf("CREACI�N MANUAL DE REGISTRO\n");
         boldBar(BarLen);
         lightBar(BarLen);

         printf("Sitio: ");
         gets(temp.sitio);

         printf("Nombre de usuario: ");
         gets(temp.usuario);

         printf("Contrase�a: ");
         gets(temp.contenido);

         Sleep(Wait);
         clear();

         lightBar(BarLen);
         printf("Sitio: %s\n", temp.sitio);

         lightBar(BarLen);
         printf("Nombre de usuario: %s\n", temp.usuario);

         lightBar(BarLen);
         printf("Contrase�a: %s\n", temp.contenido);

         lightBar(BarLen);
         printf("�Son correctos los datos? (Si -> 1 | No -> 0): ");
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
            printf("Error de men� 1: create_record()\n");
         }
      } while (option != 1);
   }
   else if (automatic == 1)
   {
      int lenNombre, lenPass;

      // Creaci�n asistida
      do
      {
         boldBar(BarLen);
         printf("CREACI�N ASISTIDA DE REGISTRO\n");
         boldBar(BarLen);
         lightBar(BarLen);

         printf("Sitio: ");
         gets(temp.sitio);

         printf("Largo del nombre de usuario (m�ximo 255): ");
         scanf("%d", &lenNombre);
         fflush(stdin);
         rand_strings(temp.usuario, lenNombre);

         printf("Largo de la contrase�a (m�ximo 1000): ");
         scanf("%d", &lenPass);
         fflush(stdin);
         rand_strings(temp.contenido, lenPass);

         Sleep(Wait);
         clear();

         lightBar(BarLen);
         printf("Sitio: %s\n", temp.sitio);

         lightBar(BarLen);
         printf("Nombre de usuario: %s\n", temp.usuario);
         lightBar(BarLen);
         printf("Contrase�a: %s\n", temp.contenido);

         lightBar(BarLen);
         printf("�Son correctos los datos? (Si -> 1 | No -> 0): ");
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
            printf("Error de men� 1: create_record()\n");
         }
      } while (option != 1);
   }
   else
   {
      printf("Error de creaci�n 1: create_record()\n");
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
      clear();

      const char *options[] = {
          "MEN� ACTUALIZAR REGISTROS",
          "Actualizar todos los datos de un registro",
          //  "Actualizar un solo dato de un registro",
          "Volver al men� principal",
          "\0"};

      option = menu(options);

      switch (option)
      {
      case 0:
         break;
      case 1:
         update_all_record(registros, data, len);
         break;
      // case 2:
      //    update_gob_record(registros, data, len);
      //    break;
      default:
         printf("Error de men� 1: actualizar_registros_menu()\n");
      }
   } while (option != 0);
}

void update_all_record(password *registros, FILE *data, int len)
{
   short option, ID_temp, baton = 0;
   password temp;

   // Limpiamos pantalla
   clear();

   lightBar(BarLen);
   printf("�Qu� registro desea actualizar? (ID): ");
   scanf("%hd", &ID_temp);
   fflush(stdin);
   lightBar(BarLen);

   for (int flag = 0; flag < len; flag++)
   {
      if (ID_temp == registros[flag].ID && registros[flag].visibilidad == 1)
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
      clear();
      do
      {
         printf("�Desea buscar otro registro? (Si -> 1 / No -> 0): ");
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
            printf("Error de men� 1: update_all_record()\n");
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

         printf("Contrase�a: ");
         gets(temp.contenido);

         Sleep(Wait);
         clear();

         lightBar(BarLen);
         printf("Sitio: %s\n", temp.sitio);

         lightBar(BarLen);
         printf("Nombre de usuario: %s\n", temp.usuario);

         lightBar(BarLen);
         printf("Contrase�a: %s\n", temp.contenido);

         lightBar(BarLen);
         printf("�Son correctos los datos? (Si -> 1 | No -> 0): ");
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
            printf("Error de men� 1: update_all_record()\n");
         }
      } while (option != 1);
   }
}

// A�n no trabajo en esta. Dejar como opcional
void update_gob_record(password *registros, FILE *data, int len)
{
   printf("Actualizar un dato de un registro.\n");
}

void eliminar_registros_menu(password *registros, FILE *data, int *len)
{
   short option;

   do
   {
      // Limpiamos pantalla
      clear();

      const char *options[] = {
          "MEN� ELIMINAR REGISTROS",
          "Borrar un registro",
          "Recuperar un registro",
          "Eliminar todos los registros",
          "Volver al men� principal",
          "\0"};

      option = menu(options);

      switch (option)
      {
      case 0:
         break;
      case 1:
         erase_record(registros, data, *len);
         break;
      case 2:
         recover_record(registros, data, *len);
         break;
      case 3:
         delete_data(registros, data, len);
         break;
      default:
         printf("Error de men� 1: eliminar_registros_menu()\n");
      }
   } while (option != 0);
}

void erase_record(password *registros, FILE *data, int len)
{
   short option, ID_temp, baton = 0;
   password temp;

   // Limpiamos pantalla
   clear();

   lightBar(BarLen);
   printf("�Qu� registro desea eliminar? (ID): ");
   scanf("%hd", &ID_temp);
   fflush(stdin);
   lightBar(BarLen);

   for (int flag = 0; flag < len; flag++)
   {
      if (ID_temp == registros[flag].ID && registros[flag].visibilidad == 1)
      {
         temp = registros[flag];
         baton = 1;
         break;
      }
   }

   if (baton == 0)
   {
      printf("Error de busqueda 1: erase_record()\n");
      Sleep(Wait);
      clear();
      do
      {
         printf("�Desea buscar otro registro? (Si -> 1 / No -> 0): ");
         scanf("%hd", &option);
         fflush(stdin);

         switch (option)
         {
         case 0:
            break;
         case 1:
            erase_record(registros, data, len);
            break;
         default:
            printf("Error de men� 1: erase_record()\n");
         }
      } while (option != 0);
   }
   else
   {
      temp.visibilidad = 0;

      Sleep(Wait);
      clear();

      registros[ID_temp].visibilidad = temp.visibilidad;
      printf("Registro eliminado.\n");
      save_data(registros, data, len); //
      Sleep(Wait);
   }
}

void recover_record(password *registros, FILE *data, int len)
{
   short option, ID_temp, baton = 0;
   password temp;

   // Limpiamos pantalla
   clear();

   lists_title("LISTADO DE REGISTROS ELIMINADOS");
   for (int flag = 0; flag < len; flag++)
   {
      if (registros[flag].visibilidad == 0)
      {
         print_record(registros[flag]);
         lightBar(BarLen);
         printf("\n");
         baton++;
      }
   }
   boldBar(BarLen);

   if (baton != 0)
   {
      baton = 0;
      lightBar(BarLen);
      printf("�Qu� registro desea recuperar? (ID): ");
      scanf("%hd", &ID_temp);
      fflush(stdin);
      lightBar(BarLen);

      for (int flag = 0; flag < len; flag++)
      {
         if (ID_temp == registros[flag].ID && registros[flag].visibilidad == 0)
         {
            temp = registros[flag];
            baton++;
            break;
         }
      }

      if (baton == 0)
      {
         printf("Error de busqueda 1: recover_record()\n");
         Sleep(Wait);
         clear();
         do
         {
            printf("�Desea buscar otro registro? (Si -> 1 / No -> 0): ");
            scanf("%hd", &option);
            fflush(stdin);

            switch (option)
            {
            case 0:
               break;
            case 1:
               recover_record(registros, data, len);
               break;
            default:
               printf("Error de men� 1: recover_record()\n");
            }
         } while (option != 0);
      }
      else
      {
         temp.visibilidad = 1;

         Sleep(Wait);
         clear();

         registros[ID_temp].visibilidad = temp.visibilidad;
         printf("Registro recuperado.\n");
         save_data(registros, data, len); //
      	 Sleep(Wait);
      }
   }
   else
   {
      printf("Error de busqueda 2: recover_record()\n");
      Sleep(Wait);
   }
}

// A�n no trabajo en esta
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

      printf("Registros inicializados con �xito...\n");
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
      printf("Registros actualizados con �xito.\n");
   }
}

void delete_data(password *registros, FILE *data, int *len)
{
   FILE *archi;
   char clave[] = "0000", temp[5];

   boldBar(BarLen);
   printf("ELIMINAR TODOS LOS REGISTROS\n");
   boldBar(BarLen);

   lightBar(BarLen);
   printf("Clave de seguridad: ");
   gets(temp);

   Sleep(Wait);
   clear();

   if (strcmp(clave, temp) == 0)
   {
      printf("Borrando archivo...\n");
      Sleep(Wait);
      remove("./data/data.bin");
      Sleep(Wait);
      init_data(registros, data, len);
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
   printf("ID : %d | ", input.ID);
   printf("Sitio: %s | ", input.sitio);
   printf("Usuario: %s | ", input.usuario);
   printf("Contrase�a: %s\n", input.contenido);
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
   printf("Opci�n: ");
   scanf("%hd", &option);
   fflush(stdin);
   lightBar(BarLen);

   return option;
}

void exportar(password *input, int len)
{
   FILE *data;
   data = fopen("./data/export.txt", "w");

   if (data == NULL)
   {
      printf("Error de escritura 1: exportar()\n");
   }
   else
   {
      for (int flag = 0; flag < len; flag++)
      {
         fprintf(data, "ID : %d \n Sitio: %s \n Usuario: %s \n Contrase�a: %s\n", input[flag].ID, input[flag].sitio, input[flag].usuario, input[flag].contenido);
      }
      fflush(data);
      fclose(data);
   }

   system("python pdf.py");
   system("start ./data/export.pdf");
}

/*Listado de errores.
(Errores de lectura)
{
   Error de lectura 1: El fichero data.bin no existe.
   Error de lectura 2: El fichero data.bin est� vac�o o no contiene registros.
}

(Errores de escritura)
{
   Error de escritura 1: El fichero data.bin no existe.
}

(Errores de men�)
{
   Error de men� 1: La opci�n seleccionada por el usuario no es v�lida.
}

(Errores de busqueda)
{
   Error de busqueda 1: El ID brindado no coincide con ningun registro.
   Error de busqueda 2: No hay registros que coincidan con el filtro.
}

(Errores de creaci�n)
{
   Error de creaci�n 1: No se reconoce la opci�n de creaci�n. Valores posibles: 0 o 1.
}
*/
