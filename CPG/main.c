#include <stdio.h>
#include <stdlib.h>
#include "lista_simple.h"
#include "lista_doble.h"
#include "lista_doble_circular.h"

void menuListaSimple(NodoSimple **listaSimple);
void menuListaDoble(NodoDoble **listaDoble);
void menuListaDobleCircular(NodoDobleCircular **listaDobleCircular);

int main()
{
    NodoSimple *listaSimple = NULL;
    NodoDoble *listaDoble = NULL;
    NodoDobleCircular *listaDobleCircular = NULL;
    int opcion;

    while (1)
    {
        printf("\n--- Menu Principal ---\n");
        printf("1. Lista Simplemente Ligada\n");
        printf("2. Lista Doblemente Ligada\n");
        printf("3. Lista Doblemente Ligada Circular\n");
        printf("4. Salir\n");
        printf("Seleccione el tipo de lista: ");
        scanf("%d", &opcion);

        switch (opcion)
        {
        case 1:
            menuListaSimple(&listaSimple);
            break;
        case 2:
            menuListaDoble(&listaDoble);
            break;
        case 3:
            menuListaDobleCircular(&listaDobleCircular);
            break;
        case 4:
            printf("Saliendo del programa...\n");
            return 0;
        default:
            printf("Opcion no valida. Intente de nuevo.\n");
        }
    }
    return 0;
}

void menuListaSimple(NodoSimple **listaSimple)
{
    int opcion, valor;
    while (1)
    {
        printf("\n--- Lista Simplemente Ligada ---\n");
        printf("1. Insertar al Inicio\n");
        printf("2. Insertar al Final\n");
        printf("3. Insertar Ordenado\n");
        printf("4. Borrar\n");
        printf("5. Imprimir Lista\n");
        printf("6. Volver al Menu Principal\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);

        switch (opcion)
        {
        case 1:
            printf("Ingrese un valor: ");
            scanf("%d", &valor);
            insertarInicioSimple(listaSimple, valor);
            break;
        case 2:
            printf("Ingrese un valor: ");
            scanf("%d", &valor);
            insertarFinSimple(listaSimple, valor);
            break;
        case 3:
            printf("Ingrese un valor: ");
            scanf("%d", &valor);
            insertarOrdenadoSimple(listaSimple, valor);
            break;
        case 4:
            printf("Ingrese un valor a borrar: ");
            scanf("%d", &valor);
            borrarSimple(listaSimple, valor);
            break;
        case 5:
            imprimirSimple(*listaSimple);
            break;
        case 6:
            return;
        default:
            printf("Opcion no valida.\n");
        }
    }
}

void menuListaDoble(NodoDoble **listaDoble)
{
    int opcion, valor;
    while (1)
    {
        printf("\n--- Lista Doblemente Ligada ---\n");
        printf("1. Insertar al Inicio\n");
        printf("2. Insertar al Final\n");
        printf("3. Insertar Ordenado\n");
        printf("4. Borrar\n");
        printf("5. Imprimir Lista\n");
        printf("6. Volver al Menu Principal\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);

        switch (opcion)
        {
        case 1:
            printf("Ingrese un valor: ");
            scanf("%d", &valor);
            insertarInicioDoble(listaDoble, valor);
            break;
        case 2:
            printf("Ingrese un valor: ");
            scanf("%d", &valor);
            insertarFinDoble(listaDoble, valor);
            break;
        case 3:
            printf("Ingrese un valor: ");
            scanf("%d", &valor);
            insertarOrdenadoDoble(listaDoble, valor);
            break;
        case 4:
            printf("Ingrese un valor a borrar: ");
            scanf("%d", &valor);
            borrarDoble(listaDoble, valor);
            break;
        case 5:
            imprimirDoble(*listaDoble);
            break;
        case 6:
            return;
        default:
            printf("Opcion no valida.\n");
        }
    }
}

void menuListaDobleCircular(NodoDobleCircular **listaDobleCircular)
{
    int opcion, valor;
    while (1)
    {
        printf("\n--- Lista Doblemente Ligada Circular ---\n");
        printf("1. Insertar al Inicio\n");
        printf("2. Insertar al Final\n");
        printf("3. Insertar Ordenado\n");
        printf("4. Borrar\n");
        printf("5. Imprimir Lista\n");
        printf("6. Volver al Menu Principal\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);

        switch (opcion)
        {
        case 1:
            printf("Ingrese un valor: ");
            scanf("%d", &valor);
            insertarInicioDobleCircular(listaDobleCircular, valor);
            break;
        case 2:
            printf("Ingrese un valor: ");
            scanf("%d", &valor);
            insertarFinDobleCircular(listaDobleCircular, valor);
            break;
        case 3:
            printf("Ingrese un valor: ");
            scanf("%d", &valor);
            insertarOrdenadoDobleCircular(listaDobleCircular, valor);
            break;
        case 4:
            printf("Ingrese un valor a borrar: ");
            scanf("%d", &valor);
            borrarDobleCircular(listaDobleCircular, valor);
            break;
        case 5:
            imprimirDobleCircular(*listaDobleCircular);
            break;
        case 6:
            return;
        default:
            printf("Opcion no valida.\n");
        }
    }
}
