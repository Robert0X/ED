#ifndef LISTA_SIMPLE_H
#define LISTA_SIMPLE_H

typedef struct NodoSimple
{
    int dato;
    struct NodoSimple *siguiente;
} NodoSimple;

void insertarInicioSimple(NodoSimple **head, int valor);
void insertarFinSimple(NodoSimple **head, int valor);
void insertarOrdenadoSimple(NodoSimple **head, int valor);
void borrarSimple(NodoSimple **head, int valor);
void imprimirSimple(NodoSimple *head);

#endif
