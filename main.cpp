#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

#include "AVL.h"
#include "MinHeap.h"
#include "Pedido.h"
#include "Producto.h"

//Funciones para el menu principal.
    void crearPedido();
    void entregarPedido();
    void cancelarPedido();
    void buscarPedido();
    void menuEstadisticas();
    void cerrarSistema();




    void mostrarMenu() {
        int opcion;


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

        switch (opcion) { // Menu principal
            case 1:
                crearPedido();
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




        void crearPedido(){

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

        }




    int main() {

        AVL avl;
        MinHeap minHeap;







        // Este codigo es muy parecido la usado en el taller anterior, si bien el codigo funciona bien
        // tengo un error de que solamente lo lee cuando pones exactamente la direccion raiz del archivo txt
        // Si es posible reemplazar la direccion por la cual tenga en su computador, porfavor :D

        //ID,Nombre del Producto,Precio (CLP)
        std::ifstream archivoProductos("C:/Users/lopez/CLionProjects/Taller2_LopezRicardo-ApellidoMaximiliano/productos_grill_of_victory.txt"); //Aca poner la direccion raiz
        if (!archivoProductos.is_open()) {
            std::cerr << "No se pudo abrir el archivo de productos" << std::endl;
            return 1;
        }

        std::vector<Producto> productos;
        std::string linea;



        while (std::getline(archivoProductos, linea)) {
            std::stringstream ss(linea);
            int id, precio;
            std::string nombre;


            if (ss >> id) {
                ss.ignore();
                std::getline(ss, nombre, ','); // Leer hasta la coma
                ss >> precio;

                // crea objeto Producto y agrega al vector
                Producto producto(id, nombre, precio);
                productos.push_back(producto);
            } else {
                std::cerr << "Error al procesar la linea: " << linea << std::endl;
            }
        }

        // Mostrar los productos leídos
        for (const Producto& p : productos) {
            std::cout << p.toString() << std::endl;
        }








         mostrarMenu();







         archivoProductos.close();
        return 0;

    }





    Pedido crearPedidoDelUsuario(const std::vector<Producto>& productos) {
        std::string nombre;
        std::string apellido;
        std::vector<Producto> productosSeleccionados;
        int idProducto;

        std::cout << "Ingrese el nombre del cliente: ";
        std::cin >> nombre;
        std::cout << "Ingrese el apellido del cliente: ";
        std::cin >> apellido;

        std::cout << "Productos disponibles: ";
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
                productosSeleccionados.push_back(*it);
            } else {
                std::cout << "Producto no existente. Intente una opcion valida." << std::endl;
            }
        }

        //Pedido nuevoPedido(0,nombre, apellido, productosSeleccionados,nullptr);
        //std::cout << "Pedido creado:\n" << nuevoPedido.toString() << std::endl;
        //return nuevoPedido;




    }