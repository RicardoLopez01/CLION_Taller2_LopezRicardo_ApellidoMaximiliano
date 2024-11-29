//
// Created by lopez on 23-11-2024.
//

#include "Pedido.h"
#include <sstream>
#include <algorithm>

Pedido::Pedido(int id, const std::string& nombre, const std::string& apellido, const std::vector<std::string>& productos, int horaPedido)
    : id(id), nombreCliente(nombre), apellidoCliente(apellido), productos(productos), horaPedido(horaPedido), estado("Pendiente"), prioridad(0) {}

// Getters
int Pedido::getId() const {return id;}

std::string Pedido::getNombreCliente() const { return nombreCliente; }

std::string Pedido::getApellidoCliente() const { return apellidoCliente; }

std::vector<std::string> Pedido::getProductos() const { return productos; }

int Pedido::getHoraPedido() const { return horaPedido; }

std::string Pedido::getEstado() const { return estado; }

int Pedido::getPrioridad() const { return prioridad; }



// sets
void Pedido::setEstado(std::string nuevoEstado) { estado = nuevoEstado; }

void Pedido::calcularPrioridad(int horaActual) {
    int tiempoEspera = horaActual - horaPedido;
    prioridad = productos.size() * tiempoEspera; // usar formula para estoo CPP * (HA - HP)
    }

// Métodos auxiliares
std::string Pedido::toString() const {
    std::ostringstream os;
    os << "ID: " << id << "\n"
       << "Nombre: " << nombreCliente << "\n"
       << "Apellido: " << apellidoCliente << "\n"
       << "Hora del pedido: " << horaPedido << "\n"
       << "Prioridad: " << prioridad << "\n"
       << "Productos:\n";

    for (const auto& producto : productos) {
        os << "  - " << producto << "\n";
    }

    return os.str();
}
enum class EstadoPedido {
    Pendiente,
    enPreparacion,
    Completado,
    Cancelado
};

enum class TipoCliente {
    Presencial,
    Repartidor
};
TipoCliente tipoCliente;

void Pedido::agregarProducto(const std::string& producto) {
    productos.push_back(producto);
}

void Pedido::eliminarProducto(const std::string& producto) {
    auto it = std::find(productos.begin(), productos.end(), producto);
    if (it != productos.end()) productos.erase(it);
}
