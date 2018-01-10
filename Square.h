//
// Created by jherskow on 1/8/18.
//

#ifndef CPP_SQUARE_H
#define CPP_SQUARE_H


#include "Piece.h"

class Square
{
private:
    Piece* piece;
    int letter, number;
    bool isEmpty = true;

public:
    /**
     * Distructor;
     */
    virtual ~Square();

    /**
    * @brief Contructor.
    */
    Square(int letter, int number);

    /**
    * @brief setPiece.
    */
    void setPiece(Piece *piece);

    /**
    * @brief getPiece.
    */
    Piece* getPiece();

    /**
    * @brief getts if the square is emoty or not return true or false accordingly .
    */
    bool isEmpty();

    /**
     * if the square is not empty it will delete it
     */
    void deletePiece();

};


#endif //CPP_SQUARE_H
