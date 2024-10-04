#include <iostream>
#include <fstream>
#include <cstdlib>
using namespace std;

// Definición de un nodo del árbol AVL.
struct Nodo {
    int dato;
    int FE; // Factor de equilibrio
    Nodo* izquierdo;
    Nodo* derecho;
    Nodo* padre;

    Nodo(int valor) : dato(valor), FE(0), izquierdo(nullptr), derecho(nullptr), padre(nullptr) {}
};

typedef Nodo* pNodo;
typedef Nodo* Arbol;

// Funciones auxiliares para rotaciones y reestructuración.
void RotaDerecha(Arbol* raiz, pNodo& NODO);
void RotaIzquierda(Arbol* raiz, pNodo& NODO);
void Reestructura_izq(Arbol* raiz, pNodo& NODO, bool& BO);
void Reestructura_der(Arbol* raiz, pNodo& NODO, bool& BO);

// Función para insertar un elemento en el árbol balanceado.
void Inserta_balanceado(Arbol* raiz, pNodo& NODO, bool& BO, int INFOR) {
    if (NODO != nullptr) {
        if (INFOR < NODO->dato) { // Inserción en el subárbol izquierdo.
            Inserta_balanceado(raiz, NODO->izquierdo, BO, INFOR);
            if (BO) {
                if (NODO->FE == 1) {
                    NODO->FE = 0;
                    BO = false;
                } else if (NODO->FE == 0) {
                    NODO->FE = -1;
                } else if (NODO->FE == -1) {
                    pNodo NODO1 = NODO->izquierdo;
                    if (NODO1->FE <= 0) { // Rotación II
                        RotaDerecha(raiz, NODO);
                        NODO->FE = 0;
                        NODO1->FE = 0;
                    } else { // Rotación ID
                        pNodo NODO2 = NODO1->derecho;
                        RotaIzquierda(raiz, NODO->izquierdo);
                        RotaDerecha(raiz, NODO);
                        NODO->FE = (NODO2->FE == 1) ? -1 : 0;
                        NODO1->FE = (NODO2->FE == -1) ? 1 : 0;
                        NODO2->FE = 0;
                    }
                    BO = false;
                }
            }
        } else if (INFOR > NODO->dato) { // Inserción en el subárbol derecho.
            Inserta_balanceado(raiz, NODO->derecho, BO, INFOR);
            if (BO) {
                if (NODO->FE == -1) {
                    NODO->FE = 0;
                    BO = false;
                } else if (NODO->FE == 0) {
                    NODO->FE = 1;
                } else if (NODO->FE == 1) {
                    pNodo NODO1 = NODO->derecho;
                    if (NODO1->FE >= 0) { // Rotación DD
                        RotaIzquierda(raiz, NODO);
                        NODO->FE = 0;
                        NODO1->FE = 0;
                    } else { // Rotación DI
                        pNodo NODO2 = NODO1->izquierdo;
                        RotaDerecha(raiz, NODO->derecho);
                        RotaIzquierda(raiz, NODO);
                        NODO->FE = (NODO2->FE == -1) ? 1 : 0;
                        NODO1->FE = (NODO2->FE == 1) ? -1 : 0;
                        NODO2->FE = 0;
                    }
                    BO = false;
                }
            }
        } else {
            cout << "El número ya se encuentra en el árbol." << endl;
            BO = false;
            return;  // Evitar insertar duplicados
        }
    } else {
        // Crear un nuevo nodo si NODO es nullptr.
        NODO = new Nodo(INFOR);
        if (NODO == nullptr) {
            cout << "Error al crear el nodo." << endl;
            BO = false;
        } else {
            BO = true;
        }
    }
}

// Función para eliminar un elemento del árbol balanceado.
void Elimina_balanceado(Arbol* raiz, pNodo& NODO, bool& BO, int INFOR) {
    if (NODO != nullptr) {
        if (INFOR < NODO->dato) { // Eliminar en el subárbol izquierdo.
            Elimina_balanceado(raiz, NODO->izquierdo, BO, INFOR);
            if (BO) Reestructura_der(raiz, NODO, BO);
        } else if (INFOR > NODO->dato) { // Eliminar en el subárbol derecho.
            Elimina_balanceado(raiz, NODO->derecho, BO, INFOR);
            if (BO) Reestructura_izq(raiz, NODO, BO);
        } else { // Nodo encontrado.
            pNodo OTRO = NODO;
            BO = true;
            if (NODO->derecho == nullptr) {
                NODO = NODO->izquierdo;
            } else if (NODO->izquierdo == nullptr) {
                NODO = NODO->derecho;
            } else { // Nodo con dos hijos.
                pNodo AUX = NODO->izquierdo;
                bool BOOL = false;
                while (AUX->derecho != nullptr) {
                    AUX = AUX->derecho;
                    BOOL = true;
                }
                NODO->dato = AUX->dato;
                OTRO = AUX;
                if (BOOL) {
                    AUX->padre->derecho = AUX->izquierdo;
                } else {
                    NODO->izquierdo = AUX->izquierdo;
                }
                delete OTRO;
                Reestructura_der(raiz, NODO->izquierdo, BO);
            }
            delete OTRO;
        }
    } else {
        cout << "El número no se encuentra en el árbol." << endl;
        BO = false;
    }
}

// Función para modificar un valor en el árbol.
void Modificar_valor(Arbol* raiz, int valor_antiguo, int valor_nuevo) {
    bool BO = false;
    Elimina_balanceado(raiz, *raiz, BO, valor_antiguo);
    if (BO) {
        Inserta_balanceado(raiz, *raiz, BO, valor_nuevo);
    }
}

// Función para generar el grafo en formato Graphviz.
void GenerarGraphviz(pNodo NODO, ofstream& archivo) {
    if (NODO != nullptr) {
        archivo << NODO->dato << " [label=\"" << NODO->dato << " (" << NODO->FE << ")\"];\n";
        if (NODO->izquierdo != nullptr) {
            archivo << NODO->dato << " -> " << NODO->izquierdo->dato << ";\n";
            GenerarGraphviz(NODO->izquierdo, archivo);
        } else {
            archivo << "null" << NODO->dato << " [shape=point];\n";
            archivo << NODO->dato << " -> null" << NODO->dato << ";\n";
        }
        if (NODO->derecho != nullptr) {
            archivo << NODO->dato << " -> " << NODO->derecho->dato << ";\n";
            GenerarGraphviz(NODO->derecho, archivo);
        } else {
            archivo << "null" << NODO->dato << "r [shape=point];\n";
            archivo << NODO->dato << " -> null" << NODO->dato << "r;\n";
        }
    }
}

void GenerarArchivoGraphviz(Arbol raiz) {
    ofstream archivo("grafo.txt");
    archivo << "digraph AVL {\n";
    GenerarGraphviz(raiz, archivo);
    archivo << "}\n";
    archivo.close();
    system("dot -Tpng -ografo.png grafo.txt");
    system("eog grafo.png");
}

// Menú principal para el programa.
void Menu(Arbol* raiz) {
    int opcion, valor, valor_nuevo;
    bool BO = false;
    do {
        cout << "1) Insertar número" << endl;
        cout << "2) Eliminar número" << endl;
        cout << "3) Modificar número" << endl;
        cout << "4) Generar grafo" << endl;
        cout << "5) Salir" << endl;
        cout << "Seleccione una opción: ";
        cin >> opcion;

        switch (opcion) {
        case 1:
            cout << "Ingrese un número: ";
            cin >> valor;
            Inserta_balanceado(raiz, *raiz, BO, valor);
            break;
        case 2:
            cout << "Ingrese el número a eliminar: ";
            cin >> valor;
            Elimina_balanceado(raiz, *raiz, BO, valor);
            break;
        case 3:
            cout << "Ingrese el número a modificar: ";
            cin >> valor;
            cout << "Ingrese el nuevo valor: ";
            cin >> valor_nuevo;
            Modificar_valor(raiz, valor, valor_nuevo);
            break;
        case 4:
            GenerarArchivoGraphviz(*raiz);
            break;
        case 5:
            cout << "Saliendo..." << endl;
            break;
        default:
            cout << "Opción no válida." << endl;
        }
    } while (opcion != 5);
}

int main() {
    Arbol raiz = nullptr;
    Menu(&raiz);
    return 0;
}
