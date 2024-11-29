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

int main() {
    sistemaPedidos sistema({});
    sistema.cargarProductosDesdeArchivo("productos_grill_of_victory.txt");

    int opcion = 0;

    do {
        cout << "" << endl;
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
                // Procesar el pedido
                std::vector<Pedido> pedidos = {nuevoPedido};
                sistema.procesarPedidos(pedidos);
                break;
            }
            case 2: {
                // Generar pedidos aleatorios
                std::vector<Pedido> pedidosAleatorios = sistema.generarPedidosAleatorios(10);
                // Procesar estos pedidos
                sistema.procesarPedidos(pedidosAleatorios);
                break;
            }
            case 3: {
                // Muestra los pedidos en el AVL
                std::cout << "Pedidos en el arbol AVL:\n";
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
                std::cout << "Opcion no valida. Intenta de nuevo.\n";
            break;
        }

    } while (opcion != 5);

    return 0;




}


        AVL avl;
        MinHeap minHeap;





