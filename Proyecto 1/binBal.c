#include <stdio.h>
#include <stdlib.h>

// Definicion de un nodo del arbol AVL
typedef struct Nodo {
    int dato;
    int altura;
    struct Nodo* izquierda;
    struct Nodo* derecha;
} Nodo;

// Funcion para obtener la altura de un nodo
int obtenerAltura(Nodo* nodo) {
    return nodo ? nodo->altura : 0;
}

// Funcion para calcular el factor de balance de un nodo
int obtenerFactorBalance(Nodo* nodo) {
    return nodo ? obtenerAltura(nodo->izquierda) - obtenerAltura(nodo->derecha) : 0;
}

// Funcion para crear un nuevo nodo
Nodo* crearNodo(int dato) {
    Nodo* nuevoNodo = (Nodo*)malloc(sizeof(Nodo));
    nuevoNodo->dato = dato;
    nuevoNodo->altura = 1; // Un nuevo nodo tiene altura 1
    nuevoNodo->izquierda = NULL;
    nuevoNodo->derecha = NULL;
    return nuevoNodo;
}

// Rotacion derecha
Nodo* rotacionDerecha(Nodo* y) {
    Nodo* x = y->izquierda;
    Nodo* T = x->derecha;

    x->derecha = y;
    y->izquierda = T;

    y->altura = 1 + (obtenerAltura(y->izquierda) > obtenerAltura(y->derecha) ? obtenerAltura(y->izquierda) : obtenerAltura(y->derecha));
    x->altura = 1 + (obtenerAltura(x->izquierda) > obtenerAltura(x->derecha) ? obtenerAltura(x->izquierda) : obtenerAltura(x->derecha));

    return x;
}

// Rotacion izquierda
Nodo* rotacionIzquierda(Nodo* x) {
    Nodo* y = x->derecha;
    Nodo* T = y->izquierda;

    y->izquierda = x;
    x->derecha = T;

    x->altura = 1 + (obtenerAltura(x->izquierda) > obtenerAltura(x->derecha) ? obtenerAltura(x->izquierda) : obtenerAltura(x->derecha));
    y->altura = 1 + (obtenerAltura(y->izquierda) > obtenerAltura(y->derecha) ? obtenerAltura(y->izquierda) : obtenerAltura(y->derecha));

    return y;
}

// Funcion para balancear el arbol
Nodo* balancear(Nodo* nodo) {
    int balance = obtenerFactorBalance(nodo);

    // Caso de desbalanceo a la izquierda
    if (balance > 1 && obtenerFactorBalance(nodo->izquierda) >= 0) {
        return rotacionDerecha(nodo);
    }

    // Caso de desbalanceo a la derecha
    if (balance < -1 && obtenerFactorBalance(nodo->derecha) <= 0) {
        return rotacionIzquierda(nodo);
    }

    // Caso de desbalanceo izquierdo-derecho
    if (balance > 1 && obtenerFactorBalance(nodo->izquierda) < 0) {
        nodo->izquierda = rotacionIzquierda(nodo->izquierda);
        return rotacionDerecha(nodo);
    }

    // Caso de desbalanceo derecho-izquierdo
    if (balance < -1 && obtenerFactorBalance(nodo->derecha) > 0) {
        nodo->derecha = rotacionDerecha(nodo->derecha);
        return rotacionIzquierda(nodo);
    }

    return nodo;
}

// Insercion en el arbol AVL
Nodo* insertarNodo(Nodo* nodo, int dato) {
    if (nodo == NULL) {
        return crearNodo(dato);
    }

    if (dato < nodo->dato) {
        nodo->izquierda = insertarNodo(nodo->izquierda, dato);
    } else if (dato > nodo->dato) {
        nodo->derecha = insertarNodo(nodo->derecha, dato);
    } else {
        return nodo;  // No permitimos duplicados
    }

    // Actualizamos la altura del nodo
    nodo->altura = 1 + (obtenerAltura(nodo->izquierda) > obtenerAltura(nodo->derecha) ? obtenerAltura(nodo->izquierda) : obtenerAltura(nodo->derecha));

    // Balanceamos el arbol
    return balancear(nodo);
}

// Funcion para encontrar el nodo con el valor mas pequeno en el arbol
Nodo* obtenerMinimo(Nodo* nodo) {
    Nodo* actual = nodo;
    while (actual && actual->izquierda != NULL) {
        actual = actual->izquierda;
    }
    return actual;
}

// Eliminar un nodo en el arbol AVL
Nodo* eliminarNodo(Nodo* raiz, int dato) {
    if (raiz == NULL) {
        return raiz;
    }

    if (dato < raiz->dato) {
        raiz->izquierda = eliminarNodo(raiz->izquierda, dato);
    } else if (dato > raiz->dato) {
        raiz->derecha = eliminarNodo(raiz->derecha, dato);
    } else {
        if (raiz->izquierda == NULL) {
            Nodo* temp = raiz->derecha;
            free(raiz);
            return temp;
        } else if (raiz->derecha == NULL) {
            Nodo* temp = raiz->izquierda;
            free(raiz);
            return temp;
        }

        Nodo* temp = obtenerMinimo(raiz->derecha);
        raiz->dato = temp->dato;
        raiz->derecha = eliminarNodo(raiz->derecha, temp->dato);
    }

    if (raiz == NULL) {
        return raiz;
    }

    raiz->altura = 1 + (obtenerAltura(raiz->izquierda) > obtenerAltura(raiz->derecha) ? obtenerAltura(raiz->izquierda) : obtenerAltura(raiz->derecha));
    return balancear(raiz);
}

// Funcion para imprimir el arbol de manera visual
void imprimirArbol(Nodo* raiz, int espacio) {
    if (raiz == NULL) {
        return;
    }

    const int ESPACIO_ENTRE_NIVELES = 5;
    espacio += ESPACIO_ENTRE_NIVELES;

    imprimirArbol(raiz->derecha, espacio);

    printf("\n");
    for (int i = ESPACIO_ENTRE_NIVELES; i < espacio; i++) {
        printf(" ");
    }
    printf("%d\n", raiz->dato);

    imprimirArbol(raiz->izquierda, espacio);
}

// Liberar memoria del arbol
void liberarArbol(Nodo* raiz) {
    if (raiz != NULL) {
        liberarArbol(raiz->izquierda);
        liberarArbol(raiz->derecha);
        free(raiz);
    }
}

// Menu
void mostrarMenu() {
    printf("\n--- Menu de Arbol AVL ---\n");
    printf("1. Insertar un nodo\n");
    printf("2. Eliminar un nodo\n");
    printf("3. Liberar el arbol y salir\n");
    printf("Seleccione una opcion: ");
}

// Programa principal
int main() {
    Nodo* raiz = NULL;
    int opcion, dato;

    do {
        mostrarMenu();
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                printf("Ingrese un numero para insertar en el arbol: ");
                scanf("%d", &dato);
                raiz = insertarNodo(raiz, dato);
                printf("Numero %d insertado correctamente.\n", dato);
                printf("\n--- Arbol AVL (vista visual actualizada) ---\n");
                imprimirArbol(raiz, 0);
                break;

            case 2:
                printf("Ingrese el numero para eliminar del arbol: ");
                scanf("%d", &dato);
                raiz = eliminarNodo(raiz, dato);
                printf("Numero %d eliminado correctamente.\n", dato);
                printf("\n--- Arbol AVL (vista visual actualizada) ---\n");
                imprimirArbol(raiz, 0);
                break;

            case 3:
                liberarArbol(raiz);
                raiz = NULL;
                printf("Memoria del arbol liberada. Saliendo...\n");
                break;

            default:
                printf("Opcion no valida. Intente de nuevo.\n");
                break;
        }
    } while (opcion != 3);

    return 0;
}