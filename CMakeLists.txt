cmake_minimum_required(VERSION 3.15)
project(pascal-compiler)

set(CMAKE_CXX_STANDARD 14)

add_executable(pascal-compiler main.cpp global.h SymbolTable.cpp SymbolTable.h)