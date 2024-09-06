#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <queue>
#include <string>

// Estructura de Paciente
struct Paciente {
    std::string nombre;
    int edad;
    double peso;
    double altura;
    double a1c;
    double imc;
    double prioridad;

    /// 
    ///
    bool operator<(const Paciente& other) const {
        return prioridad < other.prioridad;
    }
};

// Función para calcular el IMC.
double calcularIMC(double peso, double altura) {
    if (altura <= 0) {
        std::cerr << "Error:La altura debe ser mayor que cero." << std::endl;
        return 0;
    }
    return peso / (altura * altura);
}

// Función para calcular la prioridad basada en IMC y A1C. La prioridad será calculada dependiendo de su IMC y A1C mientras más elevado sea el valor final más prioritario será.
double calcularPrioridad(double imc, double a1c) {
    int factorA1C = 0;
    if (a1c < 5.7) {
        factorA1C = 0; // Normal
    } else if (a1c >= 5.7 && a1c <= 6.5) {
        factorA1C = 1; // Prediabetes
    } else {
        factorA1C = 2; // Diabetes
    }

    return imc * factorA1C;
}

// Función para cargar pacientes desde un archivo CSV
void cargarPacientesDesdeArchivo(std::vector<Paciente>& lista, const std::string& filename) {
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Error al abrir el archivo: " << filename << std::endl;
        return;
    }

    std::string line;
    std::getline(file, line);
    std::cout << "Cargando pacientes desde archivo...\n";

    while (std::getline(file, line)) {
        std::istringstream iss(line);
        Paciente p;
        std::string temp;

        // Lee los datos del archivo CSV
        std::getline(iss, p.nombre, ','); 
        std::getline(iss, temp, ',');     
        p.edad = std::stoi(temp);      // Convertir a int
        std::getline(iss, temp, ',');     
        p.altura = std::stod(temp);    // Convertir a double
        std::getline(iss, temp, ',');     
        p.peso = std::stod(temp);    // Convertir a double
        std::getline(iss, temp, ',');     
        p.a1c = std::stod(temp);    // Convertir a double

        // Calcular IMC y prioridad
        p.imc = calcularIMC(p.peso, p.altura);
        p.prioridad = calcularPrioridad(p.imc, p.a1c);
        lista.push_back(p);

        std::cout << "Paciente cargado: " << p.nombre 
                  << ", IMC: " << p.imc 
                  << ", A1C: " << p.a1c 
                  << ", Prioridad: " << p.prioridad 
                  << std::endl;
    }

    if (lista.empty()) {
        std::cout << "No se han cargado pacientes.\n";
    } else {
        std::cout << "Pacientes cargados correctamente.\n";
    }
}

// Función para buscar pacientes por IMC
void buscarPorIMC(const std::vector<Paciente>& lista, double minIMC, double maxIMC) {
    std::cout << "Pacientes con IMC entre " << minIMC << " y " << maxIMC << ":\n";
    bool encontrado = false;
    for (const auto& p : lista) {
        if (p.imc >= minIMC && p.imc <= maxIMC) {
            std::cout << "Nombre: " << p.nombre << ", IMC: " << p.imc << ", A1C: " << p.a1c << ", Prioridad: " << p.prioridad << "\n";
            encontrado = true;
        }
    }

    if (!encontrado) {
        std::cout << "No se encontraron pacientes en el rango de IMC especificado.\n";
    }
}

// Función para buscar pacientes por A1C
void buscarPorA1C(const std::vector<Paciente>& lista, double minA1C, double maxA1C) {
    std::cout << "Pacientes con A1C entre " << minA1C << " y " << maxA1C << ":\n";
    bool encontrado = false;
    for (const auto& p : lista) {
        if (p.a1c >= minA1C && p.a1c <= maxA1C) {
            std::cout << "Nombre: " << p.nombre << ", IMC: " << p.imc << ", A1C: " << p.a1c << ", Prioridad: " << p.prioridad << "\n";
            encontrado = true;
        }
    }

    if (!encontrado) {
        std::cout << "No se encontraron pacientes en el rango de A1C especificado.\n";
    }
}

// Funciones para la cola de atención
void encolarPacientesPrioritarios(const std::vector<Paciente>& lista, std::priority_queue<Paciente>& cola) {
    for (const auto& p : lista) {
        cola.push(p);
    }
    std::cout << "Pacientes encolados según prioridad.\n";
}

void atenderPacientes(std::priority_queue<Paciente>& cola) {
    int pacientesAtendidos = 0;
    while (!cola.empty() && pacientesAtendidos < 5) {
        Paciente paciente = cola.top();
        std::cout << "Atendiendo a: " << paciente.nombre << ", Prioridad: " << paciente.prioridad << "\n";
        cola.pop();
        pacientesAtendidos++;
    }
    if (pacientesAtendidos == 0) {
        std::cout << "No hay pacientes en la cola.\n";
    }
}

void verTamanioCola(const std::priority_queue<Paciente>& cola) {
    std::cout << "Tamaño de la cola: " << cola.size() << " pacientes.\n";
}

void limpiarCola(std::priority_queue<Paciente>& cola) {
    while (!cola.empty()) {
        cola.pop();
    }
    std::cout << "Cola limpiada.\n";
}

// Menú interactivo
void menuInteractivo() {
    std::vector<Paciente> lista;
    std::priority_queue<Paciente> colaPacientes;
    int opcion;

    do {
        std::cout << "\n--- Menú ---\n"
                  << "1. Cargar pacientes desde archivo\n"
                  << "2. Buscar pacientes por IMC\n"
                  << "3. Buscar pacientes por A1C\n"
                  << "4. Encolar pacientes prioritarios\n"
                  << "5. Atender pacientes\n"
                  << "6. Ver tamaño de la cola\n"
                  << "7. Limpiar cola\n"
                  << "8. Salir\n"
                  << "Seleccione una opción: ";
        std::cin >> opcion;

        switch (opcion) {
            case 1: {
                std::string nombreArchivo;
                std::cout << "Ingrese el nombre del archivo CSV: ";
                std::cin >> nombreArchivo;
                cargarPacientesDesdeArchivo(lista, nombreArchivo);
                break;
            }
            case 2: {
                double minIMC, maxIMC;
                std::cout << "Ingrese el rango de IMC (mínimo y máximo): escribir con un espaciado  ";
                std::cin >> minIMC >> maxIMC;
                buscarPorIMC(lista, minIMC, maxIMC);
                break;
            }
            case 3: {
                double minA1C, maxA1C;
                std::cout << "Ingrese el rango de A1C (mínimo y máximo): escribir con un espaciado  ";
                std::cin >> minA1C >> maxA1C;
                buscarPorA1C(lista, minA1C, maxA1C);
                break;
            }
            case 4: {
                encolarPacientesPrioritarios(lista, colaPacientes);
                break;
            }
            case 5: {
                atenderPacientes(colaPacientes);
                break;
            }
            case 6: {
                verTamanioCola(colaPacientes);
                break;
            }
            case 7: {
                limpiarCola(colaPacientes);
                break;
            }
            case 8: {
                std::cout << "Saliendo del programa...\n";
                break;
            }
            default: {
                std::cout << "Opción inválida. Intente nuevamente.\n";
                break;
            }
        }

    } while (opcion != 8);
}

int main() {
    menuInteractivo();
    return 0;
}

