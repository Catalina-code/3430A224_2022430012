#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

struct Paciente {
    string nombre;
    int edad;
    double peso;
    double altura;
    Paciente* sgte;
};

typedef Paciente* PLista;

// Funciones de manejo de la lista de pacientes
void agregarPaciente(PLista& lista, const string& nombre, int edad, double peso, double altura) {
    PLista nuevo = new Paciente;
    nuevo->nombre = nombre;
    nuevo->edad = edad;
    nuevo->peso = peso;
    nuevo->altura = altura;
    nuevo->sgte = NULL;

    if (lista == NULL) {
        lista = nuevo;
    } else {
        PLista t = lista;
        while (t->sgte != NULL) {
            t = t->sgte;
        }
        t->sgte = nuevo;
    }
}

double calcularIMC(const Paciente* p) {
    return p->peso / (p->altura * p->altura);
}

double promedioEdad(PLista lista) {
    int totalEdad = 0, contador = 0;
    PLista q = lista;
    while (q != NULL) {
        totalEdad += q->edad;
        contador++;
        q = q->sgte;
    }
    return (contador == 0) ? 0 : static_cast<double>(totalEdad) / contador;
}

double promedioPeso(PLista lista) {
    double totalPeso = 0.0;
    int contador = 0;
    PLista q = lista;
    while (q != NULL) {
        totalPeso += q->peso;
        contador++;
        q = q->sgte;
    }
    return (contador == 0) ? 0 : totalPeso / contador;
}

void mostrarPacientes(PLista lista) {
    int i = 1;
    PLista q = lista;

    if (q == NULL) {
        cout << "\nNo hay pacientes registrados.\n";
        return;
    }

    while (q != NULL) {
        cout << "\nPaciente " << i << ":\n";
        cout << "Nombre: " << q->nombre << endl;
        cout << "Edad: " << q->edad << " años" << endl;
        cout << "Peso: " << q->peso << " kg" << endl;
        cout << "Altura: " << q->altura << " m" << endl;
        cout << "IMC: " << calcularIMC(q) << endl;
        q = q->sgte;
        i++;
    }
}

void cargarPacientesDesdeArchivo(PLista& lista, const string& nombreArchivo) {
    ifstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        cout << "No se pudo abrir el archivo " << nombreArchivo << endl;
        return;
    }

    string linea;
    while (getline(archivo, linea)) {
        stringstream ss(linea);
        string nombre;
        int edad;
        double peso, altura;
        getline(ss, nombre, ',');
        ss >> edad;
        ss.ignore();
        ss >> peso;
        ss.ignore();
        ss >> altura;
        agregarPaciente(lista, nombre, edad, peso, altura);
    }

    archivo.close();
    cout << "Datos cargados desde " << nombreArchivo << " correctamente." << endl;
}

void liberarLista(PLista& lista) {
    while (lista != NULL) {
        PLista temp = lista;
        lista = lista->sgte;
        delete temp;
    }
}

int main() {
    PLista lista = NULL;
    int opcion;

    do {
        cout << "\n\t\t[    REGISTRO DE PACIENTES    ]\n";
        cout << "\t\t----------------------------\n\n";
        cout << "1. Registrar paciente\n";
        cout << "2. Mostrar pacientes\n";
        cout << "3. Mostrar promedios de edad y peso\n";
        cout << "4. Cargar pacientes desde archivo CSV\n";
        cout << "5. Salir\n";
        cout << "\nIngrese opción: ";
        cin >> opcion;
        cin.ignore();

        switch (opcion) {
            case 1: {
                string nombre;
                int edad;
                double peso, altura;
                cout << "\nIngrese nombre del paciente: ";
                getline(cin, nombre);
                cout << "Ingrese edad: ";
                cin >> edad;
                cout << "Ingrese peso: ";
                cin >> peso;
                cout << "Ingrese altura: ";
                cin >> altura;
                cin.ignore();  
                agregarPaciente(lista, nombre, edad, peso, altura);
                break;
            }

            case 2:
                mostrarPacientes(lista);
                break;

            case 3:
                cout << "\nPromedio de edad: " << promedioEdad(lista) << " años" << endl;
                cout << "Promedio de peso: " << promedioPeso(lista) << " kg" << endl;
                break;

            case 4:
                cargarPacientesDesdeArchivo(lista, "pacientes.csv");
                break;

            case 5:
                cout << "\nSaliendo...\n";
                liberarLista(lista);
                break;

            default:
                cout << "\nOpción incorrecta. Intente nuevamente.\n";
                break;
        }

    } while (opcion != 5);

    return 0;
}
///