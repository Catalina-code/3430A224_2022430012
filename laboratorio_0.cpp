#include <iostream>
#include <string>
#include <limits>

bool esPar(int numero) {
    return numero % 2 == 0;
}

int longitudString(const std::string& texto) {
    return static_cast<int>(texto.length());
}

int leerNumero() {
    int numero;
    while (true) {
        std::cout << "Ingrese un número entero: ";
        std::cin >> numero;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Entrada no válida. Por favor, ingrese un número entero.\n";
        } else {
            break;
        }
    }
    return numero;
}

std::string leerString() {
    std::string texto;
    std::cout << "Ingrese un string: ";
    std::cin >> texto;
    return texto;
}

int main() {
    int numero = leerNumero();
    std::cout << "Número ingresado: " << numero << std::endl;
    std::cout << "El número " << numero << (esPar(numero) ? " es par." : " es impar.") << std::endl;

    for (int i = 1; i <= 10; i++) {
        std::cout << "El número " << i << (esPar(i) ? " es par." : " es impar.") << std::endl;
    }

    std::string textoUsuario = leerString();
    std::cout << "La longitud del string ingresado es: " << longitudString(textoUsuario) << std::endl;

    return 0;
}
//
