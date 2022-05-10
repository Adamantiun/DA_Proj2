cmake_minimum_required(VERSION 3.21)
project(DA_Proj2)

set(CMAKE_CXX_STANDARD 14)

add_executable(DA_Proj2 codigo/main.cpp codigo/Interface/System.h codigo/Interface/System.cpp
        codigo/Controller.cpp codigo/Controller.h codigo/Interface/Menu.h codigo/Interface/Menu.cpp
        codigo/Order.h codigo/Order.cpp codigo/Truck.h codigo/Truck.cpp)
