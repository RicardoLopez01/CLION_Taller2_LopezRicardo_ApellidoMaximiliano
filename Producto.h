//
// Created by lopez on 23-11-2024.
//

#ifndef PRODUCTO_H
#define PRODUCTO_H

#include <string>

class Producto {
private:
    int id;
    std::string nombre;
    int precio;

public:

    Producto(int id, const std::string& nombre, int precio);

    // getsets
    int getId() const;
    std::string getNombre() const;
    int getPrecio() const;


    std::string toString() const;


};

#endif