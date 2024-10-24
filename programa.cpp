#include <iostream>
#include <cstdlib> // Para rand() y atoi()
#include <ctime>   // Para time()
#include <chrono>  // Para medir el tiempo 

using namespace std;

// Función de ordenamiento por selección (Selection Sort)
// Esta función ordena un arreglo iterando desde el primer hasta el penúltimo elemento.
// En cada iteración, encuentra el valor mínimo del subarreglo restante y lo intercambia
// con el valor en la posición actual.
void Seleccion(int arr[], int size) {
    // Itera desde el primer hasta el penúltimo elemento
    for (int i = 0; i < size - 1; ++i) {
        int indiceMinimo = i;
        // Busca el índice del menor valor en el subarreglo restante.
        for (int j = i + 1; j < size; ++j) {
            if (arr[j] < arr[indiceMinimo]) {
                indiceMinimo = j;
            }
        }  // Intercambia el valor mínimo encontrado con el valor actual.
        swap(arr[i], arr[indiceMinimo]);
    }
}


// Función de partición para Quicksort
// Reorganiza los elementos del arreglo de modo que todos los elementos menores que el pivote
// queden a la izquierda del mismo, y los mayores a la derecha.
int particion(int arr[], int bajo, int alto) {
    int pivote = arr[alto];
    int i = bajo - 1;
    for (int j = bajo; j < alto; ++j) {
        if (arr[j] < pivote) {
            ++i;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[alto]);
    return i + 1;
}


void Quicksort(int arr[], int bajo, int alto) {
    if (bajo < alto) {
        int pi = particion(arr, bajo, alto);
           // Quicksort recursivamente al subarreglo izquierdo
        Quicksort(arr, bajo, pi - 1);
         //Quicksort recursivamente al subarreglo derecho 
        Quicksort(arr, pi + 1, alto);
    }
}


// Función para llenar el arreglo con valores aleatorios entre 1 y 100000
void llenarArreglo(int arr[], int size) {
    for (int i = 0; i < size; ++i) {
        arr[i] = rand() % 100000 + 1;
    }
}

// Función para mostrar el contenido del arreglo
void mostrarArreglo(int arr[], int size) {
    for (int i = 0; i < size; ++i) {
        cout << "a[" << i << "]=" << arr[i] << " ";
    }
    cout << endl;
}

int main(int argc, char* argv[]) {
    // Verificación de parámetros de entrada
    if (argc < 3) {
        cout << "uso: ./programa N VER (donde N es el número de elementos y VER es 's' para mostrar el arreglo o 'n' para no mostrarlo)" << endl;
        return -1;
    }

    // Convertimos el primer argumento a entero
    int N = atoi(argv[1]); 
    if (N <= 0) { //Validaciones
        cout << "N debe ser un número positivo" << endl;
        return -1;
    }
    
    // El segundo argumento se interpreta como "s" o "n" para mostrar o no el arreglo
    char mostrar = tolower(argv[2][0]); 
    if (mostrar != 's' && mostrar != 'n') {
        cout << "El segundo parámetro debe ser 's' o 'n'" << endl;
        return -1;
    }

    // Reservamos memoria dinámica para el arreglo
    int* arr = new int[N];
    llenarArreglo(arr, N); // Llenamos el arreglo con números aleatorios

    // Copia del arreglo incial para seleccion y quicksort 
    int* arrCopia = new int[N];
    copy(arr, arr + N, arrCopia); 

    // Mostramos el arreglo original si se solicitó ('s')
    if (mostrar == 's') {
        cout << "Arreglo original:" << endl;
        mostrarArreglo(arr, N);
    }

    // Medición del tiempo de ejecución de Selection Sort
    auto inicioSeleccion = chrono::high_resolution_clock::now();
    Seleccion(arr, N); // Ordena el arreglo usando Selection Sort
    auto finSeleccion = chrono::high_resolution_clock::now();
    chrono::duration<double> duracionSeleccion = (finSeleccion - inicioSeleccion) * 1000;

    // Medición del tiempo de ejecución para Quicksort
    auto inicioQuicksort = chrono::high_resolution_clock::now();
    Quicksort(arrCopia, 0, N - 1); // Ordena el arreglo usando Quicksort
    auto finQuicksort = chrono::high_resolution_clock::now();
    chrono::duration<double> duracionQuicksort = (finQuicksort - inicioQuicksort) * 1000;

    // Mostrar la tabla de tiempos primero
    cout << "-----------------------------------------" << endl;
    cout << "    Método        |          Tiempo      " << endl;
    cout << "-----------------------------------------" << endl;
    cout << "Selección         |" << duracionSeleccion.count() << " milisegundos" << endl;
    cout << "Quicksort         |" << duracionQuicksort.count() << " milisegundos" << endl;
    cout << "-----------------------------------------" << endl;

    // Mostrar el arreglo ordenado con Selección si se solicitó
    if (mostrar == 's') {
        cout << "Selección           ";
        mostrarArreglo(arr, N);
    }

    // Mostrar el arreglo ordenado con Quicksort si se solicitó 
    if (mostrar == 's') {
        cout << "Quicksort           ";
        mostrarArreglo(arrCopia, N);
    }

    // Liberar memoria
    delete[] arr;
    delete[] arrCopia;

    return 0;
}
