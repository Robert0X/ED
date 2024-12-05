#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct NodoArbolB {
    int n; // Número de claves almacenadas en el nodo
    bool leaf; // Si el nodo es hoja
    int *key; // Claves del nodo
    struct NodoArbolB **child; // Referencias a los hijos
} NodoArbolB;

typedef struct {
    NodoArbolB *root;
    int t; // Grado mínimo
} ArbolB;

// Crear un nodo
NodoArbolB* crearNodo(int t, bool leaf) {
    NodoArbolB *nuevoNodo = (NodoArbolB *)malloc(sizeof(NodoArbolB));
    nuevoNodo->n = 0;
    nuevoNodo->leaf = leaf;
    nuevoNodo->key = (int *)malloc(sizeof(int) * (2 * t + 1)); // Cambiado a 2 * t + 1
    nuevoNodo->child = (NodoArbolB **)malloc(sizeof(NodoArbolB *) * (2 * t + 2)); // Cambiado a 2 * t + 2
    return nuevoNodo;
}

// Crear un árbol B
ArbolB* crearArbolB(int t) {
    ArbolB *arbol = (ArbolB *)malloc(sizeof(ArbolB));
    arbol->t = t;
    arbol->root = crearNodo(t, true);
    return arbol;
}

// Imprimir un nodo
void imprimirNodo(NodoArbolB *nodo) {
    printf("[ ");
    for (int i = 0; i < nodo->n; i++) {
        printf("%d", nodo->key[i]);
        if (i < nodo->n - 1) printf(", ");
    }
    printf(" ]");
}

// Mostrar árbol por niveles
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
        printf("\n");
    }

    free(cola);
}

// Dividir un nodo
void dividirNodo(NodoArbolB *padre, int i, NodoArbolB *hijo, int t) {
    NodoArbolB *nuevoNodo = crearNodo(t, hijo->leaf);
    nuevoNodo->n = t;

    for (int j = 0; j < t; j++) {
        nuevoNodo->key[j] = hijo->key[j + t + 1];
    }

    if (!hijo->leaf) {
        for (int j = 0; j < t + 1; j++) {
            nuevoNodo->child[j] = hijo->child[j + t + 1];
        }
    }

    hijo->n = t;

    for (int j = padre->n; j >= i + 1; j--) {
        padre->child[j + 1] = padre->child[j];
    }
    padre->child[i + 1] = nuevoNodo;

    for (int j = padre->n; j >= i; j--) {
        padre->key[j + 1] = padre->key[j];
    }
    padre->key[i] = hijo->key[t];
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

        if (nodo->child[i]->n == 2 * t + 1) {
            dividirNodo(nodo, i, nodo->child[i], t);

            if (key > nodo->key[i]) {
                i++;
            }
        }
        insertarNoLleno(nodo->child[i], key, t);
    }
}

// Insertar en el árbol B
void insertar(ArbolB *arbol, int key) {
    NodoArbolB *raiz = arbol->root;

    if (raiz->n == 2 * arbol->t + 1) {
        NodoArbolB *nuevoNodo = crearNodo(arbol->t, false);
        arbol->root = nuevoNodo;
        nuevoNodo->child[0] = raiz;

        dividirNodo(nuevoNodo, 0, raiz, arbol->t);
        insertarNoLleno(nuevoNodo, key, arbol->t);
    } else {
        insertarNoLleno(raiz, key, arbol->t);
    }

    printf("\nArbol despues de insertar %d:\n", key);
    mostrarArbol(arbol->root);
}

// Prestar una clave de un hermano
void prestarClave(NodoArbolB *padre, int idx, int t) {
    NodoArbolB *hijo = padre->child[idx];
    NodoArbolB *hermano = padre->child[idx + 1];

    if (hermano->n > t) {
        // Prestar del hermano derecho
        hijo->key[hijo->n] = padre->key[idx];
        padre->key[idx] = hermano->key[0];

        for (int i = 0; i < hermano->n - 1; i++) {
            hermano->key[i] = hermano->key[i + 1];
        }

        if (!hermano->leaf) {
            hijo->child[hijo->n + 1] = hermano->child[0];
            for (int i = 0; i < hermano->n; i++) {
                hermano->child[i] = hermano->child[i + 1];
            }
        }

        hijo->n++;
        hermano->n--;
    } else {
        // Prestar del hermano izquierdo
        hijo->key[hijo->n] = padre->key[idx];
        padre->key[idx] = hermano->key[hermano->n - 1];

        for (int i = hermano->n - 1; i > 0; i--) {
            hermano->key[i] = hermano->key[i - 1];
        }

        if (!hermano->leaf) {
            hijo->child[hijo->n + 1] = hermano->child[hermano->n];
            for (int i = hermano->n; i > 0; i--) {
                hermano->child[i] = hermano->child[i - 1];
            }
        }

        hijo->n++;
        hermano->n--;
    }
}

// Fusionar dos nodos
void fusionar(NodoArbolB *padre, int idx, int t) {
    NodoArbolB *hijo = padre->child[idx];
    NodoArbolB *hermano = padre->child[idx + 1];

    // El primer hijo toma una clave del padre
    hijo->key[hijo->n] = padre->key[idx];
    for (int i = 0; i < hermano->n; i++) {
        hijo->key[i + hijo->n + 1] = hermano->key[i];
    }

    if (!hijo->leaf) {
        for (int i = 0; i <= hermano->n; i++) {
            hijo->child[i + hijo->n + 1] = hermano->child[i];
        }
    }

    // Mover las claves del padre hacia la izquierda
    for (int i = idx + 1; i < padre->n; i++) {
        padre->key[i - 1] = padre->key[i];
    }

    for (int i = idx + 2; i <= padre->n; i++) {
        padre->child[i - 1] = padre->child[i];
    }

    padre->n--;
    hijo->n += hermano->n + 1;

    free(hermano);
}

// Balancear después de eliminar
void balancear(NodoArbolB *padre, int idx, int t) {
    if (padre->child[idx]->n < t) {
        if (idx > 0 && padre->child[idx - 1]->n > t) {
            // Prestar clave desde el hermano izquierdo
            prestarClave(padre, idx - 1, t);
        } else if (idx < padre->n && padre->child[idx + 1]->n > t) {
            // Prestar clave desde el hermano derecho
            prestarClave(padre, idx, t);
        } else {
            // Fusionar con el hermano
            if (idx < padre->n) {
                fusionar(padre, idx, t);
            } else {
                fusionar(padre, idx - 1, t);
            }
        }
    }
}

// Eliminar una clave de un nodo
void eliminarClave(NodoArbolB *nodo, int key, int t) {
    int idx = 0;
    while (idx < nodo->n && nodo->key[idx] < key) {
        idx++;
    }

    if (idx < nodo->n && nodo->key[idx] == key) {
        if (nodo->leaf) {
            // Eliminar en hoja
            for (int i = idx; i < nodo->n - 1; i++) {
                nodo->key[i] = nodo->key[i + 1];
            }
            nodo->n--;
        } else {
            // Eliminar en nodo no hoja
            NodoArbolB *hijo = nodo->child[idx];
            if (hijo->n >= t) {
                // Encontrar el predecesor
                NodoArbolB *predecesor = hijo;
                while (!predecesor->leaf) {
                    predecesor = predecesor->child[predecesor->n];
                }
                nodo->key[idx] = predecesor->key[predecesor->n - 1];
                eliminarClave(hijo, nodo->key[idx], t);
            } else {
                // Encontrar el sucesor
                NodoArbolB *sucesor = nodo->child[idx + 1];
                if (sucesor->n >= t) {
                    nodo->key[idx] = sucesor->key[0];
                    eliminarClave(sucesor, nodo->key[idx], t);
                } else {
                    fusionar(nodo, idx, t);
                    eliminarClave(hijo, key, t);
                }
            }
        }
    } else if (!nodo->leaf) {
        eliminarClave(nodo->child[idx], key, t);
    }

    if (nodo->n < t) {
        balancear(nodo, idx, t);
    }
}

// Eliminar en el árbol B
void eliminar(ArbolB *arbol, int key) {
    if (arbol->root == NULL) {
        printf("El arbol está vacio.\n");
        return;
    }

    eliminarClave(arbol->root, key, arbol->t);

    if (arbol->root->n == 0) {
        NodoArbolB *antiguaRaiz = arbol->root;
        if (arbol->root->leaf) {
            arbol->root = NULL;
        } else {
            arbol->root = arbol->root->child[0];
        }
        free(antiguaRaiz);
    }

    printf("\nArbol después de eliminar %d:\n", key);
    mostrarArbol(arbol->root);
}

int main() {
    int t;
    printf("Ingrese el grado minimo del Arbol B (t >= 2): ");
    scanf("%d", &t);

    ArbolB *arbol = crearArbolB(t);

    int opcion, valor;
    do {
        printf("\n1. Insertar\n2. Eliminar\n3. Mostrar Arbol\n4. Salir\n");
        printf("Opcion: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                printf("Ingrese un valor a insertar: ");
            scanf("%d", &valor);
            insertar(arbol, valor);
            break;
            case 2:
                printf("Ingrese un valor a eliminar: ");
            scanf("%d", &valor);
            eliminar(arbol, valor);
            break;
            case 3:
                mostrarArbol(arbol->root);
            break;
            case 4:
                printf("Saliendo...\n");

            free(arbol);
            break;
            default:
                printf("Opcion invalida.\n");
        }
    } while (opcion != 4);

    return 0;
}