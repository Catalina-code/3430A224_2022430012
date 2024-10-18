#include <iostream>
#include <fstream>
#include <vector>
#include <limits>
#include <set>  // Para manejar los conjuntos L y U

using namespace std;

// definicion de clase para el grafo
class Graph {
private:
    int N;  // numero de nodos
    vector<vector<int>> adjMatrix;  // matriz de adyacencia
    vector<pair<int, int>> MST;  // lista de aristas del arbol de costo minimo
    set<pair<int, int>> L;  // conjunto de aristas del mst
    set<int> U;  // conjunto de nodos en el mst

public:
    // constructor del grafo
    Graph(int n) : N(n) {
        adjMatrix.resize(N, vector<int>(N, -1));  // inicializar la matriz con -1 (sin conexion)
    }

    // funcion para leer la matriz de adyacencia desde la terminal
    void leerMatriz() {
        cout << "introduce los valores de la matriz de adyacencia (use -1 para no conexion):" << endl;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                cout << "distancia de " << char('a' + i) << " hasta " << char('a' + j) << ": ";
                cin >> adjMatrix[i][j];
                if (i == j) adjMatrix[i][j] = 0;  // la diagonal siempre es 0 (nodo a si mismo)
            }
        }
    }

    // funcion para aplicar el algoritmo de prim
    void prim() {
        vector<int> minCost(N, numeric_limits<int>::max());  // costo minimo para llegar a cada nodo
        vector<int> parent(N, -1);  // nodo anterior en el mst
        vector<bool> inMST(N, false);  // para verificar si el nodo ya esta en el mst

        // comenzar con el nodo 0
        minCost[0] = 0;
        parent[0] = -1;
        U.insert(0);  // agregar el nodo 0 al conjunto U (mst)

        for (int count = 0; count < N - 1; count++) {
            // elegir el nodo con el costo minimo que no esta en el mst
            int u = minDistance(minCost, inMST);
            inMST[u] = true;

            // actualizar los costos de los nodos adyacentes
            for (int v = 0; v < N; v++) {
                if (adjMatrix[u][v] != -1 && !inMST[v] && adjMatrix[u][v] < minCost[v]) {
                    minCost[v] = adjMatrix[u][v];
                    parent[v] = u;
                }
            }

            // agregar la arista (parent[u], u) al conjunto L y agregar u a U
            if (parent[u] != -1) {
                L.insert({parent[u], u});  // agregar la arista al conjunto L
                U.insert(u);  // agregar el nodo al conjunto U
                MST.push_back({parent[u], u});  // agregar la arista al MST
            }
        }
    }

    // funcion para obtener el nodo con el costo minimo que aun no esta en el mst
    int minDistance(vector<int>& minCost, vector<bool>& inMST) {
        int min = numeric_limits<int>::max(), min_index;

        for (int v = 0; v < N; v++) {
            if (!inMST[v] && minCost[v] < min) {
                min = minCost[v];
                min_index = v;
            }
        }
        return min_index;
    }

    // funcion para generar el archivo .dot del grafo original
    void generarDotOriginal() {
        ofstream archivo_dot("grafo_original.dot");
        archivo_dot << "graph G {\n";
        archivo_dot << "graph [rankdir=LR];\n";  // forzar direccion izquierda-derecha
        archivo_dot << "node [style=filled fillcolor=\"#00ff005f\"];\n";  // color de nodos

        // agregar las conexiones del grafo original
        for (int i = 0; i < N; i++) {
            for (int j = i + 1; j < N; j++) {
                if (adjMatrix[i][j] != -1) {
                    archivo_dot << "  " << char('a' + i) << " -- " << char('a' + j) << " [label=" << adjMatrix[i][j] << "];\n";
                }
            }
        }
        archivo_dot << "}\n";
        archivo_dot.close();
        cout << "archivo grafo_original.dot generado correctamente." << endl;
    }

    // funcion para generar el archivo .dot del arbol de costo minimo (mst)
    void generarDotMST() {
        ofstream archivo_dot("grafo_mst.dot");
        archivo_dot << "graph G {\n";
        archivo_dot << "graph [rankdir=LR];\n";  // forzar direccion izquierda-derecha
        archivo_dot << "node [style=filled fillcolor=\"#00ff005f\"];\n";  // color de nodos

        // agregar las conexiones del mst
        for (auto& edge : MST) {
            archivo_dot << "  " << char('a' + edge.first) << " -- " << char('a' + edge.second) << " [label=" << adjMatrix[edge.first][edge.second] << "];\n";
        }

        archivo_dot << "}\n";
        archivo_dot.close();
        cout << "archivo grafo_mst.dot generado correctamente." << endl;
    }

    // funcion para imprimir las aristas del mst
    void imprimirMST() {
        cout << "aristas del arbol abarcador de costo minimo (mst):" << endl;
        for (auto& edge : MST) {
            cout << char('a' + edge.first) << " -- " << char('a' + edge.second) << " [costo: " << adjMatrix[edge.first][edge.second] << "]" << endl;
        }
    }

    // funcion para imprimir los conjuntos L y U
    void imprimirConjuntosLU() {
        // imprimir el conjunto L (aristas seleccionadas)
        cout << "\nconjunto L (aristas seleccionadas en el mst):" << endl;
        for (auto& edge : L) {
            cout << char('a' + edge.first) << " -- " << char('a' + edge.second) << " [costo: " << adjMatrix[edge.first][edge.second] << "]" << endl;
        }

        // imprimir el conjunto U (nodos incluidos en el mst)
        cout << "\nconjunto U (nodos incluidos en el mst):" << endl;
        for (auto& node : U) {
            cout << char('a' + node) << " ";
        }
        cout << endl;
    }
};

int main(int argc, char* argv[]) {
    // verificar que se ingrese un valor valido para N
    if (argc < 2) {
        cout << "uso: ./prim N (donde N es mayor a 2)" << endl;
        return -1;
    }

    int N = atoi(argv[1]);
    if (N <= 2) {
        cout << "el valor de N debe ser mayor a 2." << endl;
        return -1;
    }

    // crear el grafo con N nodos
    Graph g(N);
    g.leerMatriz();  // leer la matriz de adyacencia desde la terminal
    g.generarDotOriginal();  // generar el grafo original en formato DOT

    g.prim();  // aplicar el algoritmo de prim
    g.imprimirMST();  // imprimir las aristas del mst
    g.generarDotMST();  // generar el mst en formato DOT
    g.imprimirConjuntosLU();  // imprimir los conjuntos L y U

    return 0;
}
