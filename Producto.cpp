//
// Created by lopez on 23-11-2024.
//

#include "Producto.h"
#include <sstream>


Producto::Producto(int id, const std::string& nombre, int precio)
    : id(id), nombre(nombre), precio(precio) {}


int Producto::getId() const { return id; }

std::string Producto::getNombre() const { return nombre; }

int Producto::getPrecio() const { return precio; }


std::string Producto::toString() const {
    std::stringstream ss;
    ss << id << ", " << nombre << ", " << precio;
    return ss.str();
}
