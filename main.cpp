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




//Funciones para el menu principal.
    void crearPedidoUsuario();
    void entregarPedido();
    void cancelarPedido();
    void buscarPedido();
    void menuEstadisticas();
    void cerrarSistema();


    void mostrarMenu() {
        const std::string archivo = "productos_grill_of_victory.txt";

        // Crear instancia
        sistemaPedidos sistema;


        // Verificar si el archivo existe antes de cargar
        if (!std::filesystem::exists(archivo)) {
            std::cerr << "Error: No se encontró el archivo '" << archivo << "'. Asegúrese de que esté en la carpeta correcta.\n";
            return 1; // Salir del programa con error
        }

        // Intentar cargar productos
        try {
            sistema.cargarProductosDesdeArchivo(archivo);
            std::cout << "Productos cargados automáticamente desde '" << archivo << "'.\n";
        } catch (const std::exception& e) {
            std::cerr << "Error al cargar los productos: " << e.what() << "\n";
            return 1; // Salir del programa con error
        }
        int opcion;


        std::cout << "************************\n";
        std::cout << "     Menu principal\n";
        std::cout << "************************\n";
        std::cout << "1) Crear pedido\n";
        std::cout << "2) Entregar pedido\n";
        std::cout << "3) Cancelar pedido\n";
        std::cout << "4) Buscar pedido\n";
        std::cout << "5) Menu estadisticas\n";
        std::cout << "6) Cerrar sistema\n";
        std::cout << "Ingrese su opción: ";

        switch (opcion) { // Menu principal
            case 1:
                if(productos.empty()) {
                    std::cout<<"No hay productos cargados.\n";
                }else {
                    Pedido nuevoPedido = crearPedidoUsuario();
                    procesarPedidos({nuevoPedido});
                    std::cout<<"Pedido creado\n";
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

            case 5:menuEstadisticas();
            break;

            case 6:cerrarSistema();
            break;

            default:
                std::cout << "Opcion no valida";
                std::cout << "Ingrese una opcion valida!";
                break;
        }
        mostrarMenu();
    }




        void crearPedidoUsuario(){

        }

        void entregarPedido(){

        }

        void cancelarPedido(){

        }

        void buscarPedido() {

        }

        void menuEstadisticas() {

        }

        void cerrarSistema() {
            std::cout<<"Saliendo del sistema...\n";
        }


        const std::string archivo = "productos_grill_of_victory.txt";
        sistemaPedidos.cargarProductosDesdeArchivo(archivo);
        std::cout << "Productos cargados automáticamente desde '" << archivo << "'.\n";

    int main() {

        AVL avl;
        MinHeap minHeap;
        mostrarMenu();





        return 0;
    }





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
