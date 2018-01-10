cmake_minimum_required(VERSION 3.8)
project(ex2)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        Board.cpp
        Board.h
        ex2.cpp
        ex2.h
        Game.cpp
        Game.h
        Piece.cpp
        Piece.h
        Square.cpp
        Square.h)

add_executable(ex2 ${SOURCE_FILES})