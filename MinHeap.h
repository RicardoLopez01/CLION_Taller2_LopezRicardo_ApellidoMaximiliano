//
// Created by lopez on 23-11-2024.
//

#ifndef MINHEAP_H
#define MINHEAP_H

#include "Pedido.h"
#include <vector>
#include <iostream>

class MinHeap {
private:
    std::vector<Pedido> heap;

    // Métodos auxiliares
    void heapifyUp(int index);
    void heapifyDown(int index);

public:
    MinHeap();

    void insertar(const Pedido& pedido);
    Pedido extraerMin(); // menor priodidad
    Pedido obtenerMin() const; // llama al menor prioridad pa saber como es
    bool estaVacio() const;
    void mostrar() const;
};

#endif // MINHEAP_H