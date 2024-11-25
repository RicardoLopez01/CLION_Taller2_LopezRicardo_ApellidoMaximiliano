//
// Created by lopez on 23-11-2024.
//

#include "AVL.h"

NodoAVL::NodoAVL(const Pedido& pedido)
    : pedido(pedido), altura(1), izquierda(nullptr), derecha(nullptr) {}

AVL::AVL() : raiz(nullptr) {}

int AVL::obtenerAltura(const std::shared_ptr<NodoAVL>& nodo) const {
    return nodo ? nodo->altura : 0;
}

int AVL::obtenerBalance(const std::shared_ptr<NodoAVL>& nodo) const {
    return nodo ? obtenerAltura(nodo->izquierda) - obtenerAltura(nodo->derecha) : 0;
}

std::shared_ptr<NodoAVL> AVL::rotacionDerecha(const std::shared_ptr<NodoAVL>& nodo) {
    auto nuevaRaiz = nodo->izquierda;
    nodo->izquierda = nuevaRaiz->derecha;
    nuevaRaiz->derecha = nodo;

    nodo->altura = std::max(obtenerAltura(nodo->izquierda), obtenerAltura(nodo->derecha)) + 1;
    nuevaRaiz->altura = std::max(obtenerAltura(nuevaRaiz->izquierda), obtenerAltura(nuevaRaiz->derecha)) + 1;

    return nuevaRaiz;
}

std::shared_ptr<NodoAVL> AVL::rotacionIzquierda(const std::shared_ptr<NodoAVL>& nodo) {
    auto nuevaRaiz = nodo->derecha;
    nodo->derecha = nuevaRaiz->izquierda;
    nuevaRaiz->izquierda = nodo;

    nodo->altura = std::max(obtenerAltura(nodo->izquierda), obtenerAltura(nodo->derecha)) + 1;
    nuevaRaiz->altura = std::max(obtenerAltura(nuevaRaiz->izquierda), obtenerAltura(nuevaRaiz->derecha)) + 1;

    return nuevaRaiz;
}

std::shared_ptr<NodoAVL> AVL::insertarNodo(const std::shared_ptr<NodoAVL>& nodo, const Pedido& pedido) {
    if (!nodo) return std::make_shared<NodoAVL>(pedido);

    if (pedido.getId() < nodo->pedido.getId()) {
        nodo->izquierda = insertarNodo(nodo->izquierda, pedido);
    } else if (pedido.getId() > nodo->pedido.getId()) {
        nodo->derecha = insertarNodo(nodo->derecha, pedido);
    } else {
        return nodo; // No se permiten duplicados
    }

    nodo->altura = std::max(obtenerAltura(nodo->izquierda), obtenerAltura(nodo->derecha)) + 1;

    int balance = obtenerBalance(nodo);

    if (balance > 1 && pedido.getId() < nodo->izquierda->pedido.getId()) {
        return rotacionDerecha(nodo);
    }
    if (balance < -1 && pedido.getId() > nodo->derecha->pedido.getId()) {
        return rotacionIzquierda(nodo);
    }
    if (balance > 1 && pedido.getId() > nodo->izquierda->pedido.getId()) {
        nodo->izquierda = rotacionIzquierda(nodo->izquierda);
        return rotacionDerecha(nodo);
    }
    if (balance < -1 && pedido.getId() < nodo->derecha->pedido.getId()) {
        nodo->derecha = rotacionDerecha(nodo->derecha);
        return rotacionIzquierda(nodo);
    }

    return nodo;
}

void AVL::insertar(const Pedido& pedido) {
    raiz = insertarNodo(raiz, pedido);
}

void AVL::mostrarRecursivo(const std::shared_ptr<NodoAVL>& nodo) const {
    if (nodo) {
        mostrarRecursivo(nodo->izquierda);
        std::cout << nodo->pedido.toString() << std::endl;
        mostrarRecursivo(nodo->derecha);
    }
}

void AVL::mostrar() const {
    mostrarRecursivo(raiz);
}