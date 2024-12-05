#ifndef LISTA_DOBLE_CIRCULAR_H
#define LISTA_DOBLE_CIRCULAR_H

typedef struct NodoDobleCircular
{
    int valor;
    struct NodoDobleCircular *anterior;
    struct NodoDobleCircular *siguiente;
} NodoDobleCircular;

void insertarInicioDobleCircular(NodoDobleCircular **head, int valor);
void insertarFinDobleCircular(NodoDobleCircular **head, int valor);
void insertarOrdenadoDobleCircular(NodoDobleCircular **head, int valor);
void borrarDobleCircular(NodoDobleCircular **head, int valor);
void imprimirDobleCircular(NodoDobleCircular *head);

#endif
