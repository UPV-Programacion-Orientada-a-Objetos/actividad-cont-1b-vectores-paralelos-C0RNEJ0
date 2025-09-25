#include <iostream>
#include <string>
#include <iomanip> // para mostrar precios con 2 decimales
#include <fstream>
#include  <vector>
// CONFIGURACIÓN 
const int MAX_PRODUCTOS = 100;  // tamaño fijo de los arreglos
const int INICIA_PRODUCTOS = 6; // cantidad inicial cargada

//  ARREGLOS PARALELOS 
// Mismo índice = mismo producto
int    codigos[MAX_PRODUCTOS]   = {101, 102, 103, 104, 105, 106};
std::string nombres[MAX_PRODUCTOS]   = {
    "Martillo de bola",
    "Destornillador",
    "Cinta metrica",
    "Llave inglesa",
    "Taladro inalambrico"
    "Veredictor",
};
int    stocks[MAX_PRODUCTOS]    = {50, 120, 75, 45, 10, 11}; //LA CANTIDAD DE PRODUCTOS
float  precios[MAX_PRODUCTOS]   = {15.50f, 8.75f, 20.00f, 25.99f, 120.00f, 122.00f,}; //precios

// cuántos productos realmente hay cargados
int numProductos = INICIA_PRODUCTOS;

//  COSAS SENCILLAS DE ENTRADA 
// Lee un entero. Si el usuario se equivoca, le vuelve a pedir.
void leerEntero(const std::string& mensaje, int& destino) {
    std::cout << mensaje;
    while (!(std::cin >> destino)) {
        std::cin.clear();
        std::cin.ignore(1000, '\n');
        std::cout << "Entrada invalida. Ingresa un numero: ";
    }
    std::cin.ignore(1000, '\n'); // limpia resto de la línea
}

//  MENÚ 
void mostrarMenu() {
    std::cout << "\n--- Inventario \"El Martillo\" ---\n";
    std::cout << "1) Consultar producto por codigo\n";
    std::cout << "2) Actualizar inventario (+/- stock)\n";
    std::cout << "3) Reporte completo\n";
    std::cout << "4) Producto mas caro\n";
    std::cout << "5) Salir\n";
    std::cout << "Opcion: ";
}

int main() {
    // Para que los precios se vean con 2 decimales siempre
      
       
      std::ifstream myfile("inventario.txt");

   if (myfile.is_open())
   {
      std::string line;
      std::vector<std::string> v;

      while (std::getline(myfile, line))
      {
         v.push_back(line);
      }

      myfile.close();

      std::cout << "TOTAL: " << v.size() << '\n';

      for (size_t index { }; index < v.size(); index++)
      {
         std::cout << "Line #" << index + 1 << " - " << v[index] << '\n';
      }
   }
   else
   {
      std::cout << "Unable to open file\n";
   }
}
    
   
    std::cout << std::fixed << std::setprecision(2);

    int opcion = 0;
    do {
        mostrarMenu();
        leerEntero("", opcion);

        if (opcion == 1) {
            //  Consultar producto 
            int codigo;
            leerEntero("Codigo a consultar: ", codigo);

            bool encontrado = false;
            for (int i = 0; i < numProductos; i++) {
                if (codigos[i] == codigo) {
                    std::cout << "Codigo : " << codigos[i]   << "\n";
                    std::cout << "Nombre : " << nombres[i]   << "\n";
                    std::cout << "Stock  : " << stocks[i]    << "\n";
                    std::cout << "Precio : $" << precios[i]  << "\n";
                    encontrado = true;
                    break;
                }
            }
            if (!encontrado) {
                std::cout << "No existe un producto con ese codigo.\n";
            }
        }
        else if (opcion == 2) {
            //  Actualizar inventario -
            int codigo;
            leerEntero("Codigo a actualizar: ", codigo);

            bool encontrado = false;
            for (int i = 0; i < numProductos; i++) {
                if (codigos[i] == codigo) {
                    int cantidad;
                    leerEntero("Cantidad a sumar/restar (ej. 10 o -5): ", cantidad);

                    // no permitir stock negativo
                    if (stocks[i] + cantidad < 0) {
                        std::cout << "Error: el stock no puede quedar negativo.\n";
                    } else {
                        stocks[i] += cantidad;
                        std::cout << "Stock nuevo: " << stocks[i] << "\n";
                    }
                    encontrado = true;
                    break;
                }
            }
            if (!encontrado) {
                std::cout << "No existe un producto con ese codigo.\n";
            }
        }
        else if (opcion == 3) {
            //  Reporte completo 
            std::cout << "\nCodigo  | Nombre               | Stock | Precio\n";
            std::cout << "------------------------------------------------\n";
            for (int i = 0; i < numProductos; i++) {
                // Alinear un poco el nombre (padding simple)
                std::string nom = nombres[i];
                if ((int)nom.size() < 20) nom.append(20 - (int)nom.size(), ' ');
                else nom = nom.substr(0, 20); // si es muy largo, lo corto
                std::cout << codigos[i] << "     | " << nom << " |  " << stocks[i] << "   | $" << precios[i] << "\n";
            }
        }
        else if (opcion == 4) {
            // producto mas caro 
            if (numProductos == 0) {
                std::cout << "No hay productos.\n";
            } else {
                int idxMax = 0;
                for (int i = 1; i < numProductos; i++) {
                    if (precios[i] > precios[idxMax]) idxMax = i;
                }
                std::cout << "Mas caro: " << nombres[idxMax] << " ($" << precios[idxMax] << ")\n";
            }
        }
        else if (opcion == 5) {
            std::cout << "Fin del sistema. Bye!\n";
        }
        else {
            std::cout << "Opcion invalida.\n";
        }

    } while (opcion != 5);

    return 0;
}
