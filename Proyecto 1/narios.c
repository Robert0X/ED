#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Nodo {
    char valor;
    struct Nodo** hijos;
    int numHijos;
} Nodo;

// Crear un nuevo nodo
Nodo* crearNodo(char valor) {
    Nodo* nuevoNodo = (Nodo*)malloc(sizeof(Nodo));
    nuevoNodo->valor = valor;
    nuevoNodo->numHijos = 0;
    nuevoNodo->hijos = NULL;
    return nuevoNodo;
}

// Buscar un nodo hijo con un valor específico
Nodo* buscarHijo(Nodo* nodo, char valor) {
    for (int i = 0; i < nodo->numHijos; i++) {
        if (nodo->hijos[i]->valor == valor) {
            return nodo->hijos[i];
        }
    }
    return NULL;
}

// Agregar un hijo a un nodo
void agregarHijo(Nodo* padre, Nodo* hijo) {
    padre->numHijos++;
    padre->hijos = (Nodo**)realloc(padre->hijos, padre->numHijos * sizeof(Nodo*));
    padre->hijos[padre->numHijos - 1] = hijo;
}

// Insertar una palabra en el árbol
void insertarPalabra(Nodo* raiz, const char* palabra) {
    Nodo* actual = raiz;
    for (int i = 0; palabra[i] != '\0'; i++) {
        char letra = palabra[i];
        Nodo* hijo = buscarHijo(actual, letra);
        if (hijo == NULL) {
            // Crear un nuevo nodo si no existe
            hijo = crearNodo(letra);
            agregarHijo(actual, hijo);
        }
        actual = hijo;
    }
}

// Función para buscar una palabra en el árbol
int buscarPalabra(Nodo* raiz, const char* palabra) {
    Nodo* actual = raiz;
    for (int i = 0; palabra[i] != '\0'; i++) {
        char letra = palabra[i];
        Nodo* hijo = buscarHijo(actual, letra);
        if (hijo == NULL) {
            return 0;  // No se encontró la palabra
        }
        actual = hijo;
    }
    return 1;  // Se encontró la palabra
}

// Imprimir el árbol
void imprimirArbol(Nodo* nodo, int nivel) {
    if (nodo == NULL) return;

    for (int i = 0; i < nivel; i++) {
        printf("    ");
    }
    if (nivel > 0) {
        printf("|-- ");
    }
    printf("%c\n", nodo->valor);

    for (int i = 0; i < nodo->numHijos; i++) {
        imprimirArbol(nodo->hijos[i], nivel + 1);
    }
}

// Liberar la memoria del árbol
void liberarArbol(Nodo* nodo) {
    if (nodo == NULL) return;

    for (int i = 0; i < nodo->numHijos; i++) {
        liberarArbol(nodo->hijos[i]);
    }
    free(nodo->hijos);
    free(nodo);
}

int main() {
    Nodo* raiz = crearNodo('\0');  // Raíz vacía del árbol
    int opcion;

    do {
        printf("\n--- Arbol N-ario para palabras ---\n");
        printf("1. Insertar palabra\n");
        printf("2. Mostrar arbol\n");
        printf("3. Buscar palabra\n");
        printf("4. Salir\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1: {
                char palabra[100];
                printf("Ingrese una palabra: ");
                scanf("%s", palabra);
                insertarPalabra(raiz, palabra);
                printf("\nPalabra '%s' insertada en el arbol.\n", palabra);
                break;
            }
            case 2:
                printf("\nRepresentacion grafica del arbol:\n");
                imprimirArbol(raiz, 0);
                break;
            case 3: {
                char palabra[100];
                printf("Ingrese la palabra a buscar: ");
                scanf("%s", palabra);
                if (buscarPalabra(raiz, palabra)) {
                    printf("La palabra '%s' se encontro en el arbol.\n", palabra);
                } else {
                    printf("La palabra '%s' no se encontro en el arbol.\n", palabra);
                }
                break;
            }
            case 4:
                printf("Saliendo del programa...\n");
                liberarArbol(raiz);
                break;
            default:
                printf("Opcion invalida. Intente nuevamente.\n");
        }
    } while (opcion != 4);

    return 0;
}
