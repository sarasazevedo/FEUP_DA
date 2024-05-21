cmake_minimum_required(VERSION 3.27)
project(project2_RAOSUD)

set(CMAKE_CXX_STANDARD 11)

include_directories(.)
include_directories(src)

add_executable(project2_RAOSUD
        src/Interface.h
        src/main.cpp
        src/Interface.cpp
        src/Graph.cpp
        src/Graph.h
        src/Edge.cpp
        src/Edge.h
        src/Vertex.cpp
        src/Vertex.h
        src/RoutingManager.h
        src/RoutingManager.cpp
)