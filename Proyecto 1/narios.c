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
    padre->hijos = (Nodo*)realloc(padre->hijos, padre->numHijos * sizeof(Nodo));
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

// Imprimir el árbol
void imprimirArbol(Nodo* nodo, int nivel) {
    if (nodo == NULL) return;

    for (int i = 0; i < nivel; i++) {
        printf("       ");
    }
    if (nivel > 0) {
        printf("|--- ");
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
        printf("\n--- Árbol N-ario para palabras ---\n");
        printf("1. Insertar palabra\n");
        printf("2. Mostrar árbol\n");
        printf("3. Salir\n");
        printf("Seleccione una opción: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1: {
                char palabra[100];
                printf("Ingrese una palabra: ");
                scanf("%s", palabra);
                insertarPalabra(raiz, palabra);
                printf("Palabra '%s' insertada en el árbol.\n", palabra);
                break;
            }
            case 2:
                printf("\nRepresentación gráfica del árbol:\n");
                imprimirArbol(raiz, 0);
                break;
            case 3:
                printf("Saliendo del programa...\n");
                liberarArbol(raiz);
                break;
            default:
                printf("Opción inválida. Intente nuevamente.\n");
        }
    } while (opcion != 3);

    return 0;
}