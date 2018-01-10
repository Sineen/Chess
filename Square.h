//
// Created by jherskow on 1/8/18.
//

#ifndef CPP_SQUARE_H
#define CPP_SQUARE_H


#include "Piece.h"

class Square
{

public:
    Piece piece;
    int letter, number;

    /**
    * @brief Contructor.
    */
    Square(Piece piece);

    /**
    * @brief setPiece.
    */
    void setPiece(Piece piece);

    /**
    * @brief getPiece.
    */
    Piece getPiece();

    /**
    * @brief empty.
    */
    void empty();

};


#endif //CPP_SQUARE_H
