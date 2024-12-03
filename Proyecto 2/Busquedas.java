public class Busquedas {

    // Búsqueda Binaria
    public static int BusquedaBinaria(int[] arr, int valor) {
        int izquierda = 0, derecha = arr.length - 1;
        while (izquierda <= derecha) {
            int medio = izquierda + (derecha - izquierda) / 2;
            if (arr[medio] == valor) {
                return medio;
            }
            if (arr[medio] < valor) {
                izquierda = medio + 1;
            } else {
                derecha = medio - 1;
            }
        }
        return -1;
    }

    // Búsqueda Lineal
    public static int BusquedaLineal(int[] arr, int valor) {
        for (int i = 0; i < arr.length; i++) {
            if (arr[i] == valor) {
                return i;
            }
        }
        return -1;
    }
}
