//
// Created by lopez on 23-11-2024.
//

#include "Pedido.h"

#include <iostream>

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
    std::cout << "ID: " << id << std::endl;
    std::cout << "Nombre: " << nombreCliente << std::endl;
    std::cout << "Apellido: " << apellidoCliente << std::endl;
    std::cout << "Estado: " << estado << std::endl;
    // std::cout << "Productos: " << productos << std::endl;

}
