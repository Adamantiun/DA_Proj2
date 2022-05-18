cmake_minimum_required(VERSION 3.20.2)
project(DA_Proj2)

set(CMAKE_CXX_STANDARD 14)

add_executable(DA_Proj2 codigo/main.cpp codigo/Interface/System.h codigo/Interface/System.cpp
        codigo/Controller.cpp codigo/Controller.h codigo/Interface/Menu.h codigo/Interface/Menu.cpp
        codigo/StopEdge.h codigo/StopEdge.cpp codigo/Line.cpp codigo/Line.h
        codigo/Graph.cpp codigo/Graph.h codigo/minHeap.h)
