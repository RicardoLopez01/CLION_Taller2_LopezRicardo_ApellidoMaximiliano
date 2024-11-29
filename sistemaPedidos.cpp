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
    std::ifstream archivoProductos(archivo);
    if (!archivoProductos.is_open()) {
        std::cerr << "No se pudo abrir el archivo de productos" << std::endl;
        return;
    }

    std::string linea;
    while (std::getline(archivoProductos, linea)) {
        std::stringstream ss(linea);
        int id, precio;
        std::string nombre;

        if (ss >> id) {
            ss.ignore();
            std::getline(ss, nombre, ',');
            ss >> precio;
            Producto producto(id, nombre, precio);
            productosCargados.push_back(producto);
        }
    }
}