import java.util.*;

public class Main {

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        Random random = new Random();

        // Generar arreglo aleatorio de 10 números
        int[] arr = new int[10];
        for (int i = 0; i < arr.length; i++) {
            arr[i] = random.nextInt(100); // Números entre 0 y 99
        }

        System.out.println("Arreglo generado: " + Arrays.toString(arr));

        // Menú principal
        System.out.println("\nOpciones:");
        System.out.println("1. Ordenar con Shell Sort");
        System.out.println("2. Ordenar con Quick Sort");
        System.out.println("3. Ordenar con Arrays.sort()");
        System.out.println("4. Búsqueda binaria");
        System.out.println("5. Búsqueda lineal");
        System.out.print("Ingrese su opción: ");
        int opcion = scanner.nextInt();

        switch (opcion) {
            case 1:
                Ordenamiento.shellSort(arr);
                System.out.println("Arreglo ordenado (Shell Sort): " + Arrays.toString(arr));
                break;
            case 2:
                Ordenamiento.quickSort(arr, 0, arr.length - 1);
                System.out.println("Arreglo ordenado (Quick Sort): " + Arrays.toString(arr));
                break;
            case 3:
                Arrays.sort(arr);
                System.out.println("Arreglo ordenado (Arrays.sort()): " + Arrays.toString(arr));
                break;
            case 4:
                Arrays.sort(arr); // Necesario para búsqueda binaria
                System.out.println("Arreglo ordenado para búsqueda binaria: " + Arrays.toString(arr));
                System.out.print("Ingrese el valor a buscar: ");
                int valorBinario = scanner.nextInt();
                int resultadoBinario = Busquedas.BusquedaBinaria(arr, valorBinario);
                if (resultadoBinario != -1) {
                    System.out.println("Valor encontrado en la posición " + resultadoBinario);
                } else {
                    System.out.println("Valor no encontrado");
                }
                break;
            case 5:
                System.out.print("Ingrese el valor a buscar: ");
                int valorLineal = scanner.nextInt();
                int resultadoLineal = Busquedas.BusquedaLineal(arr, valorLineal);
                if (resultadoLineal != -1) {
                    System.out.println("Valor encontrado en la posición " + resultadoLineal);
                } else {
                    System.out.println("Valor no encontrado");
                }
                break;
            default:
                System.out.println("Opción inválida");
                break;
        }

        scanner.close();
    }
}
