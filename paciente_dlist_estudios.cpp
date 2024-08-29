#include <iostream>
#include <string>

using namespace std;

struct Paciente {
    string nombre;
    int edad;
    double peso;
    double altura;
    Paciente* sgte;  // Puntero al siguiente paciente en la lista
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

// Función para calcular el IMC de un paciente
double calcularIMC(const Paciente* p) {
    return p->peso / (p->altura * p->altura);
}

// Función para calcular el promedio de edad de los pacientes
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

// Función para calcular el promedio de peso de los pacientes
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

// Función para mostrar los pacientes y su IMC
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

int main() {
    PLista lista = NULL;

    // Agregar pacientes a la lista
    agregarPaciente(lista, "Eduardo", 22, 80, 1.80);
    agregarPaciente(lista, "Juanita", 18, 65, 1.63);
    agregarPaciente(lista, "Raúl", 45, 90, 1.77);

    // Mostrar pacientes y sus datos
    mostrarPacientes(lista);

    // Calcular y mostrar los promedios de edad y peso
    cout << "\nPromedio de edad: " << promedioEdad(lista) << " años" << endl;
    cout << "Promedio de peso: " << promedioPeso(lista) << " kg" << endl;

    return 0;
}
///gi