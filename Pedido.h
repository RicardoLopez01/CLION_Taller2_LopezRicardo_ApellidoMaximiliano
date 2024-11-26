//
// Created by lopez on 23-11-2024.
//

#ifndef PEDIDO_H
#define PEDIDO_H
#include <string>
#include <vector>
#include <ctime>

class Pedido {

    int id;
    std::string nombreCliente;
    std::string apellidoCliente;
    std::vector<std::string> productos;
    time_t  horaPedido;   // Este es el formato que sale en las consideraciones.
    std::string estado;
    int  prioridad;

public:
    Pedido(int id, const std::string& nombre, const std::string& apellido, const std::vector<std::string>& productos, int horaPedido);


    //gets
    int getId() const;
    std::string getNombreCliente() const;
    std::string getApellidoCliente() const;
    std::vector<std::string> getProductos() const;
    int getHoraPedido() const;
    std::string getEstado() const;
    int getPrioridad() const;
    void agregarProducto(const std::string &producto);
    void eliminarProducto(const std::string &producto);

    // sets
    void setEstado(std::string nuevoEstado);
    void calcularPrioridad(int horaActual);


    std::string toString() const; // imprime pedido



};

#endif //PEDIDO_H
