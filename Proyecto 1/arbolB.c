#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct NodoArbolB {
    int n; // Numero de claves almacenadas en el nodo
    bool leaf; // Si el nodo es hoja
    int *key; // Claves del nodo
    struct NodoArbolB **child; // Referencias a los hijos
} NodoArbolB;

typedef struct {
    NodoArbolB *root;
    int t; // Grado minimo
} ArbolB;

// Funcion para crear un nodo
NodoArbolB* crearNodo(int t, bool leaf) {
    NodoArbolB *nuevoNodo = (NodoArbolB *)malloc(sizeof(NodoArbolB));
    nuevoNodo->n = 0;
    nuevoNodo->leaf = leaf;
    nuevoNodo->key = (int *)malloc(sizeof(int) * (2 * t - 1));
    nuevoNodo->child = (NodoArbolB **)malloc(sizeof(NodoArbolB *) * (2 * t));
    return nuevoNodo;
}

// Funcion para inicializar un Arbol B
ArbolB* crearArbolB(int t) {
    ArbolB *arbol = (ArbolB *)malloc(sizeof(ArbolB));
    arbol->t = t;
    arbol->root = crearNodo(t, true);
    return arbol;
}

// Imprimir un nodo
void imprimirNodo(NodoArbolB *nodo) {
    printf("[");
    for (int i = 0; i < nodo->n; i++) {
        printf("%d", nodo->key[i]);
        if (i < nodo->n - 1) printf(" | ");
    }
    printf("]");
}

// Imprimir el arbol por niveles
void mostrarArbol(NodoArbolB *root) {
    if (root == NULL) {
        printf("El arbol esta vacio.\n");
        return;
    }

    NodoArbolB **cola = (NodoArbolB **)malloc(sizeof(NodoArbolB *) * 1000);
    int inicio = 0, fin = 0;

    cola[fin++] = root;

    while (inicio < fin) {
        int nivelSize = fin - inicio;

        for (int i = 0; i < nivelSize; i++) {
            NodoArbolB *actual = cola[inicio++];

            imprimirNodo(actual);
            printf(" ");

            if (!actual->leaf) {
                for (int j = 0; j <= actual->n; j++) {
                    if (actual->child[j] != NULL) {
                        cola[fin++] = actual->child[j];
                    }
                }
            }
        }
        printf("\n"); // Salto de linea al final del nivel
    }

    free(cola);
}

// Dividir un nodo
void dividirNodo(NodoArbolB *padre, int i, NodoArbolB *hijo, int t) {
    NodoArbolB *nuevoNodo = crearNodo(t, hijo->leaf);
    nuevoNodo->n = t - 1;

    for (int j = 0; j < t - 1; j++) {
        nuevoNodo->key[j] = hijo->key[j + t];
    }

    if (!hijo->leaf) {
        for (int j = 0; j < t; j++) {
            nuevoNodo->child[j] = hijo->child[j + t];
        }
    }

    hijo->n = t - 1;

    for (int j = padre->n; j >= i + 1; j--) {
        padre->child[j + 1] = padre->child[j];
    }
    padre->child[i + 1] = nuevoNodo;

    for (int j = padre->n; j >= i; j--) {
        padre->key[j + 1] = padre->key[j];
    }
    padre->key[i] = hijo->key[t - 1];
    padre->n++;
}

// Insertar en un nodo no lleno
void insertarNoLleno(NodoArbolB *nodo, int key, int t) {
    int i = nodo->n - 1;

    if (nodo->leaf) {
        while (i >= 0 && nodo->key[i] > key) {
            nodo->key[i + 1] = nodo->key[i];
            i--;
        }
        nodo->key[i + 1] = key;
        nodo->n++;
    } else {
        while (i >= 0 && nodo->key[i] > key) {
            i--;
        }
        i++;

        if (nodo->child[i]->n == 2 * t - 1) {
            dividirNodo(nodo, i, nodo->child[i], t);

            if (key > nodo->key[i]) {
                i++;
            }
        }
        insertarNoLleno(nodo->child[i], key, t);
    }
}

// Insertar en el arbol B
void insertar(ArbolB *arbol, int key) {
    NodoArbolB *raiz = arbol->root;

    if (raiz->n == 2 * arbol->t - 1) {
        NodoArbolB *nuevoNodo = crearNodo(arbol->t, false);
        arbol->root = nuevoNodo;
        nuevoNodo->child[0] = raiz;

        dividirNodo(nuevoNodo, 0, raiz, arbol->t);
        insertarNoLleno(nuevoNodo, key, arbol->t);
    } else {
        insertarNoLleno(raiz, key, arbol->t);
    }
}

// Buscar el valor maximo
int buscarMaximo(NodoArbolB *nodo) {
    while (!nodo->leaf) {
        nodo = nodo->child[nodo->n];
    }
    return nodo->key[nodo->n - 1];
}

// Liberar memoria del nodo
void liberarNodo(NodoArbolB *nodo) {
    free(nodo->key);
    free(nodo->child);
    free(nodo);
}

// Liberar memoria del arbol
void liberarArbol(NodoArbolB *nodo) {
    if (nodo == NULL) return;

    if (!nodo->leaf) {
        for (int i = 0; i <= nodo->n; i++) {
            liberarArbol(nodo->child[i]);
        }
    }
    liberarNodo(nodo);
}

int main() {
    int t;
    printf("Ingrese el grado minimo del Arbol B (t >= 2): ");
    scanf("%d", &t);

    ArbolB *arbol = crearArbolB(t);

    int opcion, valor;
    do {
        printf("\n1. Insertar\n2. Mostrar Arbol\n3. Buscar maximo\n4. Salir\n");
        printf("Opcion: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                printf("Ingrese un valor a insertar: ");
                scanf("%d", &valor);
                insertar(arbol, valor);
                break;
            case 2:
                mostrarArbol(arbol->root);
                break;
            case 3:
                printf("El valor maximo es: %d\n", buscarMaximo(arbol->root));
                break;
            case 4:
                printf("Saliendo...\n");
                liberarArbol(arbol->root);
                free(arbol);
                break;
            default:
                printf("Opcion invalida.\n");
        }
    } while (opcion != 4);

    return 0;
}