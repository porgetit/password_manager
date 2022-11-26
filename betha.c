#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>
#include <windows.h>
#define NOMBRE_ARCHIVO "./data/data.bin"
#define Len 100
#define Wait 1.125

typedef struct
{
   int ID;
   char sitio[1024];
   char usuario[256];
   char contenido[1024];
   int token;
   short visibilidad;
} password;

/* FUNCIONES ESTÉTICAS */
void bar(char, int);
void boldBar(int);
void ligthBar(int);
void clear();

/* FUNCIONES DE MANIPULACIÓN DE DATOS EN DISCO */
void init_data(password *, FILE *);
void save_data(password *, FILE *);
void delete_data();

/* FUNCIONES DE MANIPULACIÓN DE DATOS EN MEMORIA */
//    Funciones de impresión de datos
void ver_registros_menu(password *, FILE *);
void all_records(password *, FILE *);
void find_record(password *, FILE *);
void filter_records(password *, FILE *);

//    Funciones de creación de datos
void crear_registros_menu(password *, FILE *);
void create_record(password *, FILE *, short);

//    Funciones de actualización de datos
void actualizar_registros_menu(password *, FILE *);
void update_all_record(password *, FILE *);
void update_gob_record(password *, FILE *);

//    Funciones de eliminación de datos
void eliminar_registros_menu(password *, FILE *);

/* FUNCIONES DE GENERACIÓN DE REPORTES */
void reportes_menu(password *, FILE *);

int main(void)
{
   // Establecemos parámetros globales
   setlocale(LC_ALL, "");
   srand(time(NULL));

   // Inicializamos los punteros de estructuras
   FILE *data;
   password registros[Len];

   // Inicializamos el vector de registros
   init_data(registros, data);

   // Menu de usuario
   short option;
   do
   {
      // Limpiamos pantalla
      clear();

      boldBar(40);
      printf("MENÚ PRINCIPAL");

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
         clear();
         printf("Saliendo...\n");
         sleep(Wait);
         break;
      case 1:
         ver_registros_menu(registros, data);
         break;
      case 2:
         crear_registros_menu(registros, data);
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
         printf("Error de menu 1: main()");
      }

   } while (option != 0);
}

void ver_registros_menu(password *registros, FILE *data)
{
   short option;

   do
   {
      // Limpiamos pantalla
      clear();

      boldBar(40);
      printf("MENÚ VER REGISTROS");

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
         all_records(registros, data);
         break;
      case 2:
         find_record(registros, data);
         break;
      case 3:
         filter_records(registros, data);
         break;
      default:
         printf("Error de menu 1: ver_registros_menu()");
      }
   } while (option != 0);
}

void crear_registros_menu(password *registros, FILE *data)
{
   short option;

   do
   {
      // Limpiamos pantalla
      clear();

      boldBar(40);
      printf("MENÚ CREAR REGISTROS");

      lightBar(40);
      printf("\t>> 1: Creación manual.\n");
      printf("\t>> 2: Creación automática.\n");
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
         create_record(registros, data, 0);
         break;
      case 2:
         create_record(registros, data, 1);
         break;
      default:
         printf("Error de menu 1: crear_registros_menu()");
      }
   } while (option != 0);
}

void actualizar_registros_menu(password *registros, FILE *data)
{
   short option;

   do
   {
      // Limpiamos pantalla
      clear();

      boldBar(40);
      printf("MENÚ ACTUALIZAR REGISTROS");

      lightBar(40);
      printf("\t>> 1: Actualizar todos los datos de un registro.\n");
      printf("\t>> 2: Actualizar un solo datos de un registro.\n");
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
         printf("Error de menu 1: actualizar_registros_menu()");
      }
   } while (option != 0);
}

void eliminar_registros_menu(password *registros, FILE *data)
{
   short option;

   do
   {
      // Limpiamos pantalla
      clear();

      boldBar(40);
      printf("MENÚ ELIMINAR REGISTROS");

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
         printf("Error de menu 1: eliminar_registros_menu()");
      }
   } while (option != 0);
}

void init_data(password *registros, FILE *data)
{
   data = fopen(NOMBRE_ARCHIVO, "rb");

   if (data == NULL)
   {
      printf("Error de lectura 1: init_data()\n");
      printf("Creando el archivo...\n");
      sleep(Wait);
      data = fopen(NOMBRE_ARCHIVO, "wb");
      fflush(data);
      fclose(data);
      init_data(registros, data);
   }
   else
   {
      int flag = 0;
      while (!feof(data))
      {
         fread(&registros[flag], sizeof(password), 1, data);
         flag++;
      }

      if ((sizeof(registros) / sizeof(password)) == 0)
      {
         printf("Error de lectura 2: init_data()\n");
      }

      printf("Registros inicializados con éxito...\n");
      sleep(Wait);
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

void bar(char character, int length)
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

(Errores de menú)
{
   Error de menú 1: La opción seleccionada por el usuario no es válida.
}
*/