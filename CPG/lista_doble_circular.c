#include <stdio.h>
#include <stdlib.h>
#include "lista_doble_circular.h"

NodoDobleCircular *crearNodo(int valor)
{
    NodoDobleCircular *nuevoNodo = (NodoDobleCircular *)malloc(sizeof(NodoDobleCircular));
    nuevoNodo->valor = valor;
    nuevoNodo->siguiente = nuevoNodo->anterior = nuevoNodo;
    return nuevoNodo;
}

void insertarInicioDobleCircular(NodoDobleCircular **head, int valor)
{
    NodoDobleCircular *nuevoNodo = crearNodo(valor);
    if (*head == NULL)
    {
        *head = nuevoNodo;
    }
    else
    {
        NodoDobleCircular *ultimo = (*head)->anterior;
        nuevoNodo->siguiente = *head;
        nuevoNodo->anterior = ultimo;
        ultimo->siguiente = nuevoNodo;
        (*head)->anterior = nuevoNodo;
        *head = nuevoNodo;
    }
}

void insertarFinDobleCircular(NodoDobleCircular **head, int valor)
{
    NodoDobleCircular *nuevoNodo = crearNodo(valor);
    if (*head == NULL)
    {
        *head = nuevoNodo;
    }
    else
    {
        NodoDobleCircular *ultimo = (*head)->anterior;
        nuevoNodo->siguiente = *head;
        nuevoNodo->anterior = ultimo;
        ultimo->siguiente = nuevoNodo;
        (*head)->anterior = nuevoNodo;
    }
}

void insertarOrdenadoDobleCircular(NodoDobleCircular **head, int valor)
{
    NodoDobleCircular *nuevoNodo = crearNodo(valor);
    if (*head == NULL || (*head)->valor >= valor)
    {
        insertarInicioDobleCircular(head, valor);
    }
    else
    {
        NodoDobleCircular *actual = *head;
        while (actual->siguiente != *head && actual->siguiente->valor < valor)
        {
            actual = actual->siguiente;
        }
        nuevoNodo->siguiente = actual->siguiente;
        nuevoNodo->anterior = actual;
        actual->siguiente->anterior = nuevoNodo;
        actual->siguiente = nuevoNodo;
    }
}

void borrarDobleCircular(NodoDobleCircular **head, int valor)
{
    if (*head == NULL)
    {
        printf("La lista esta vacía.\n");
        return;
    }

    NodoDobleCircular *actual = *head;
    do
    {
        if (actual->valor == valor)
        {
            if (actual->siguiente == actual)
            { // Si es el único nodo
                free(actual);
                *head = NULL;
            }
            else
            {
                actual->anterior->siguiente = actual->siguiente;
                actual->siguiente->anterior = actual->anterior;
                if (actual == *head)
                    *head = actual->siguiente;
                free(actual);
            }
            printf("Valor %d borrado.\n", valor);
            return;
        }
        actual = actual->siguiente;
    } while (actual != *head);
    printf("Valor %d no encontrado.\n", valor);
}

void imprimirDobleCircular(NodoDobleCircular *head)
{
    if (head == NULL)
    {
        printf("La lista esta vacía.\n");
        return;
    }

    NodoDobleCircular *actual = head;
    printf("Lista circular doblemente ligada: ");
    do
    {
        printf("%d ", actual->valor);
        actual = actual->siguiente;
    } while (actual != head);
    printf("\n");
}
