//
// Created by lopez on 23-11-2024.
//

#ifndef SISTEMAPEDIDOS_H
#define SISTEMAPEDIDOS_H

#include "Producto.h"
#include "Pedido.h"
#include "AVL.h"  // El árbol AVL
#include "MinHeap.h" // El MinHeap
#include <vector>
#include <iostream>

class sistemaPedidos {
private:
    std::vector<Producto> productosCargados;  // Lista de productos cargados
    AVL avl;  // Árbol AVL para pedidos
    MinHeap minHeap;  // MinHeap para pedidos

public:
    // Constructor
    sistemaPedidos(const std::vector<Producto>& productos);

    // Mcrear un pedido del usuario
    Pedido crearPedidoUsuario();

    // generar pedidos aleatorios
    std::vector<Pedido> generarPedidosAleatorios(int cantidad);

    // Mprocesar los pedidos (insertarlos en AVL y MinHeap)
    void procesarPedidos(const std::vector<Pedido>& pedidos);

    //  mostrar el arbol AVL
    void mostrarAVL() const;

    // M mostrar el MinHeap
    void mostrarMinHeap() const;

    // Cargar productos desde archivo (utilizando el código de lectura que ya tienes)
    void cargarProductosDesdeArchivo(const std::string& archivo);
};

#endif  // SISTEMAPEDIDOS_H