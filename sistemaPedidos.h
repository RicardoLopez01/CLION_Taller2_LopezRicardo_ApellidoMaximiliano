//
// Created by lopez on 23-11-2024.
//

#ifndef SISTEMAPEDIDOS_H
#define SISTEMAPEDIDOS_H

#include <fstream>

#include "Producto.h"
#include "Pedido.h"
#include "AVL.h"
#include "MinHeap.h"
#include <vector>
#include <sstream>

class sistemaPedidos {

    AVL<Producto> productos; // arbol AVL para productos
    std::vector<Pedido> pedidos; // Vector para almacenar los pedidos realizados



    void cargarProducto(const std::string& linea);
    int calcularPrioridadPedido(const Pedido& pedido) const;

public:

    sistemaPedidos();
    std::vector<Producto> getProductos() const;

    void mostrarMenu();

    // Lee los productos desde archivo
    void cargarProductosDesdeArchivo(const std::string& archivo);
    AVL<Producto> getProductos() const;

    // crear un pedido del usuario
    Pedido crearPedidoUsuario();

    // Entrega
    void entregarPedido();

    // Cancela
    void cancelarPedido();

    //Busca
    void buscarPedido();

    //Muestra las estadisticas
    void mostrarEstadisticas();

    size_t totalPedidos() const;
    size_t pedidosEntregados() const;
    size_t pedidosCancelados() const;


    // procesar los pedidos (meterlos al AVL y MinHeap)
    void procesarPedidos(const std::vector<Pedido>& pedidos);



 // mostrar el árbol AVL
    void mostrarAVL() const;

    // mostrar el MinHeap
    void mostrarMinHeap() const;

    // generar pedidos aleatorios
    std::vector<Pedido> generarPedidosAleatorios(int cantidad);
};

#endif  // SISTEMAPEDIDOS_H