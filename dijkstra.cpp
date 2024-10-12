#include <iostream>
#include <fstream>
#include <cstdlib>
#include <limits>

using namespace std;

// declaración de funciones que se utilizarán en el programa.
void inicializar_vector_caracter(char* vector, int n);
void imprimir_vector_caracter(char* vector, int n, const char* nombre);
void inicializar_matriz_enteros(int** matriz, int n);
void imprimir_matriz(int** matriz, int n);
void aplicar_dijkstra(char* V, int** M, int n, int origen);
int elegir_vertice(int* D, bool* visitados, int n);
void imprimir_grafo(int** matriz, char* vector, int n);

int main(int argc, char* argv[]) {
    // argc es el número de argumentos que se pasan al programa desde la línea de comandos
    // argv es un arreglo con los argumentos como cadenas de caracteres (el primer elemento es el nombre del programa)./ejemplo 3

    // validamos si el número de argumentos es menor a 2
    if (argc < 2) {
        cout << "uso: ./dijkstra N (donde N es mayor a 2)" << endl;
        return -1;  // -1 indica error en la ejecución
    }

    //convertir el tamaño de la matriz a entero "3"== 3
    // 'N' representa el número de nodos o vértices en el grafo
    int N = atoi(argv[1]);

    // si el valor de 'N' es menor o igual a 2, el grafo no es válido, así que mostramos un mensaje de error
    if (N <= 2) {
        cout << "el valor de N debe ser mayor a 2" << endl;
        return -1;
    }

    // ahora creamos una matriz de adyacencia dinámica para almacenar las distancias entre los nodos
    // usamos punteros para crear una matriz de tamaño N x N
    int** M = new int*[N];  // crea un arreglo de punteros a enteros
    for (int i = 0; i < N; i++) {
        M[i] = new int[N];  // para cada puntero, reservamos un arreglo de tamaño N (creamos las filas)
    }

    // inicializamos el vector que representará los nodos, usando caracteres como 'a', 'b', 'c', etc.
    char* V = new char[N];  // 
    inicializar_vector_caracter(V, N);  
    imprimir_vector_caracter(V, N, "nodos");  

    // inicializamos la matriz de adyacencia para luego leer los valores desde la terminal
    inicializar_matriz_enteros(M, N);  // establecemos todos los valores de la matriz a -1 inicialmente
    cout << "Introduce los valores de la matriz de adyacencia (use -1 para no conexión):" << endl;
    
    // aquí iteramos sobre cada celda de la matriz de adyacencia para obtener las distancias entre nodos
    for (int i = 0; i < N; i++) {  // iteramos por cada fila
        for (int j = 0; j < N; j++) {  // iteramos por cada columna
            cout << "Distancia de " << V[i] << " hasta " << V[j] << ": ";
            cin >> M[i][j];  // leemos el valor ingresado por el usuario para cada par de nodos

            // si estamos en la diagonal (es decir, el nodo conectado consigo mismo), establecemos la distancia a 0
            if (i == j) M[i][j] = 0;
        }
    }

    // imprimimos la matriz de adyacencia para ver las distancias que el usuario ingresó
    imprimir_matriz(M, N);

    // seleccionamos el vértice de origen desde el cual queremos aplicar el algoritmo de Dijkstra
    char origen;
    cout << "Ingrese el vértice de origen (nodo): ";
    cin >> origen;  // leemos el nodo origen como un carácter
    int indice_origen = -1;  // índice del nodo origen en el array de nodos
    for (int i = 0; i < N; i++) {
        // buscamos el índice correspondiente al nodo origen en el array V
        if (V[i] == origen) {
            indice_origen = i;  // si lo encontramos, guardamos su índice
            break;
        }
    }

    // si el nodo origen no es válido, terminamos el programa
    if (indice_origen == -1) {
        cout << "vértice origen no válido." << endl;
        return -1;
    }

    // aplicamos el algoritmo de Dijkstra para encontrar las rutas más cortas desde el nodo origen
    aplicar_dijkstra(V, M, N, indice_origen);

    // generamos una representación visual del grafo y la guardamos en un archivo
    imprimir_grafo(M, V, N);

    // liberamos la memoria dinámica asignada a la matriz de adyacencia y al vector de nodos
    for (int i = 0; i < N; i++) {
        delete[] M[i];  // liberamos cada fila
    }
    delete[] M;  // liberamos la matriz
    delete[] V;  // liberamos el vector de nodos

    return 0;  // el programa termina correctamente
}

// función que inicializa un vector con caracteres consecutivos (a, b, c, etc.)
void inicializar_vector_caracter(char* vector, int n) {
    for (int col = 0; col < n; col++) {
        vector[col] = 'a' + col;  // asignamos letras consecutivas desde 'a'
    }
}

// función que imprime el contenido de un vector de caracteres
void imprimir_vector_caracter(char* vector, int n, const char* nombre) {
    cout << endl << nombre << ": ";  // imprimimos el nombre del vector
    for (int i = 0; i < n; i++) {
        cout << vector[i] << " ";  // imprimimos cada carácter del vector
    }
    cout << endl;
}

// función que inicializa una matriz de enteros con el valor -1 (sin conexión)
void inicializar_matriz_enteros(int** matriz, int n) {
    for (int fila = 0; fila < n; fila++) {
        for (int col = 0; col < n; col++) {
            matriz[fila][col] = -1;  // establecemos todas las celdas a -1 (sin conexión)
        }
    }
}

// función que imprime la matriz de adyacencia, mostrando las distancias entre nodos
void imprimir_matriz(int** matriz, int n) {
    cout << endl << "matriz de adyacencia:" << endl;
    for (int fila = 0; fila < n; fila++) {
        for (int col = 0; col < n; col++) {
            cout << "matriz[" << fila << "," << col << "]: " << matriz[fila][col] << " ";
        }
        cout << endl;
    }
}

// función que aplica el algoritmo de Dijkstra para encontrar el camino más corto desde el nodo origen
void aplicar_dijkstra(char* V, int** M, int n, int origen) {
    int* D = new int[n];          
    bool* visitados = new bool[n]; 
    char* S = new char[n];         
    char* VS = new char[n];        

    // inicializamos las distancias y los conjuntos de nodos
    for (int i = 0; i < n; i++) {
        // si hay conexión entre el nodo origen y el nodo i, usamos la distancia; si no, asignamos infinito(-1)
        D[i] = (M[origen][i] != -1) ? M[origen][i] : numeric_limits<int>::max();
        visitados[i] = false;  // inicialmente, ningún nodo ha sido visitado
        S[i] = ' ';  // el conjunto de nodos visitados está vacío
        VS[i] = V[i];  // los nodos no visitados son todos los nodos al inicio
    }
    D[origen] = 0;  // la distancia desde el origen hasta sí mismo es 0, a hasta a = 0

    cout << "S[]:   VS[]:   D[]:" << endl;
    for (int i = 0; i < n; i++) {
        cout << "S[" << i << "]: " << S[i] << " VS[" << i << "]: " << VS[i] << " D[" << i << "]: " << (D[i] == numeric_limits<int>::max() ? -1 : D[i]) << endl;
    }
    cout << "-------------------------------------------" << endl;

    // aplicamos Dijkstra en n-1 iteraciones para actualizar distancias
    for (int i = 0; i < n - 1; i++) {
        // elegimos el vértice con la menor distancia que no ha sido visitado
        int u = elegir_vertice(D, visitados, n);
        visitados[u] = true;  // marcamos el vértice como visitado
        S[i] = V[u];  // añadimos el vértice al conjunto S[]
        VS[u] = ' ';  // eliminamos el vértice de VS[]

        cout << "> se agrega el vértice " << V[u] << " a S[] y se actualiza VS[]:" << endl;
        for (int j = 0; j < n; j++) {
            cout << "S[" << j << "]: " << S[j] << " VS[" << j << "]: " << VS[j] << " D[" << j << "]: " << (D[j] == numeric_limits<int>::max() ? -1 : D[j]) << endl;
        }

        // actualizamos las distancias mínimas
        for (int v = 0; v < n; v++) {
            if (!visitados[v] && M[u][v] != -1 && D[u] != numeric_limits<int>::max() &&
                D[u] + M[u][v] < D[v]) {
                D[v] = D[u] + M[u][v];  // actualizamos la distancia si se encuentra un camino más corto
            }
        }

        cout << "> se actualizan las distancias en D[]:" << endl;
        for (int j = 0; j < n; j++) {
            cout << "D[" << j << "]: " << (D[j] == numeric_limits<int>::max() ? -1 : D[j]) << endl;
        }
        cout << "-------------------------------------------" << endl;
    }

    // mostramos el resultado final: las distancias mínimas desde el nodo origen
    cout << "distancias mínimas desde el vértice " << V[origen] << ":" << endl;
    for (int i = 0; i < n; i++) {
        cout << "hasta " << V[i] << ": " << (D[i] == numeric_limits<int>::max() ? -1 : D[i]) << endl;
    }

    // liberamos la memoria dinámica
    delete[] D;
    delete[] visitados;
    delete[] S;
    delete[] VS;
}

// función para elegir el vértice no visitado con la distancia mínima
int elegir_vertice(int* D, bool* visitados, int n) {
    int min = numeric_limits<int>::max();
    int min_indice = -1;

    // iteramos sobre todos los vértices para encontrar el que tenga la menor distancia y no haya sido visitado
    for (int v = 0; v < n; v++) {
        if (!visitados[v] && D[v] < min) {
            min = D[v];  // actualizamos el valor mínimo si encontramos un vértice con menor distancia
            min_indice = v;  // guardamos el índice del vértice con la menor distancia
        }
    }

    return min_indice;  // devolvemos el índice del vértice con la distancia mínima
}

// función que imprime la representación del grafo en formato DOT (para graficar con Graphviz)
void imprimir_grafo(int** matriz, char* vector, int n) {
    ofstream archivo_dot("grafo.dot");  // creamos un archivo llamado "grafo.dot"
    archivo_dot << "digraph G {" << endl;  // comenzamos la definición del grafo en formato DOT

    // iteramos sobre la matriz de adyacencia para escribir las conexiones en el archivo DOT
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (matriz[i][j] != -1 && matriz[i][j] != 0) {  // si hay una conexión entre los nodos i y j
                archivo_dot << "    " << vector[i] << " -> " << vector[j] << " [label=" << matriz[i][j] << "];" << endl;  // escribimos la conexión
            }
        }
    }

    archivo_dot << "}" << endl;  // cerramos la definición del grafo
    archivo_dot.close();  // cerramos el archivo

    cout << "Archivo grafo.dot generado correctamente." << endl;  // informamos que el archivo se generó exitosamente
}
