//
// Created by lopez on 23-11-2024.
//

#include <algorithm>
#include "SistemaPedidos.h"
#include <iostream>
#include <fstream>
#include <sstream>

sistemaPedidos::sistemaPedidos() : productos(), heapPedidos(), historialPedidos() {}












Pedido sistemaPedidos::crearPedidoUsuario() {
    std::string nombre, apellido;
    std::vector<std::string> productosSeleccionados;
    int idProducto;

    std::cout << "Ingrese el nombre del cliente: ";
    std::cin >> nombre;
    std::cout << "Ingrese el apellido del cliente: ";
    std::cin >> apellido;

    std::cout << "Productos disponibles:";
    for (const Producto& p : productosCargados) {
        std::cout << p.toString() << std::endl;
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
            std::cout << "ID no valida. Intente nuevamente." << std::endl;
        }
    }

    int horaActual = static_cast<int>(time(nullptr));
    Pedido nuevoPedido(1, nombre, apellido, productosSeleccionados, horaActual);
    std::cout << "Pedido creado:" << nuevoPedido.toString() << std::endl;
    return nuevoPedido;
}

std::vector<Pedido> SistemaPedidos::generarPedidosAleatorios(int cantidad) {
    std::vector<Pedido> pedidos;
    std::vector<std::string> nombres = {"Anuel", "Benito", "Cosculluela", "Don Omar", "El"};
    std::vector<std::string> apellidos = {"A", "B", "C", "D", "E"};

    srand(time(nullptr)); // Inicializar semilla aleatoria

    if(productosCargados.empty()) {
        std::cout << "No productos cargados encontrado." << std::endl;
        return pedidos;
    }
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
        calcularPrioridadPedido(static_cast<int>(time(nullptr)));
        avl.insertar(pedido);
        if (pedido.getPrioridad() > 0) {
            minHeap.insertar(pedido);
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
    //Este codigo es reciclado del profesor, deberia funcar, pero primero revisemos si funciona con el nombre del archivo en si en vez de la ruta
    //ID,Nombre del Producto,Precio (CLP)
    std::ifstream archivoProductos("productos_grill_of_victory.txt");
    if (!archivoProductos.is_open()) {
        std::cerr << "No se pudo abrir el archivo: " << archivo << std::endl;
        return;
    }

    std::vector<Producto> productos;
    productos.clear();
    std::string linea;

    while (std::getline(archivoProductos, linea)) {
        std::stringstream ss(linea);
        int id, precio;
        std::string nombre;

        if (ss >> id) {
            ss.ignore();
            std::getline(ss, nombre, ','); // Leer hasta coma
            ss >> precio;

            Producto producto(id, nombre, precio);
            productos.push_back(producto);
        } else {
            std::cerr << "Error al leer la linea" << linea << std::endl;
        }
    }

    archivoProductos.close();

    // Almacenar los productos en el sistema
    this->productos = productos; // Asume que la clase tiene un miembro `productos`

    // Mostrar productos cargados (opcional para verificar)
    for (const Producto& p : productos) {
        std::cout << p.toString() << std::endl;
    }
}
size_t sistemaPedidos::totalPedidos() const {
    return historialPedidos.size() + heapPedidos.size();
}

size_t sistemaPedidos::pedidosEntregados() const {
    return std::count_if(historialPedidos.begin(), historialPedidos.end(), [](const Pedido& pedido) {
        return !pedido.getEstado();
    });
}

size_t sistemaPedidos::pedidosCancelados() const {
    return historialPedidos.size() - pedidosEntregados();
}




















    void sistemaPedidos::mostrarMenu() {
    bool salir = false;
    while (!salir) {
        std::cout << "************************";
        std::cout << "     Menu principal";
        std::cout << "************************";
        std::cout << "Ingrese su opción: ";
        std::cout << "1) Crear pedido ";
        std::cout << "2) Entregar pedido ";
        std::cout << "3) Cancelar pedido ";
        std::cout << "4) Buscar pedido ";
        std::cout << "5) Menu estadisticas ";
        std::cout << "6) Cerrar sistema ";

        int opcion;
        std::cin >> opcion;
        std::cin.ignore();

        switch (opcion) {
            case 1:
                if (productos.empty()) {
                    std::cout << "No hay productos cargados. No se puede crear un pedido.\n";
                } else {
                    Pedido nuevoPedido = crearPedidoUsuario();
                    procesarPedidos({nuevoPedido});
                    std::cout << "Pedido creado y procesado.\n";
                }
            break;

            case 2:
                entregarPedido();
            break;

            case 3:
                cancelarPedido();
            break;

            case 4:
                buscarPedido();
            break;

            case 5:
                mostrarEstadisticas();
            break;

            case 6:
                std::cout << "Saliendo del sistema...\n";
            salir = true;
            break;

            default:
                std::cout << "Opción no válida. Intente nuevamente.\n";
        }
    }
}
}