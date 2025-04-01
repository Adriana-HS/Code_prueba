#include <iostream>
#include <vector>
#include <string>#include <limits> // Para numeric_limits

using namespace std;

// Clase para representar un libro
class Libro {
public:
    string titulo;
    int copiasDisponibles;

    // Constructor de la clase Libro
    Libro(string titulo, int copiasDisponibles) : titulo(titulo), copiasDisponibles(copiasDisponibles) {}

    // Función para mostrar la información del libro
    void mostrarInformacion() const {
        cout << "Título: " << titulo << ", Copias disponibles: " << copiasDisponibles << endl;
    }
};

// Clase para representar el sistema de reserva de libros
class SistemaReserva {
private:
    vector<Libro> libros; // Vector para almacenar los libros

public:
    // Función para registrar un nuevo libro
    void registrarLibro() {
        string titulo;
        int copiasDisponibles;

        cout << "Ingrese el título del libro: ";
        getline(cin >> ws, titulo); // Usar getline para leer la línea completa incluyendo espacios.  ws consume el newline.

        cout << "Ingrese el número de copias disponibles: ";
        // Validación de entrada para asegurar que se ingrese un número entero.
        while (!(cin >> copiasDisponibles)) {
            cout << "Entrada inválida. Por favor, ingrese un número: ";
            cin.clear(); // Limpia los flags de error.
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Descarta la entrada inválida.
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Consumir la nueva línea después de leer el número.

        libros.emplace_back(titulo, copiasDisponibles); // Usar emplace_back para construir el objeto directamente en el vector.
        cout << "Libro registrado exitosamente." << endl;
    }

    // Función para reservar un libro
    void reservarLibro() {
        if (libros.empty()) {
            cout << "No hay libros registrados en el sistema." << endl;
            return;
        }

        string titulo;
        cout << "Ingrese el título del libro que desea reservar: ";
        getline(cin >> ws, titulo);

        for (Libro& libro : libros) { // Usar un bucle for-range y una referencia para modificar el objeto directamente.
            if (libro.titulo == titulo) {
                if (libro.copiasDisponibles > 0) {
                    libro.copiasDisponibles--;
                    cout << "Libro reservado exitosamente." << endl;
                    return;
                } else {
                    cout << "No hay copias disponibles del libro." << endl;
                    return;
                }
            }
        }
        cout << "Libro no encontrado." << endl;
    }

    // Función para listar los libros disponibles
    void listarLibrosDisponibles() const {
        if (libros.empty()) {
            cout << "No hay libros registrados en el sistema." << endl;
            return;
        }

        cout << "Lista de libros disponibles:" << endl;
        for (const Libro& libro : libros) { // Usar const Libro& para evitar copias innecesarias y asegurar que no se modifica el libro.
            libro.mostrarInformacion(); // Llama a la función mostrarInformacion de la clase Libro.
        }
    }
};

// Función principal del programa
int main() {
    SistemaReserva sistema;
    int opcion;

    do {
        cout << "\n--- Sistema de Reserva de Libros ---" << endl;
        cout << "1. Registrar libro" << endl;
        cout << "2. Reservar libro" << endl;
        cout << "3. Listar libros disponibles" << endl;
        cout << "0. Salir" << endl;
        cout << "Ingrese su opción: ";
        // Validación de entrada para la opción del menú
        while (!(cin >> opcion)) {
            cout << "Entrada inválida. Por favor, ingrese un número: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Consumir la nueva línea después de leer la opción.

        switch (opcion) {
            case 1:
                sistema.registrarLibro();
                break;
            case 2:
                sistema.reservarLibro();
                break;
            case 3:
                sistema.listarLibrosDisponibles();
                break;
            case 0:
                cout << "Saliendo del sistema." << endl;
                break;
            default:
                cout << "Opción inválida. Por favor, intente de nuevo." << endl;
        }
    } while (opcion != 0);

    return 0;
}
