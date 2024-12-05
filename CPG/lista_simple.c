#include <stdio.h>
#include <stdlib.h>
#include "lista_simple.h"

void insertarInicioSimple(NodoSimple **head, int valor)
{
    NodoSimple *nuevo = (NodoSimple *)malloc(sizeof(NodoSimple));
    nuevo->dato = valor;
    nuevo->siguiente = *head;
    *head = nuevo;
}

void insertarFinSimple(NodoSimple **head, int valor)
{
    NodoSimple *nuevo = (NodoSimple *)malloc(sizeof(NodoSimple));
    nuevo->dato = valor;
    nuevo->siguiente = NULL;

    if (*head == NULL)
    {
        *head = nuevo;
    }
    else
    {
        NodoSimple *temp = *head;
        while (temp->siguiente != NULL)
        {
            temp = temp->siguiente;
        }
        temp->siguiente = nuevo;
    }
}

void insertarOrdenadoSimple(NodoSimple **head, int valor)
{
    NodoSimple *nuevo = (NodoSimple *)malloc(sizeof(NodoSimple));
    nuevo->dato = valor;
    NodoSimple *actual = *head, *anterior = NULL;

    while (actual != NULL && actual->dato < valor)
    {
        anterior = actual;
        actual = actual->siguiente;
    }

    nuevo->siguiente = actual;
    if (anterior == NULL)
    {
        *head = nuevo;
    }
    else
    {
        anterior->siguiente = nuevo;
    }
}

void borrarSimple(NodoSimple **head, int valor)
{
    NodoSimple *temp = *head, *prev = NULL;

    while (temp != NULL && temp->dato != valor)
    {
        prev = temp;
        temp = temp->siguiente;
    }

    if (temp == NULL)
        return;

    if (prev == NULL)
    {
        *head = temp->siguiente;
    }
    else
    {
        prev->siguiente = temp->siguiente;
    }
    free(temp);
}

void imprimirSimple(NodoSimple *head)
{
    NodoSimple *temp = head;
    while (temp != NULL)
    {
        printf("%d -> ", temp->dato);
        temp = temp->siguiente;
    }
    printf("NULL\n");
}
