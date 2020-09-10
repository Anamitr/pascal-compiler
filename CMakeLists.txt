cmake_minimum_required(VERSION 3.15)
project(pascal-compiler)

set(CMAKE_CXX_STANDARD 14)

add_executable(pascal-compiler main.cpp global.h  Emitter.cpp Emitter.h Entry.cpp Entry.h Decoder.cpp Decoder.h SymbolTable.cpp SymbolTable.h util.cpp util.h)