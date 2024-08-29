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
    // Crear pacientes
    Paciente paciente1; 
    paciente1.nombre = "Eduardo";
    paciente1.edad = 22;
    paciente1.peso = 80;
    paciente1.altura = 1.80;

    Paciente paciente2;
    paciente2.nombre = "Juanita";
    paciente2.edad = 18;
    paciente2.peso = 65;
    paciente2.altura = 1.63;

    Paciente paciente3;
    paciente3.nombre = "Raúl";
    paciente3.edad = 45;
    paciente3.peso = 90;
    paciente3.altura = 1.77;

/// Información paciente
    cout << "Paciente 1:" << endl;
    cout << "Nombre: " << paciente1.nombre << endl;
    cout << "Edad: " << paciente1.edad << " años" << endl;
    cout << "Peso: " << paciente1.peso << " kg" << endl;
    cout << "Altura: " << paciente1.altura << " m" << endl << endl;

    cout << "Paciente 2:" << endl;
    cout << "Nombre: " << paciente2.nombre << endl;
    cout << "Edad: " << paciente2.edad << " años" << endl;
    cout << "Peso: " << paciente2.peso << " kg" << endl;
    cout << "Altura: " << paciente2.altura << " m" << endl << endl;

    cout << "Paciente 3:" << endl;
    cout << "Nombre: " << paciente3.nombre << endl;
    cout << "Edad: " << paciente3.edad << " años" << endl;
    cout << "Peso: " << paciente3.peso << " kg" << endl;
    cout << "Altura: " << paciente3.altura << " m" << endl;

    return 0;
}
