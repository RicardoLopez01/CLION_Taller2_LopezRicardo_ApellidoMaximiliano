//
// Created by lopez on 23-11-2024.
//

#ifndef AVL_H
#define AVL_H

#include "Pedido.h"
#include <memory>
#include <iostream>

struct NodoAVL {
    Pedido pedido;
    int altura;
    std::shared_ptr<NodoAVL> izquierda;
    std::shared_ptr<NodoAVL> derecha;

    NodoAVL(const Pedido& pedido);
};

class AVL {
private:
    std::shared_ptr<NodoAVL> raiz;

    // Métodos auxiliares
    int obtenerAltura(const std::shared_ptr<NodoAVL>& nodo) const;
    int obtenerBalance(const std::shared_ptr<NodoAVL>& nodo) const;
    std::shared_ptr<NodoAVL> rotacionDerecha(const std::shared_ptr<NodoAVL>& nodo);
    std::shared_ptr<NodoAVL> rotacionIzquierda(const std::shared_ptr<NodoAVL>& nodo);
    std::shared_ptr<NodoAVL> insertarNodo(const std::shared_ptr<NodoAVL>& nodo, const Pedido& pedido);
    std::shared_ptr<NodoAVL> eliminarNodo(const std::shared_ptr<NodoAVL>& nodo, int id);
    std::shared_ptr<NodoAVL> buscarNodo(const std::shared_ptr<NodoAVL> &nodo, int id) const;

    Pedido buscar(int id) const;
    void eliminar(int id);
    void mostrarRecursivo(const std::shared_ptr<NodoAVL>& nodo) const;

public:
    AVL();

    void insertar(const Pedido& pedido);

    void actualizarEstado(int id, const std::string &nuevoEstado);

    void mostrar() const;
};

#endif // AVL_H