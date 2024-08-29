#include <iostream>
#include <string>

using namespace std;

// Definición de la estructura Paciente
struct Paciente {
    string nombre;
    int edad;
    double peso;
    double altura;
};

int main() {
    // Crear un arreglo de 3 Paciente
    Paciente pacientes[3];

    // Inicializar los elementos del arreglo
    pacientes[0].nombre = "Eduardo";
    pacientes[0].edad = 22;
    pacientes[0].peso = 80;
    pacientes[0].altura = 1.80;

    pacientes[1].nombre = "Juanita";
    pacientes[1].edad = 18;
    pacientes[1].peso = 65;
    pacientes[1].altura = 1.63;

    pacientes[2].nombre = "Raúl";
    pacientes[2].edad = 45;
    pacientes[2].peso = 90;
    pacientes[2].altura = 1.77;

    // Acceder e imprimir la información del arreglo
    for (int i = 0; i < 3; ++i) {
        cout << "Paciente " << (i + 1) << ":" << endl;
        cout << "Nombre: " << pacientes[i].nombre << endl;
        cout << "Edad: " << pacientes[i].edad << " años" << endl;
        cout << "Peso: " << pacientes[i].peso << " kg" << endl;
        cout << "Altura: " << pacientes[i].altura << " m" << endl << endl;
    }

    return 0;
}
///gi