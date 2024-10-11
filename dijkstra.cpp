#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 0
#define FALSE 1
#define N 5
#define INF 9999 // representa & para las distancias

// declaracion de funciones
void leer_nodos(char vector[N]);
void leer_matriz(int M[N][N]);
void inicializar_vector_D(int D[N], int M[N][N], int origen);
void inicializar_vector_caracter(char vector[N]);
void aplicar_dijkstra(char V[N], char S[N], char VS[N], int D[N], int M[N][N], int origen);
void actualizar_VS(char V[N], char S[N], char VS[N]);
int buscar_indice_caracter(char V[N], char caracter);
void agrega_vertice_a_S(char S[N], char vertice);
int elegir_vertice(char VS[N], int D[N], char V[N]);
void actualizar_pesos(int D[N], char VS[N], int M[N][N], char V[N], char v);
int calcular_minimo(int dw, int dv, int mvw);
void imprimir_vector_caracter(char vector[N], char *);
void imprimir_vector_entero(int vector[N]);
void imprimir_matriz(int matriz[N][N]);
void imprimir_grafo(int matriz[N][N], char vector[N]);

// funcion principal
int main(int argc, char **argv) {
    char V[N], S[N], VS[N];
    int D[N];
    int origen;

    // matriz de distancias (se leera desde la terminal)
    int M[N][N];

    // leer la matriz desde la terminal
    leer_matriz(M);

    // convertir -1 a INF (infinito)
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (M[i][j] == -1) {
                M[i][j] = INF;
            }
        }
    }

    // inicializar vectores V, S y VS con espacios vacios
    inicializar_vector_caracter(V);
    inicializar_vector_caracter(S);
    inicializar_vector_caracter(VS);

    // leer nodos (etiquetar los vertices con 'a', 'b', 'c', ...)
    leer_nodos(V);

    // leer vertice origen desde la terminal
    printf("ingrese el vertice origen (0-%d): ", N-1);
    scanf("%d", &origen);

    // validar el vertice origen
    if (origen < 0 || origen >= N) {
        printf("error: el vertice origen debe estar entre 0 y %d.\n", N-1);
        return -1;
    }

    // aplicar el algoritmo de dijkstra
    aplicar_dijkstra(V, S, VS, D, M, origen);

    // imprimir el grafo con graphviz
    imprimir_grafo(M, V);

    return 0;
}

// funcion para leer la matriz desde la terminal
void leer_matriz(int M[N][N]) {
    printf("ingrese la matriz de distancias (%dx%d):\n", N, N);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            scanf("%d", &M[i][j]);
        }
    }
}

// funcion para inicializar el vector D[] con los valores de la fila correspondiente al vertice origen
void inicializar_vector_D(int D[N], int M[N][N], int origen) {
    for (int col = 0; col < N; col++) {
        D[col] = M[origen][col]; // se asignan las distancias desde el vertice origen
    }
}

// inicializa un vector de caracteres con espacios vacios
void inicializar_vector_caracter(char vector[N]) {
    for (int col = 0; col < N; col++) {
        vector[col] = ' '; // cada posicion del vector se llena con un espacio vacio
    }
}

// aplica el algoritmo de dijkstra
void aplicar_dijkstra(char V[N], char S[N], char VS[N], int D[N], int M[N][N], int origen) {
    int i, v;

    // inicializar el vector de distancias D[] segun los datos de la matriz M[][]
    inicializar_vector_D(D, M, origen);

    // imprimir los estados iniciales de la matriz, S[], VS[] y D[]
    printf("---------estados iniciales ---------------------------------------\n");
    imprimir_matriz(M);
    printf("\n");
    imprimir_vector_caracter(S, "S");
    imprimir_vector_caracter(VS, "VS");
    imprimir_vector_entero(D);
    printf("------------------------------------------------------------------\n\n");

    // agregar el primer vertice a S[] (origen) y actualizar VS[]
    printf("> agrega primer valor V[%d] a S[] y actualiza VS[]\n\n", origen);
    agrega_vertice_a_S(S, V[origen]);
    imprimir_vector_caracter(S, "S");

    // actualizar el conjunto de vertices candidatos VS[]
    actualizar_VS(V, S, VS);
    imprimir_vector_caracter(VS, "VS");
    imprimir_vector_entero(D);

    // ciclo para seleccionar el siguiente vertice y actualizar los pesos
    for (i = 1; i < N; i++) {
        printf("\n> elige vertice menor en VS[] segun valores en D[]\n");
        printf("> lo agrega a S[] y actualiza VS[]\n");
        v = elegir_vertice(VS, D, V); // se elige el vertice con la menor distancia en D[]
        if (v == -1) {
            printf("no se pudo encontrar un vertice valido.\n");
            break;
        }
        agrega_vertice_a_S(S, v);
        imprimir_vector_caracter(S, "S");
        actualizar_VS(V, S, VS);
        imprimir_vector_caracter(VS, "VS");
        actualizar_pesos(D, VS, M, V, v); // se actualizan los pesos en el vector D[]
        imprimir_vector_entero(D);
    }
}

// actualiza los pesos en D[] segun el algoritmo de dijkstra
void actualizar_pesos(int D[N], char VS[N], int M[N][N], char V[N], char v) {
    int i = 0;
    int indice_w, indice_v;

    printf("\n> actualiza pesos en D[]\n");
    indice_v = buscar_indice_caracter(V, v); // se obtiene el indice del vertice seleccionado
    while (VS[i] != ' ') { // recorrer los vertices en VS[]
        if (VS[i] != v) {
            indice_w = buscar_indice_caracter(V, VS[i]);
            D[indice_w] = calcular_minimo(D[indice_w], D[indice_v], M[indice_v][indice_w]);
        }
        i++;
    }
}

// calcula el valor minimo entre dw y dv + mvw
int calcular_minimo(int dw, int dv, int mvw) {
    int min = 0;

    if (dw == INF) { // si dw es infinito
        if (dv != INF && mvw != INF)
            min = dv + mvw; // actualiza con la suma de dv + mvw
        else
            min = INF;
    } else {
        if (dv != INF && mvw != INF) {
            if (dw <= (dv + mvw))
                min = dw;
            else
                min = (dv + mvw);
        }
        else
            min = dw;
    }

    printf("dw: %d dv: %d mvw: %d min: %d\n", dw, dv, mvw, min);
    return min;
}

// agrega un vertice a S[]
void agrega_vertice_a_S(char S[N], char vertice) {
    for (int i = 0; i < N; i++) {
        if (S[i] == ' ') { // encuentra el primer espacio vacio en S[]
            S[i] = vertice;
            return;
        }
    }
}

// elige el vertice con menor peso en VS[] y su correspondiente valor en D[]
int elegir_vertice(char VS[N], int D[N], char V[N]) {
    int i = 0;
    int menor = INF; // se inicializa el menor valor a infinito
    int vertice = -1; // vertice invalido por defecto

    // recorrer VS[] y buscar el vertice con la menor distancia en D[]
    while (VS[i] != ' ' && i < N) {
        int indice_vs = buscar_indice_caracter(V, VS[i]);
        if (D[indice_vs] < menor) {
            menor = D[indice_vs];
            vertice = VS[i]; // actualiza el vertice de menor distancia
        }
        i++;
    }

    if (vertice != -1) {
        printf("\nvertice: %c\n\n", vertice);
    } else {
        printf("no se pudo encontrar un vertice valido.\n");
    }
    return vertice;
}

// retorna el indice del caracter consultado
int buscar_indice_caracter(char V[N], char caracter) {
    for (int i = 0; i < N; i++) {
        if (V[i] == caracter)
            return i;
    }
    return -1;
}

// actualiza VS[] despues de agregar un vertice a S[]
void actualizar_VS(char V[N], char S[N], char VS[N]) {
    int j, k = 0;
    inicializar_vector_caracter(VS); // reinicia el vector VS[]

    // agregar a VS[] solo los vertices que no estan en S[]
    for (j = 0; j < N; j++) {
        int indice = buscar_indice_caracter(S, V[j]);
        if (indice == N) { // si no esta en S[]
            VS[k] = V[j];
            k++;
        }
    }
}

// lee los nodos e inicializa el vector con caracteres ascii ('a', 'b', 'c', ...)
void leer_nodos(char vector[N]) {
    int inicio = 97; // codigo ascii para 'a'
    for (int i = 0; i < N; i++) {
        vector[i] = inicio + i;
    }
}

// imprime un vector de caracteres
void imprimir_vector_caracter(char vector[N], char *nomVector) {
    for (int i = 0; i < N; i++) {
        printf("%s[%d]: %c ", nomVector, i, vector[i]);
    }
    printf("\n");
}

// imprime un vector de enteros
void imprimir_vector_entero(int vector[N]) {
    for (int i = 0; i < N; i++) {
        if (vector[i] == INF) {
            printf("D[%d]: INF ", i);
        } else {
            printf("D[%d]: %d ", i, vector[i]);
        }
    }
    printf("\n");
}

// imprime una matriz bidimensional de enteros
void imprimir_matriz(int matriz[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (matriz[i][j] == INF) {
                printf("matriz[%d,%d]: INF ", i, j);
            } else {
                printf("matriz[%d,%d]: %d ", i, j, matriz[i][j]);
            }
        }
        printf("\n");
    }
}

// genera un archivo .dot para crear el grafo con graphviz
void imprimir_grafo(int matriz[N][N], char vector[N]) {
    int i, j;
    FILE *fp;

    fp = fopen("grafo.txt", "w");
    fprintf(fp, "%s\n", "digraph G {");
    fprintf(fp, "%s\n", "graph [rankdir=LR];");
    fprintf(fp, "%s\n", "node [style=filled fillcolor=yellow];");

    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            if (i != j && matriz[i][j] != INF) {
                fprintf(fp, "%c%s%c [label=%d];\n", vector[i], "->", vector[j], matriz[i][j]);
            }
        }
    }

    fprintf(fp, "%s\n", "}");
    fclose(fp);

    system("dot -Tpng grafo.txt -o grafo.png");
    system("open grafo.png");  //mac
}
