//
// Created by lopez on 23-11-2024.
//
#include <algorithm>
#include <iostream>
#include "AVL.h"
#include "MinHeap.h"
#include "SistemaPedidos.h"
#include <fstream>
#include <sstream>
#include "Pedido.h"
#include "Producto.h"
#include <filesystem>


sistemaPedidos::sistemaPedidos(const std::vector<Producto>& productos)
    : productosCargados(productos) {}

Pedido sistemaPedidos::crearPedidoUsuario() {
    std::string nombre, apellido;
    std::vector<std::string> productosSeleccionados;
    int idProducto;

    std::cout << "Ingrese el nombre del cliente: ";
    std::cin >> nombre;
    if (nombre.empty()) {
        std::cerr << "Error: El nombre no puede estar vacio" << std::endl;
        return Pedido(0, "", "", {}, 0); // Se devuelve vacio
    }


    std::cout << "Ingrese el apellido del cliente: ";
    std::cin >> apellido;
    if (apellido.empty()) {
        std::cerr <<  "El apellido no puede estar vacoo" << std::endl;
        return Pedido(0, "", "", {}, 0);
    }

    std::cout << "Ingrese los IDs de los productos seleccionados (0 para terminar): " << std::endl;
    while (true) {
        std::cin >> idProducto;
        if (idProducto == 0) break;
        auto it = std::find_if(productosCargados.begin(), productosCargados.end(), [idProducto](const Producto& p) {
            return p.getId() == idProducto;
        });
        if (it != productosCargados.end()) {
            productosSeleccionados.push_back(it->getNombre());
        } else {
            std::cout << "ID de producto no válido. Intente nuevamente." << std::endl;
        }
    }

    int horaActual = static_cast<int>(time(nullptr));
    Pedido nuevoPedido(1, nombre, apellido, productosSeleccionados, horaActual);
    std::cout << "Pedido creado:\n" << nuevoPedido.toString() << std::endl;
    return nuevoPedido;
}

std::vector<Pedido> sistemaPedidos::generarPedidosAleatorios(int cantidad) {
    std::vector<Pedido> pedidos;
    std::vector<std::string> nombres = {"Anito", "Benito", "Chamo", "Diosdado", "Omero"};
    std::vector<std::string> apellidos = {"El huerfanito", "Espinoza", "Ovimarlixion", "Dedo", "Esqueleto"};

    srand(time(nullptr)); // Inicializar semilla aleatoria

    for (int i = 0; i < cantidad; ++i) {
        std::string nombre = nombres[rand() % nombres.size()];
        std::string apellido = apellidos[rand() % apellidos.size()];

        int numProductos = rand() % 5 + 1; // 1 a 5 productos
        std::vector<std::string> productosSeleccionados;

        for (int j = 0; j < numProductos; ++j) {
            productosSeleccionados.push_back(productosCargados[rand() % productosCargados.size()].getNombre());
        }

        int horaActual = static_cast<int>(time(nullptr));
        pedidos.emplace_back(i + 1, nombre, apellido, productosSeleccionados, horaActual);
    }

    return pedidos;
}

void sistemaPedidos::procesarPedidos(const std::vector<Pedido>& pedidos) {
    for (const Pedido& pedido : pedidos) {
        try {
            avl.insertar(pedido);
            minHeap.insertar(pedido);
        } catch (const std::exception& e) {
            std::cerr << "Error al procesar el pedido con ID " << pedido.getId() << ": " << e.what() << std::endl;
        }
    }
}

void sistemaPedidos::mostrarAVL() const {
    avl.mostrar();
}

void sistemaPedidos::mostrarMinHeap() const {
    minHeap.mostrar();
}

void sistemaPedidos::cargarProductosDesdeArchivo(const std::string& archivo) {
    // Este código es reciclado del profesor, pero revisaremos si funciona con el nombre del archivo.
    // ID, Nombre del Producto, Precio (CLP)


    if (!std::filesystem::exists(archivo)) {
        std::cerr << "El archivo no existe en la ruta: " << archivo << std::endl;
        return;
    }

    // Usamos el archivo directamente con su nombre correcto.
    std::ifstream archivoProductos(archivo);  // Usamos la variable "archivo" para poner el nombre segun corresponda "productos_grill_of_victory.txt"


    if (!archivoProductos.is_open()) {
        std::cerr << "No se pudo abrir el archivo productos_grill_of_victory.txt." << std::endl;
        std::cerr << "Asegurate de que el archivo este en la misma carpeta que el ejecutable." << std::endl;
        return;
    }

    std::vector<Producto> productos;
    productos.clear();  // Aseguramos que el vector este vacío
    std::string linea;

    // Leemos linea por linea
    while (std::getline(archivoProductos, linea)) {
        std::stringstream ss(linea);  // Usamos stringstream para dividir
        int id, precio;
        std::string nombre;

        // se lee
        if (ss >> id) {
            ss.ignore();  // Ignoramos la coma despues del ID
            std::getline(ss, nombre, ',');  // Leemos nombre hasta la coma
            ss >> precio;  // Leemos el precio hasta

            Producto producto(id, nombre, precio);
            productos.push_back(producto);  // Añadimos el producto al vector
        } else {
            std::cerr << "Error al leer la línea: " << linea << std::endl;
        }
    }

    archivoProductos.close();  // Cerramos el archivo

    // Almacenamos los productos cargados en el sistema
    this->productosCargados = productos;


    for (const Producto& p : productos) {
        std::cout << p.toString() << std::endl;
    }
}