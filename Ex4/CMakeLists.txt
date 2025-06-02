cmake_minimum_required(VERSION 3.30)
project(Ex4)

set(CMAKE_CXX_STANDARD 20)

add_executable(Ex4 main.cpp
        MyContainer.tpp
        MyContainer.hpp
        AscendingOrder.hpp
        DescendingOrder.hpp
        SideCrossOrder.hpp
        ReverseOrder.hpp
        Order.hpp
        MiddleOutOrder.hpp
        test.cpp)
