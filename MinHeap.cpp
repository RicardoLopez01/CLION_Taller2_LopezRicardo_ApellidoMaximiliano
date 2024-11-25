//
// Created by lopez on 23-11-2024.
//

#include "MinHeap.h"

MinHeap::MinHeap() {}

void MinHeap::heapifyUp(int index) {
    if (index == 0) return;

    int parent = (index - 1) / 2;
    if (heap[index].getPrioridad() < heap[parent].getPrioridad()) {
        std::swap(heap[index], heap[parent]);
        heapifyUp(parent);
    }
}

void MinHeap::heapifyDown(int index) {
    int left = 2 * index + 1;
    int right = 2 * index + 2;
    int smallest = index;

    if (left < heap.size() && heap[left].getPrioridad() < heap[smallest].getPrioridad()) {
        smallest = left;
    }
    if (right < heap.size() && heap[right].getPrioridad() < heap[smallest].getPrioridad()) {
        smallest = right;
    }
    if (smallest != index) {
        std::swap(heap[index], heap[smallest]);
        heapifyDown(smallest);
    }
}

void MinHeap::insertar(const Pedido& pedido) {
    heap.push_back(pedido);
    heapifyUp(heap.size() - 1);
}

Pedido MinHeap::extraerMin() {
    if (heap.empty()) throw std::runtime_error("El heap está vacío.");

    Pedido min = heap[0];
    heap[0] = heap.back();
    heap.pop_back();
    heapifyDown(0);
    return min;
}

Pedido MinHeap::obtenerMin() const {
    if (heap.empty()) throw std::runtime_error("El heap está vacío.");
    return heap[0];
}

bool MinHeap::estaVacio() const {
    return heap.empty();
}

void MinHeap::mostrar() const {
    for (const auto& pedido : heap) {
        std::cout << pedido.toString() << std::endl;
    }
}