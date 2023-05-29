#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>
#include <assert.h>
#include "paralelismo.h"
#include <string.h>

int thread_count;
struct timeval t_start, t_end;
double exec_time;
int option;       // Número de Operación a realizar
int hilos;        // Número de hilos
double escalar;   // Número escalar
int rows1, cols1; // Número de fila y columnas respectivamente del primer operando
int rows2, cols2; // Número de fila y columnas respectivamente del segundo operando
Matrix *A;
Matrix *B;
Matrix *result_m;
Vector *result_v;
int is_file = 0; // Para comprobar si la lectura de matrices es por archivo y evitar crear matrices aleatorias

void selectMenu(char *submenu)
{
    int opcion, h;
    double e;

    do
    {
        printf("\n"
            "################################\n"
            "################################\n"
            "#####   MENU  SECUNDARIO   #####\n"
            "################################\n"
            "################################\n"
            "\n"
            "\n"
            "================================\n"
            "     SELECCIONE UNA OPCIÓN      \n"
            "================================\n"
            "\n");
        printf("\n");
        printf("1. Calcular la media de cada columna de la matriz A\n");
        printf("2. Calcular la varianza de cada columna de la matriz A:\n");
        printf("3. Calcular la variación estandar de cada columna de la matriz A\n");
        printf("4. Calcular el valor minimo y el valor maximo de cada columna de la matriz A\n");
        printf("5. Calcular la suma de la matriz A con la matriz B\n");
        printf("6. Calcular el producto punto de la matriz A con la matriz B\n");
        printf("7. Calcular el producto de un escalar con la matriz A\n");
        printf("8. Calcular la normalización (Opción 1) de las columnas de la matriz A\n");
        printf("9. Calcular la normalización (Opción 2) de las columnas de la matriz A\n");
        printf("0. Salir de la aplicación\n");
        scanf("%d", &opcion);

        if (opcion == 1 || opcion == 2 || opcion == 3 || opcion == 4 || opcion == 7 || opcion == 8 || opcion == 9)
        {
            if (opcion == 7)
            {
                printf("Indique el valor del escalar que desea multiplicar la matriz A\n");
                scanf("%lf", &escalar);
                e = escalar;
            }
            if (strcmp(submenu, "Concurrencia") == 0)
            {
                printf("Indique con cuantos hilos desea trabajar. \n"
                       "(Recuerde que el número de hilos debe ser inferior al número de columnas que ingrese en las matrices): ");
                scanf("%d", &hilos);
                printf("Indique cuantas filas desea que tenga la matriz A:\n ");
                scanf("%d", &rows1);
                printf("Indique cuantas columnas de la matriz A:\n ");
                scanf("%d", &cols1);
                if (cols1 < hilos)
                {
                    do
                    {
                        printf("Indique las columnas de la matriz A, recuerde que debe ser mayor al número de hilos:\n ");
                        scanf("%d", &cols1);
                    } while (cols1 < hilos);
                }
            }
            else
            {
                printf("Indique cuantas filas desea que tenga la matriz A:\n ");
                scanf("%d", &rows1);
                printf("Indique cuantas columnas desea que tenga la matriz A:\n ");
                scanf("%d", &cols1);
            }

            printf("-------------------Creación de la matriz---------------\n");
            if (is_file == 0)
            {
                A = create_matrix(rows1, cols1);
                init_matrix_rand(A);
            }
            print_matrix(A);
        }
        else if (opcion == 5 || opcion == 6)
        {
            if (strcmp(submenu, "Concurrencia") == 0)
            {
                printf("Indique con cuantos hilos desea trabajar. \n"
                       "(Recuerde que el número de hilos debe ser inferior al número de columnas que ingrese en las matrices): ");
                scanf("%d", &hilos);
                printf("Indique cuantas filas desea que tenga la matriz A:\n ");
                scanf("%d", &rows1);
                printf("Indique las columnas de la matriz A:\n ");
                scanf("%d", &cols1);
                if (cols1 < hilos)
                {
                    do
                    {
                        printf("Indique las columnas de la matriz A, recuerde que debe ser mayor al número de hilos:\n ");
                        scanf("%d", &cols1);
                    } while (cols1 < hilos);
                }

                printf("Indique cuantas filas desea que tenga la matriz B:\n ");
                scanf("%d", &rows2);
                printf("Indique las columnas de la matriz B:\n ");
                scanf("%d", &cols2);
                if (cols2 < hilos)
                {
                    do
                    {
                        printf("Indique las columnas de la matriz B, recuerde que debe ser mayor al número de hilos:\n ");
                        scanf("%d", &cols2);
                    } while (cols2 < hilos);
                }
            }
            else
            {
                printf("Indique cuantas filas desea que tenga la matriz A:\n ");
                scanf("%d", &rows1);
                printf("Indique cuantas columnas desea que tenga la matriz A:\n ");
                scanf("%d", &cols1);
                printf("Indique cuantas filas desea que tenga la matriz B:\n ");
                scanf("%d", &rows2);
                printf("Indique cuantas columnas desea que tenga la matriz B:\n ");
                scanf("%d", &cols2);
            }
            printf("-------------------Creación de las matrices---------------\n");
            if (is_file == 0)
            {
                A = create_matrix(rows1, cols1);
                B = create_matrix(rows2, cols2);
                init_matrix_rand(A);
                init_matrix_rand(B);
            }
            print_matrix(A);
            print_matrix(B);
        }

        switch (opcion)
        {
        case 1:
            printf("\n"
                   "###################################################\n"
                   "#      Media de cada columna de la matriz A       #\n"
                   "###################################################\n"
                   "\n");
            printf("Calculando la media de cada columna de la matriz A[%dx%d]: \n", rows1, cols1);

            if (strcmp(submenu, "Secuencial") == 0)
            {
                // Secuencial
                gettimeofday(&t_start, NULL);
                result_v = init_vector_threads(A, 1, 1);
                printf("------------VECTOR RESULTANTE---------------\n");
                print_vector(result_v);

                gettimeofday(&t_end, NULL);

                exec_time = (t_end.tv_sec - t_start.tv_sec) * 1000.0;    // sec to ms
                exec_time += (t_end.tv_usec - t_start.tv_usec) / 1000.0; // us to ms
                printf("\n"
                       "$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n"
                       "      Tiempo de ejecución secuencial: %f ms \n",
                       exec_time);
                printf("$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n");
            }
            else
            {
                // Opción para concurrencia
                // Hilos
                gettimeofday(&t_start, NULL);
                result_v = init_vector_threads(A, hilos, 1);
                printf("------------VECTOR RESULTANTE---------------\n");
                print_vector(result_v);

                gettimeofday(&t_end, NULL);

                exec_time = (t_end.tv_sec - t_start.tv_sec) * 1000.0;    // sec to ms
                exec_time += (t_end.tv_usec - t_start.tv_usec) / 1000.0; // us to ms
                printf("\n"
                       "$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n"
                       "      Tiempo de ejecución con hilos: %f ms \n",
                       exec_time);
                printf("$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n");
            }
            free_matrix(A);
            free_vector(result_v);
            break;

        case 2:
            printf("\n"
                   "###################################################\n"
                   "#      Varianza de cada columna de la matriz A    #\n"
                   "###################################################\n"
                   "\n");
            printf("Calculando la varianza de cada columna de la matriz A[%dx%d]: \n", rows1, cols1);

            if (strcmp(submenu, "Secuencial") == 0)
            {
                // Secuencial
                gettimeofday(&t_start, NULL);
                result_v = init_vector_threads(A, 1, 2);
                printf("------------VECTOR RESULTANTE---------------\n");
                print_vector(result_v);

                gettimeofday(&t_end, NULL);

                exec_time = (t_end.tv_sec - t_start.tv_sec) * 1000.0;    // sec to ms
                exec_time += (t_end.tv_usec - t_start.tv_usec) / 1000.0; // us to ms
                printf("\n"
                       "$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n"
                       "      Tiempo de ejecución secuencial: %f ms \n",
                       exec_time);
                printf("$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n");
            }
            else
            {
                // Opción para concurrencia
                gettimeofday(&t_start, NULL);
                result_v = init_vector_threads(A, hilos, 2);
                printf("------------VECTOR RESULTANTE---------------\n");
                print_vector(result_v);

                gettimeofday(&t_end, NULL);

                exec_time = (t_end.tv_sec - t_start.tv_sec) * 1000.0;    // sec to ms
                exec_time += (t_end.tv_usec - t_start.tv_usec) / 1000.0; // us to ms
                printf("\n"
                       "$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n"
                       "      Tiempo de ejecución con hilos: %f ms \n",
                       exec_time);
                printf("$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n");
            }
            free_matrix(A);
            free_vector(result_v);

            break;

        case 3:
            printf("\n"
                   "########################################################\n"
                   "# Variación estandar de cada columna de la matriz A    #\n"
                   "########################################################\n"
                   "\n");
            printf("Calculando la variación estandar de cada columna de la matriz A[%dx%d]: \n", rows1, cols1);

            if (strcmp(submenu, "Secuencial") == 0)
            {
                // Secuencial
                gettimeofday(&t_start, NULL);
                result_v = init_vector_threads(A, 1, 3);
                printf("------------VECTOR RESULTANTE---------------\n");
                print_vector(result_v);

                gettimeofday(&t_end, NULL);
                exec_time = (t_end.tv_sec - t_start.tv_sec) * 1000.0;    // sec to ms
                exec_time += (t_end.tv_usec - t_start.tv_usec) / 1000.0; // us to ms
                printf("\n"
                       "$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n"
                       "      Tiempo de ejecución secuencial: %f ms \n",
                       exec_time);
                printf("$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n");
            }
            else
            {
                // Opción para concurrencia
                // Hilos
                gettimeofday(&t_start, NULL);
                result_v = init_vector_threads(A, hilos, 3);
                printf("------------VECTOR RESULTANTE---------------\n");
                print_vector(result_v);

                gettimeofday(&t_end, NULL);

                exec_time = (t_end.tv_sec - t_start.tv_sec) * 1000.0;    // sec to ms
                exec_time += (t_end.tv_usec - t_start.tv_usec) / 1000.0; // us to ms
                printf("\n"
                       "$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n"
                       "      Tiempo de ejecución con hilos: %f ms \n",
                       exec_time);
                printf("$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n");
            }
            free_matrix(A);
            free_vector(result_v);
            break;

        case 4:
            printf("\n"
                   "########################################################\n"
                   "#   Valor mínimo y máximo de columnas de la matriz A   #\n"
                   "########################################################\n"
                   "\n");
            printf("\nCalculando el valor minimo y el valor maximo de cada columna de la matriz A[%dx%d]: \n", rows1, cols1);
            if (strcmp(submenu, "Secuencial") == 0)
            {
                // Secuencial
                gettimeofday(&t_start, NULL);
                result_v = init_vector_threads(A, 1, 4);
                printf("------------VECTOR DE MINIMOS---------------\n");
                print_vector(result_v);

                result_v = init_vector_threads(A, 1, 5);
                printf("------------VECTOR DE MÁXIMOS---------------\n");
                print_vector(result_v);

                gettimeofday(&t_end, NULL);

                exec_time = (t_end.tv_sec - t_start.tv_sec) * 1000.0;    // sec to ms
                exec_time += (t_end.tv_usec - t_start.tv_usec) / 1000.0; // us to ms
                printf("\n"
                       "$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n"
                       "      Tiempo de ejecución secuencial: %f ms \n",
                       exec_time);
                printf("$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n");
            }
            else
            {
                // Opción para concurrencia
                // Hilos
                gettimeofday(&t_start, NULL);
                result_v = init_vector_threads(A, hilos, 4);
                printf("\n------------VECTOR DE MINIMOS---------------\n");
                print_vector(result_v);

                result_v = init_vector_threads(A, hilos, 5);
                printf("------------VECTOR DE MÁXIMOS---------------\n");
                print_vector(result_v);

                gettimeofday(&t_end, NULL);

                exec_time = (t_end.tv_sec - t_start.tv_sec) * 1000.0;    // sec to ms
                exec_time += (t_end.tv_usec - t_start.tv_usec) / 1000.0; // us to ms
                printf("\n"
                       "$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n"
                       "      Tiempo de ejecución con hilos: %f ms \n",
                       exec_time);
                printf("$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n");
            }
            free_matrix(A);
            free_vector(result_v);
            break;

        case 5:
            printf("\n"
                   "########################################################\n"
                   "#           Suma de la matriz A y la matriz B          #\n"
                   "########################################################\n"
                   "\n");
            printf("Calculando la suma de la matriz A[%dx%d]:  con la matriz B%dx%d: \n", rows1, cols1, rows2, cols2);
            if (strcmp(submenu, "Secuencial") == 0)
            {
                // Secuencial
                gettimeofday(&t_start, NULL);
                result_m = init_matrix_threads(A, B, 1, 5);
                printf("\n------------MATRIZ RESULTANTE-----------------\n");
                print_matrix(result_m);

                gettimeofday(&t_end, NULL);

                exec_time = (t_end.tv_sec - t_start.tv_sec) * 1000.0;    // sec to ms
                exec_time += (t_end.tv_usec - t_start.tv_usec) / 1000.0; // us to ms
                printf("\n"
                       "$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n"
                       "      Tiempo de ejecución secuencial: %f ms \n",
                       exec_time);
                printf("$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n");
            }
            else
            {
                // Opción para concurrencia
                // Hilos
                gettimeofday(&t_start, NULL);
                result_m = init_matrix_threads(A, B, hilos, 5);
                printf("\n------------MATRIZ RESULTANTE-----------------\n");
                print_matrix(result_m);

                gettimeofday(&t_end, NULL);

                exec_time = (t_end.tv_sec - t_start.tv_sec) * 1000.0;    // sec to ms
                exec_time += (t_end.tv_usec - t_start.tv_usec) / 1000.0; // us to ms
                printf("\n"
                       "$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n"
                       "      Tiempo de ejecución con hilos: %f ms \n",
                       exec_time);
                printf("$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n");
            }
            free_matrix(A);
            free_matrix(B);
            break;

        case 6:
            printf("\n"
                   "########################################################\n"
                   "#    Producto punto de la matriz A con la matriz B     #\n"
                   "########################################################\n"
                   "\n");
            printf("Calculando el producto punto de la matriz A(fxc): %dx%d con la matriz B(rxs): '%dx%d\n'", rows1, cols1, rows2, cols2);
            if (strcmp(submenu, "Secuencial") == 0)
            {
                // Secuencial
                gettimeofday(&t_start, NULL);
                result_m = init_matrix_threads(A, B, 1, 6);
                printf("------------MATRIZ RESULTANTE-----------------\n");
                print_matrix(result_m);

                gettimeofday(&t_end, NULL);

                exec_time = (t_end.tv_sec - t_start.tv_sec) * 1000.0;    // sec to ms
                exec_time += (t_end.tv_usec - t_start.tv_usec) / 1000.0; // us to ms
                printf("\n"
                       "$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n"
                       "      Tiempo de ejecución secuencial: %f ms \n",
                       exec_time);
                printf("$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n");
            }
            else
            {
                // Opción para concurrencia
                // Hilos
                gettimeofday(&t_start, NULL);
                result_m = init_matrix_threads(A, B, hilos, 6);
                printf("------------MATRIZ RESULTANTE-----------------\n");
                print_matrix(result_m);

                gettimeofday(&t_end, NULL);

                exec_time = (t_end.tv_sec - t_start.tv_sec) * 1000.0;    // sec to ms
                exec_time += (t_end.tv_usec - t_start.tv_usec) / 1000.0; // us to ms
                printf("\n"
                       "$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n"
                       "      Tiempo de ejecución con hilos: %f ms \n",
                       exec_time);
                printf("$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n");
            }
            free_matrix(A);
            free_matrix(B);
            break;

        case 7:
            printf("\n"
                   "########################################################\n"
                   "#        Producto de un escalar con la matriz A        #\n"
                   "########################################################\n"
                   "\n");
            Matrix *aux = create_matrix(A->rows, A->cols);
            copy_matrix(aux, A);

            printf("Calculando el producto de un escalar %f con la matriz A(fxc): '%dx%d\n'", e, rows1, cols1);
            if (strcmp(submenu, "Secuencial") == 0)
            {
                // Secuencial
                gettimeofday(&t_start, NULL);
                result_m = init_matrix_threads_void(A, 1, 7, e);
                printf("------------MATRIZ RESULTANTE-----------------\n");
                print_matrix(result_m);

                gettimeofday(&t_end, NULL);

                exec_time = (t_end.tv_sec - t_start.tv_sec) * 1000.0;    // sec to ms
                exec_time += (t_end.tv_usec - t_start.tv_usec) / 1000.0; // us to ms
                printf("\n"
                       "$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n"
                       "      Tiempo de ejecución secuencial: %f ms \n",
                       exec_time);
                printf("$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n");
            }
            else
            {
                // Opción para concurrencia
                // Hilos
                gettimeofday(&t_start, NULL);
                result_m = init_matrix_threads_void(aux, hilos, 7, e);
                printf("------------MATRIZ RESULTANTE-----------------\n");
                print_matrix(result_m);

                gettimeofday(&t_end, NULL);

                exec_time = (t_end.tv_sec - t_start.tv_sec) * 1000.0;    // sec to ms
                exec_time += (t_end.tv_usec - t_start.tv_usec) / 1000.0; // us to ms
                printf("\n"
                       "$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n"
                       "      Tiempo de ejecución con hilos: %f ms \n",
                       exec_time);
                printf("$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n");
            }
            free_matrix(A);
            free_matrix(aux);
            break;

        case 8:
            printf("\n"
                   "########################################################\n"
                   "#            Normalizando matriz A Opción 1            #\n"
                   "########################################################\n"
                   "\n");
            printf("Calculando la normalización (Opción 1) de las columnas de la matriz A%dx%d: \n", rows1, cols1);
            if (strcmp(submenu, "Secuencial") == 0)
            {
                // Secuencial
                gettimeofday(&t_start, NULL);
                result_m = init_matrix_threads_void(A, 1, 8, e);
                printf("------------MATRIZ RESULTANTE-----------------\n");
                print_matrix(result_m);

                gettimeofday(&t_end, NULL);

                exec_time = (t_end.tv_sec - t_start.tv_sec) * 1000.0;    // sec to ms
                exec_time += (t_end.tv_usec - t_start.tv_usec) / 1000.0; // us to ms
                printf("\n"
                       "$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n"
                       "      Tiempo de ejecución secuencial: %f ms \n",
                       exec_time);
                printf("$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n");
            }
            else
            {
                // Opción para concurrencia
                // Hilos
                gettimeofday(&t_start, NULL);
                result_m = init_matrix_threads_void(A, hilos, 8, e);
                printf("------------MATRIZ RESULTANTE-----------------\n");
                print_matrix(result_m);

                gettimeofday(&t_end, NULL);

                exec_time = (t_end.tv_sec - t_start.tv_sec) * 1000.0;    // sec to ms
                exec_time += (t_end.tv_usec - t_start.tv_usec) / 1000.0; // us to ms
                printf("\n"
                       "$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n"
                       "      Tiempo de ejecución con hilos: %f ms \n",
                       exec_time);
                printf("$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n");
            }
            free_matrix(A);
            break;

        case 9:
            printf("\n"
                   "########################################################\n"
                   "#            Normalizando matriz A Opción 2            #\n"
                   "########################################################\n"
                   "\n");
            printf("Calculando la normalización (Opción 2) de las columnas de la matriz A%dx%d: \n", rows1, cols1);
            if (strcmp(submenu, "Secuencial") == 0)
            {
                // Secuencial
                gettimeofday(&t_start, NULL);
                result_m = init_matrix_threads_void(A, 1, 9, e);
                printf("------------MATRIZ RESULTANTE-----------------\n");
                print_matrix(result_m);

                gettimeofday(&t_end, NULL);

                exec_time = (t_end.tv_sec - t_start.tv_sec) * 1000.0;    // sec to ms
                exec_time += (t_end.tv_usec - t_start.tv_usec) / 1000.0; // us to ms
                printf("\n"
                       "$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n"
                       "      Tiempo de ejecución secuencial: %f ms \n",
                       exec_time);
                printf("$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n");
            }
            else
            {
                // Opción para concurrencia
                // Hilos
                gettimeofday(&t_start, NULL);
                result_m = init_matrix_threads_void(A, hilos, 9, e);
                printf("------------MATRIZ RESULTANTE-----------------\n");
                print_matrix(result_m);

                gettimeofday(&t_end, NULL);

                exec_time = (t_end.tv_sec - t_start.tv_sec) * 1000.0;    // sec to ms
                exec_time += (t_end.tv_usec - t_start.tv_usec) / 1000.0; // us to ms
                printf("\n"
                       "$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n"
                       "      Tiempo de ejecución con hilos: %f ms \n",
                       exec_time);
                printf("$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n");
            }
            free_matrix(A);
            break;

        case 0:
            printf("Saliendo del programa...\n");
            break;

        default:
            printf("Opcion invalida. Por favor, selecciona una opcion valida.\n");
            break;
        }
    } while (opcion != 0);
}

int menu()
{
    // INTRODUCCIÓN AL MENÚ DE OPCIONES
    int opcion;
    char *submenu = malloc(15);

    do
    {
        printf("\n"
               "################################\n"
               "################################\n"
               "#####    MENU PRINCIPAL    #####\n"
               "################################\n"
               "################################\n"
               "\n"
               "\n"
               "================================\n"
               "     SELECCIONE UNA OPCIÓN      \n"
               "================================\n"
               "\n");
        printf("1. Menu para trabajar de forma secuencial \n");
        printf("2. Menu para trabajar con concurrencia \n");
        printf("3. SALIR \n");

        scanf("%d", &opcion);
        if (opcion == 1)
        {
            strcpy(submenu, "Secuencial");
        }
        else
        {
            strcpy(submenu, "Concurrencia");
        }

        switch (opcion)
        {
        case 1:
            printf("\n"
                   "####################################\n"
                   "#            SECUENCIAL            #\n"
                   "####################################\n"
                   "\n");
            selectMenu(submenu);
            break;

        case 2:
            printf("\n"
                   "####################################\n"
                   "#           CONCURRENCIA           #\n"
                   "####################################\n"
                   "\n");
            selectMenu(submenu);
            break;

        case 3:
            printf("Saliendo del programa...\n");
            break;

        default:
            printf("ERROR. Opcion Inválida\n");
        }
    } while (opcion != 3);
    exit(EXIT_SUCCESS);
}

int main(int argc, char *argv[])
{

    menu();

    return 0;
}