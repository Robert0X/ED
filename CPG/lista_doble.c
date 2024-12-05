#include <stdio.h>
#include <stdlib.h>
#include "lista_doble.h"

void insertarInicioDoble(NodoDoble **head, int valor)
{
    NodoDoble *nuevo = (NodoDoble *)malloc(sizeof(NodoDoble));
    nuevo->dato = valor;
    nuevo->anterior = NULL;
    nuevo->siguiente = *head;

    if (*head != NULL)
    {
        (*head)->anterior = nuevo;
    }
    *head = nuevo;
}

void insertarFinDoble(NodoDoble **head, int valor)
{
    NodoDoble *nuevo = (NodoDoble *)malloc(sizeof(NodoDoble));
    nuevo->dato = valor;
    nuevo->siguiente = NULL;

    if (*head == NULL)
    {
        nuevo->anterior = NULL;
        *head = nuevo;
    }
    else
    {
        NodoDoble *temp = *head;
        while (temp->siguiente != NULL)
        {
            temp = temp->siguiente;
        }
        temp->siguiente = nuevo;
        nuevo->anterior = temp;
    }
}

void insertarOrdenadoDoble(NodoDoble **head, int valor)
{
    NodoDoble *nuevo = (NodoDoble *)malloc(sizeof(NodoDoble));
    nuevo->dato = valor;
    NodoDoble *actual = *head;

    while (actual != NULL && actual->dato < valor)
    {
        actual = actual->siguiente;
    }

    if (actual == *head)
    {
        nuevo->siguiente = *head;
        nuevo->anterior = NULL;
        if (*head != NULL)
        {
            (*head)->anterior = nuevo;
        }
        *head = nuevo;
    }
    else
    {
        nuevo->siguiente = actual;
        nuevo->anterior = actual->anterior;
        if (actual->anterior != NULL)
        {
            actual->anterior->siguiente = nuevo;
        }
        if (actual != NULL)
        {
            actual->anterior = nuevo;
        }
    }
}

void borrarDoble(NodoDoble **head, int valor)
{
    NodoDoble *temp = *head;

    while (temp != NULL && temp->dato != valor)
    {
        temp = temp->siguiente;
    }

    if (temp == NULL)
        return;

    if (temp->anterior != NULL)
    {
        temp->anterior->siguiente = temp->siguiente;
    }
    else
    {
        *head = temp->siguiente;
    }

    if (temp->siguiente != NULL)
    {
        temp->siguiente->anterior = temp->anterior;
    }
    free(temp);
}

void imprimirDoble(NodoDoble *head)
{
    NodoDoble *temp = head;
    while (temp != NULL)
    {
        printf("%d <-> ", temp->dato);
        temp = temp->siguiente;
    }
    printf("NULL\n");
}
