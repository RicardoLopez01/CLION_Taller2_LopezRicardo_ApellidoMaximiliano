//
// Created by lopez on 23-11-2024.
//

#include "Pedido.h"
#include <sstream>

Pedido::Pedido(int id, const std::string& nombre, const std::string& apellido, const std::vector<std::string>& productos, int horaPedido)
    : id(id), nombreCliente(nombre), apellidoCliente(apellido), productos(productos), horaPedido(horaPedido), estado(true), prioridad(0) {}

// Getters
int Pedido::getId() const {return id;}

std::string Pedido::getNombreCliente() const { return nombreCliente; }

std::string Pedido::getApellidoCliente() const { return apellidoCliente; }

std::vector<std::string> Pedido::getProductos() const { return productos; }

int Pedido::getHoraPedido() const { return horaPedido; }

bool Pedido::getEstado() const { return estado; }

int Pedido::getPrioridad() const { return prioridad; }



// sets
void Pedido::setEstado(bool nuevoEstado) { estado = nuevoEstado; }

void Pedido::calcularPrioridad(int horaActual) {
    int tiempoEspera = horaActual - horaPedido;
    prioridad = productos.size() * tiempoEspera; // CPP * (HA - HP)
    }

// Métodos auxiliares
std::string Pedido::toString() const {
    std::ostringstream os;
    os << "ID: " << id << "\n"
       << "Nombre: " << nombreCliente << "\n"
       << "Apellido: " << apellidoCliente << "\n"
       << "Estado: " << (estado ? "Activo" : "Completado") << "\n"
       << "Hora del pedido: " << horaPedido << "\n"
       << "Prioridad: " << prioridad << "\n"
       << "Productos:\n";

    for (const auto& producto : productos) {
        os << "  - " << producto << "\n";
    }

    return os.str();
}
