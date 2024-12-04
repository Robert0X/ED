#include <stdio.h>
#include <stdlib.h>

// Definicion de un nodo del arbol binario de busqueda
typedef struct Nodo {
    int dato;
    struct Nodo* izquierda;
    struct Nodo* derecha;
} Nodo;

// Funcion para crear un nuevo nodo
Nodo* crearNodo(int dato) {
    Nodo* nuevoNodo = (Nodo*)malloc(sizeof(Nodo));
    nuevoNodo->dato = dato;
    nuevoNodo->izquierda = NULL;
    nuevoNodo->derecha = NULL;
    return nuevoNodo;
}

// Insercion en el arbol binario de busqueda (sin balanceo)
Nodo* insertarNodo(Nodo* nodo, int dato) {
    if (nodo == NULL) {
        return crearNodo(dato);
    }

    if (dato < nodo->dato) {
        nodo->izquierda = insertarNodo(nodo->izquierda, dato);
    } else if (dato > nodo->dato) {
        nodo->derecha = insertarNodo(nodo->derecha, dato);
    }

    return nodo;
}

// Funcion para encontrar el nodo con el valor mas pequeno en el arbol
Nodo* obtenerMinimo(Nodo* nodo) {
    Nodo* actual = nodo;
    while (actual && actual->izquierda != NULL) {
        actual = actual->izquierda;
    }
    return actual;
}

// Eliminar un nodo en el arbol binario de busqueda (sin balanceo)
Nodo* eliminarNodo(Nodo* raiz, int dato) {
    if (raiz == NULL) {
        return raiz;  // Si el arbol esta vacio, no hay nada que eliminar
    }

    // Encontramos el nodo que queremos eliminar
    if (dato < raiz->dato) {
        raiz->izquierda = eliminarNodo(raiz->izquierda, dato);
    } else if (dato > raiz->dato) {
        raiz->derecha = eliminarNodo(raiz->derecha, dato);
    } else {
        // Nodo con un solo hijo o sin hijos
        if (raiz->izquierda == NULL) {
            Nodo* temp = raiz->derecha;
            free(raiz);
            return temp;
        } else if (raiz->derecha == NULL) {
            Nodo* temp = raiz->izquierda;
            free(raiz);
            return temp;
        }

        // Nodo con dos hijos: obtenemos el sucesor inorden (minimo en el subarbol derecho)
        Nodo* temp = obtenerMinimo(raiz->derecha);

        // Reemplazamos el nodo con el sucesor inorden
        raiz->dato = temp->dato;

        // Eliminamos el sucesor inorden
        raiz->derecha = eliminarNodo(raiz->derecha, temp->dato);
    }

    return raiz;
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
    printf("\n--- Menu de Arbol Binario de Busqueda ---\n");
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
                printf("\n--- Arbol Binario de Busqueda (vista visual actualizada) ---\n");
                imprimirArbol(raiz, 0);
                break;

            case 2:
                printf("Ingrese el numero para eliminar del arbol: ");
                scanf("%d", &dato);
                raiz = eliminarNodo(raiz, dato);
                printf("Numero %d eliminado correctamente.\n", dato);
                printf("\n--- Arbol Binario de Busqueda (vista visual actualizada) ---\n");
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