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

std::shared_ptr<NodoAVL> AVL::eliminarNodo(const std::shared_ptr<NodoAVL>& nodo, int id) {
    if(nodo) return nullptr;
    if (id < nodo->pedido.getId()) {
        nodo->izquierda = eliminarNodo(nodo->izquierda, id);
    } else if(id > nodo->pedido.getId()) {
        nodo->derecha = eliminarNodo(nodo->derecha, id);
    }else {
        if(!nodo->izquierda || !nodo->derecha) {
            return nodo->izquierda ? nodo->izquierda : nodo->derecha;
        }
        auto siguiente = nodo->derecha;
        while(siguiente->izquierda) siguiente = siguiente->izquierda;
        nodo->pedido = siguiente->pedido;
        nodo->derecha = eliminarNodo(nodo->derecha, siguiente->pedido.getId());
    }
    nodo->altura = std::max(obtenerAltura(nodo->izquierda) obtenerAltura(nodo->derecha)) + 1;
    int balance = obtenerBalance(nodo);
    if (balance > 1 && obtenerBalance(nodo->izquierda) >= 0) return rotacionDerecha(nodo);
    if (balance > 1 && obtenerBalance(nodo->izquierda) < 0) {
        nodo->izquierda = rotacionIzquierda(nodo->izquierda);
        return rotacionDerecha(nodo);
    }
    if (balance < -1 && obtenerBalance(nodo->derecha) <= 0) return rotacionIzquierda(nodo);
    if (balance < -1 && obtenerBalance(nodo->derecha) > 0) {
        nodo->derecha = rotacionDerecha(nodo->derecha);
        return rotacionIzquierda(nodo);
    }
    return nodo;
}

std::shared_ptr<NodoAVL> AVL::buscarNodo(const std::shared_ptr<NodoAVL>& nodo, int id) const {
    if (!nodo || nodo->pedido.getId() == id) return nodo;
    if (id < nodo->pedido.getId()) return buscarNodo(nodo->izquierda, id);
    return buscarNodo(nodo->derecha, id);
}

Pedido AVL::buscar(int id) const {
    auto nodo = buscarNodo(raiz, id);
    if (!nodo) throw std::runtime_error("Pedido no encontrado");
    return nodo->pedido;
}

void AVL::eliminar(int id) {
    raiz = eliminarNodo(raiz, id);
}

void AVL::insertar(const Pedido& pedido) {
    raiz = insertarNodo(raiz, pedido);
}

void AVL::actualizarEstado(int id, const std::string& nuevoEstado) {
    auto nodo = buscarNodo(raiz, id);
    if (!nodo) throw std::runtime_error("Pedido no encontrado");
    nodo->pedido.setEstado(nuevoEstado.data()); // Supone que Pedido tiene un método setEstado()
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