#include <iostream>
#include <string>

using namespace std;

struct Paciente {
    string nombre;
    int edad;
    double peso;
    double altura;
    Paciente* sgte;  // Puntero 
};

typedef Paciente* PLista;

// Función para agregar un paciente a la lista
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

// Función para eliminar un paciente de la lista
void eliminarPaciente(PLista& lista, const string& nombre) {
    PLista q = lista;
    PLista prev = NULL;

    while (q != NULL) {
        if (q->nombre == nombre) {
            if (q == lista) {
                lista = lista->sgte;
            } else {
                prev->sgte = q->sgte;
            }
            delete q;
            cout << "\nPaciente eliminado.\n";
            return;
        }
        prev = q;
        q = q->sgte;
    }
    cout << "\nPaciente no encontrado.\n";
}

// Función para actualizar la información de un paciente
void actualizarPaciente(PLista lista, const string& nombre) {
    PLista q = lista;

    while (q != NULL) {
        if (q->nombre == nombre) {
            cout << "\nActualice los datos del paciente:\n";
            cout << "Nuevo nombre (o presione Enter para mantener el actual): ";
            string nuevoNombre;
            getline(cin, nuevoNombre);
            if (!nuevoNombre.empty()) {
                q->nombre = nuevoNombre;
            }

            cout << "Nueva edad: ";
            cin >> q->edad;
            cout << "Nuevo peso: ";
            cin >> q->peso;
            cout << "Nueva altura: ";
            cin >> q->altura;
            cin.ignore();  // Limpiar el buffer

            cout << "\nPaciente actualizado.\n";
            return;
        }
        q = q->sgte;
    }
    cout << "\nPaciente no encontrado.\n";
}

// Función para mostrar todos los pacientes
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
        cout << "Edad: " << q->edad << endl;
        cout << "Peso: " << q->peso << endl;
        cout << "Altura: " << q->altura << endl;
        q = q->sgte;
        i++;
    }
}

// Función para liberar la memoria de la lista
void liberarLista(PLista& lista) {
    while (lista != NULL) {
        PLista temp = lista;
        lista = lista->sgte;
        delete temp;
    }
}

// Función principal
int main() {
    PLista lista = NULL;
    int opcion;
    string nombre;
    int edad;
    double peso;
    double altura;

    do {
        cout << "\n\t\t[    REGISTRO DE PACIENTES    ]\n";
        cout << "\t\t----------------------------\n\n";
        cout << "1. Registrar paciente\n";
        cout << "2. Eliminar paciente\n";
        cout << "3. Actualizar paciente\n";
        cout << "4. Mostrar pacientes\n";
        cout << "5. Salir\n";
        cout << "\nIngrese opción: ";
        cin >> opcion;
        cin.ignore();  // Limpiar el buffer

        switch (opcion) {
            case 1:
                cout << "\nIngrese nombre del paciente: ";
                getline(cin, nombre);
                cout << "Ingrese edad: ";
                cin >> edad;
                cout << "Ingrese peso: ";
                cin >> peso;
                cout << "Ingrese altura: ";
                cin >> altura;
                cin.ignore();  // Limpiar el buffer
                agregarPaciente(lista, nombre, edad, peso, altura);
                break;

            case 2:
                cout << "\nIngrese nombre del paciente a eliminar: ";
                getline(cin, nombre);
                eliminarPaciente(lista, nombre);
                break;

            case 3:
                cout << "\nIngrese nombre del paciente a actualizar: ";
                getline(cin, nombre);
                actualizarPaciente(lista, nombre);
                break;

            case 4:
                mostrarPacientes(lista);
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
