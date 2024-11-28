//
// Created by lopez on 23-11-2024.
//
#include <iostream>
#include "AVL.h"
#include "MinHeap.h"
#include "SistemaPedidos.h"

using namespace std;

class SistemaPedidos {
private:
    AVL<int, string> pedidos; // Almacena los pedidos con su ID como clave y detalles como valor.
    MinHeap<pair<int, int>> tiemposEntrega; // Gestiona los tiempos de entrega con pares iempo id

public:
    SistemaPedidos() {}

    void agregarPedido(int id, const string& detalles, int tiempoEntrega) {
        if (pedidos.find(id)) {
            cout << "El pedido con ID " << id << " ya existe." << endl;
            return;
        }
        pedidos.insert(id, detalles);
        tiemposEntrega.insert({tiempoEntrega, id});
        cout << "Pedido agregado: ID = " << id << ", Detalles = " << detalles << ", Tiempo de entrega = " << tiempoEntrega << " minutos." << endl;
    }

    void eliminarPedido(int id) {
        if (!pedidos.find(id)) {
            cout << "El pedido con ID " << id << " no existe." << endl;
            return;
        }
        pedidos.remove(id);

        // Reconstruccion de la MinHeap sin el pedido eliminado.
        MinHeap<pair<int, int>> nuevaHeap;
        while (!tiemposEntrega.isEmpty()) {
            auto actual = tiemposEntrega.extractMin();
            if (actual.second != id) {
                nuevaHeap.insert(actual);
            }
        }
        tiemposEntrega = nuevaHeap;

        cout << "Pedido con ID " << id << " eliminado." << endl;
    }

    void mostrarPedidos() {
        cout << "\nLista de pedidos:" << endl;
        pedidos.inOrderTraversal([](int id, const string& detalles) {
            cout << "ID: " << id << ", Detalles: " << detalles << endl;
        });
    }

    void obtenerPedidoPrioritario() {
        if (tiemposEntrega.isEmpty()) {
            cout << "No hay pedidos en la cola." << endl;
            return;
        }
        auto prioritario = tiemposEntrega.getMin();
        int id = prioritario.second;
        int tiempo = prioritario.first;
        string detalles;
        if (pedidos.find(id, detalles)) {
            cout << "Pedido prioritario: ID = " << id << ", Detalles = " << detalles << ", Tiempo de entrega = " << tiempo << " minutos." << endl;
        }
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


        // Mostrar productos cargados (opcional para verificar)
        for (const Producto& p : productos) {
            std::cout << p.toString() << std::endl;
        }
    }
};
