#include <iostream>
#include <string> // Necesario para usar std::string

using namespace std;

// Definición de la estructura Paciente
struct Paciente {
    string nombre;
    int edad;
    double peso;
    double altura;
};

int main() {
    /// Crear un arreglo de 3 Paciente
    Paciente pacientes[3];

    /// Inicializar el arreglo con datos
    pacientes[0].nombre = "Juanita";
    pacientes[0].edad = 30;
    pacientes[0].peso = 70.5;
    pacientes[0].altura = 1.75;

    pacientes[1].nombre = "Pepita";
    pacientes[1].edad = 25;
    pacientes[1].peso = 60.2;
    pacientes[1].altura = 1.68;

    pacientes[2].nombre = "Cristina";
    pacientes[2].edad = 40;
    pacientes[2].peso = 80.3;
    pacientes[2].altura = 1.80;

    /// Acceder e imprimir la información de cada paciente
    for (int i = 0; i < 3; ++i) {
        cout << "Paciente " << (i + 1) << ": " << pacientes[i].nombre << endl;
        cout << "Edad: " << pacientes[i].edad << " años" << endl;
        cout << "Peso: " << pacientes[i].peso << " kg" << endl;
        cout << "Altura: " << pacientes[i].altura << " m" << endl;
        cout << endl;
    }

    return 0;
}
