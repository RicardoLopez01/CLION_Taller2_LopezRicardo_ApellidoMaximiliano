#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
#include "AVL.h"
#include "MinHeap.h"
#include "Pedido.h"
#include "Producto.h"
#include <filesystem>
#include "sistemaPedidos.h"

using namespace std;
void crearPedido();
void entregarPedido();
void cancelarPedido();
void buscarPedido();
void cerrarSistema();
void menuEstadisticas();

int main() {
    sistemaPedidos sistema({});
    sistema.cargarProductosDesdeArchivo("productos_grill_of_victory.txt");

    int opcion = 0;

    do {
        std::cout << "=**** Sistema de Gestion de Pedidos ****=\n";
        std::cout << "Seleccione una opcion: ";
        std::cout << "1) Crear un pedido de usuario\n";
        std::cout << "2) Generar pedidos aleatorios\n";
        std::cout << "3) Mostrar pedidos en AVL\n";
        std::cout << "4) Mostrar pedidos en MinHeap\n";
        std::cout << "5) Salir\n";

        std::cin >> opcion;

        switch (opcion) {
            case 1: {
                // Crear un pedido de usuario
                Pedido nuevoPedido = sistema.crearPedidoUsuario();
                // Procesar el pedido (insertarlo en AVL y MinHeap)
                std::vector<Pedido> pedidos = {nuevoPedido};
                sistema.procesarPedidos(pedidos);
                break;
            }
            case 2: {
                // Generar pedidos aleatorios (por ejemplo, 10 pedidos)
                std::vector<Pedido> pedidosAleatorios = sistema.generarPedidosAleatorios(10);
                // Procesar estos pedidos
                sistema.procesarPedidos(pedidosAleatorios);
                break;
            }
            case 3: {
                // Mostrar los pedidos en el AVL
                std::cout << "Pedidos en el árbol AVL:\n";
                sistema.mostrarAVL();
                break;
            }
            case 4: {
                // Mostrar los pedidos en el MinHeap
                std::cout << "Pedidos en el MinHeap:\n";
                sistema.mostrarMinHeap();
                break;
            }
            case 5:
                std::cout << "Saliendo del sistema...\n";
            break;

            default:
                std::cout << "Opción no válida. Intente de nuevo.\n";
            break;
        }

    } while (opcion != 5);

    return 0;




}

        AVL avl;
        MinHeap minHeap;





    Pedido crearPedidoUsuario(const std::vector<Producto>& productos) {
    std::string nombre, apellido;
    std::vector<std::string> productosSeleccionados;
    int idProducto;

    std::cout << "Ingrese el nombre del cliente: ";
    std::cin >> nombre;
    std::cout << "Ingrese el apellido del cliente: ";
    std::cin >> apellido;

    std::cout << "Productos disponibles:\n";
    for (const Producto& p : productos) {
        std::cout << p.toString() << std::endl;
    }

    std::cout << "Ingrese los IDs de los productos seleccionados (0 para terminar): " << std::endl;
    while (true) {
        std::cin >> idProducto;
        if (idProducto == 0) break;
        auto it = std::find_if(productos.begin(), productos.end(), [idProducto](const Producto& p) {
            return p.getId() == idProducto;
        });
        if (it != productos.end()) {
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

std::vector<Pedido> generarPedidosAleatorios(int cantidad, const std::vector<Producto>& productos) {
    std::vector<Pedido> pedidos;
    std::vector<std::string> nombres = {"Juan", "Ana", "Luis", "Maria", "Carlos"};
    std::vector<std::string> apellidos = {"Perez", "Lopez", "Gomez", "Diaz", "Torres"};

    srand(time(nullptr)); // Inicializar semilla aleatoria

    for (int i = 0; i < cantidad; ++i) {
        std::string nombre = nombres[rand() % nombres.size()];
        std::string apellido = apellidos[rand() % apellidos.size()];

        int numProductos = rand() % 5 + 1; // 1 a 5 productos
        std::vector<std::string> productosSeleccionados;

        for (int j = 0; j < numProductos; ++j) {
            productosSeleccionados.push_back(productos[rand() % productos.size()].getNombre());
        }

        int horaActual = static_cast<int>(time(nullptr));
        pedidos.emplace_back(i + 1, nombre, apellido, productosSeleccionados, horaActual);
    }

    return pedidos;
}

void procesarPedidos(const std::vector<Pedido>& pedidos, AVL& avl, MinHeap& minHeap) {
    for (const Pedido& pedido : pedidos) {
        avl.insertar(pedido);
        if (pedido.getPrioridad() > 0) {
            minHeap.insertar(pedido);
        }
    }
}
