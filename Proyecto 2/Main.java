import java.util.*;

public class Main {
    private static Scanner cin = new Scanner(System.in);
    private static Random random = new Random();

    static int[] Aleatoreo() {

        int[] arr = new int[10];
        for (int i = 0; i < arr.length; i++) {
            arr[i] = random.nextInt(10);
        }

        return arr;
    }

    static int[] Leer() {
        System.out.println("Dame la cantidad de numeros del arreglo:");
        int n = cin.nextInt();

        int arr[] = new int[n];
        for (int i = 0; i < n; i++) {
            arr[i] = cin.nextInt();
        }

        return arr;
    }

    static void ImprimirBonito(int arr[]) {
        for (int i : arr) {
            System.out.print(i + " ");
        }
        System.out.println();
        for (int i = 0; i < arr.length; i++) {
            System.out.print(i + " ");
        }
        System.out.println();
    }

    public static void main(String[] args) {

        System.out.println("1)Arreglo aleatoreo de 10 digito \n2)Uno de N espacios dado por el usuario");
        int op = cin.nextInt();

        int arraux[];
        if (op == 1) {
            arraux = Aleatoreo();
        } else {
            arraux = Leer();
        }

        boolean band = true;

        do {
            int arr[] = Arrays.copyOf(arraux, arraux.length);

            System.out.println("\nArreglo actual: ");
            ImprimirBonito(arr);

            System.out.println("\nOpciones:");
            System.out.println("1. Ordenar con Shell Sort");
            System.out.println("2. Ordenar con Quick Sort");
            System.out.println("3. Ordenar con Arrays.sort()");
            System.out.println("4. Busqueda binaria");
            System.out.println("5. Busqueda lineal");
            System.out.println("SALIR Cualquier otro");
            System.out.print("Ingrese su opción: ");
            int opcion = cin.nextInt();

            switch (opcion) {
                case 1:
                    Ordenamiento.shellSort(arr);
                    System.out.println("\nArreglo ordenado (Shell Sort): " + Arrays.toString(arr));
                    break;
                case 2:
                    Ordenamiento.quickSort(arr, 0, arr.length - 1);
                    System.out.println("\nArreglo ordenado (Quick Sort): " + Arrays.toString(arr));
                    break;
                case 3:
                    Arrays.sort(arr);
                    System.out.println("\nArreglo ordenado (Arrays.sort()): " + Arrays.toString(arr));
                    break;
                case 4:
                    Arrays.sort(arr); // Necesario para busqueda binaria
                    System.out.println("\nArreglo ordenado para busqueda binaria: ");
                    ImprimirBonito(arr);

                    System.out.print("\nIngrese el valor a buscar: ");
                    int valorBinario = cin.nextInt();
                    int resultadoBinario = Busquedas.BusquedaBinaria(arr, valorBinario);
                    if (resultadoBinario != -1) {
                        System.out.println("Valor encontrado en la posición " + resultadoBinario);
                    } else {
                        System.out.println("Valor no encontrado");
                    }
                    break;
                case 5:
                    ImprimirBonito(arr);
                    System.out.print("\nIngrese el valor a buscar: ");
                    int valorLineal = cin.nextInt();
                    int resultadoLineal = Busquedas.BusquedaLineal(arr, valorLineal);
                    if (resultadoLineal != -1) {
                        System.out.println("Valor encontrado en la posicion " + resultadoLineal);
                    } else {
                        System.out.println("Valor no encontrado");
                    }
                    break;
                default:
                    System.out.println("\n\nGracias BYE :) ");
                    band = false;
                    break;
            }

        } while (band != false);

        cin.close();
    }
}
