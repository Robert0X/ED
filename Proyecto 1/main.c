#include <stdio.h>
#include <stdlib.h>

// Funcion para mostrar el menu principal
void mostrarMenu() {
    printf("\n--- Menu Principal ---\n");
    printf("1. Ejecutar Codigo 1 (arbolB.c)\n");
    printf("2. Ejecutar Codigo 2 (bin.c)\n");
    printf("3. Ejecutar Codigo 3 (narios.c)\n");
    printf("4. Ejecutar Codigo 4 (binBal.c)\n");
    printf("5. Salir\n");
    printf("Seleccione una opcion: ");
}

// Funcion para ejecutar un archivo dado
void ejecutarArchivo(const char* nombreArchivo) {
    char comando[200];

    // Comando para compilar el archivo
    snprintf(comando, sizeof(comando), "gcc -o ejecutable.exe %s", nombreArchivo);
    if (system(comando) != 0) {
        printf("Error al compilar %s. Asegurese de que el archivo es correcto.\n", nombreArchivo);
        return;
    }

    // Comando para ejecutar el archivo compilado
    if (system("ejecutable.exe") != 0) {
        printf("Error al ejecutar %s.\n", nombreArchivo);
    }

    // Limpieza del ejecutable generado
    system("del ejecutable.exe");
}

int main() {
    int opcion;

    do {
        mostrarMenu();
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                ejecutarArchivo("arbolB.c");
            break;
            case 2:
                ejecutarArchivo("bin.c");
            break;
            case 3:
                ejecutarArchivo("narios.c");
            break;
            case 4:
                ejecutarArchivo("binBal.c");
            break;
            case 5:
                printf("Saliendo del programa...\n");
            break;
            default:
                printf("Opcion invalida. Intente nuevamente.\n");
        }
    } while (opcion != 5);

    return 0;
}