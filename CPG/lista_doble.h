#ifndef LISTA_DOBLE_H
#define LISTA_DOBLE_H

typedef struct NodoDoble
{
    int dato;
    struct NodoDoble *anterior;
    struct NodoDoble *siguiente;
} NodoDoble;

void insertarInicioDoble(NodoDoble **head, int valor);
void insertarFinDoble(NodoDoble **head, int valor);
void insertarOrdenadoDoble(NodoDoble **head, int valor);
void borrarDoble(NodoDoble **head, int valor);
void imprimirDoble(NodoDoble *head);

#endif
