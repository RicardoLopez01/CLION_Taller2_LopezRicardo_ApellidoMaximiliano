cmake_minimum_required(VERSION 3.29)
project(Taller2_LopezRicardo_ApellidoMaximiliano)

set(CMAKE_CXX_STANDARD 20)

add_executable(Taller2_LopezRicardo_ApellidoMaximiliano main.cpp
        Pedido.cpp
        Pedido.h
        AVL.cpp
        AVL.h
        MinHeap.cpp
        MinHeap.h
        sistemaPedidos.cpp
        sistemaPedidos.h
        Producto.cpp
        Producto.h
)
