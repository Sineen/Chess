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
    bool isEmptty;

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

    int getLetter() const;

    int getNumber() const;

};

int Square::getLetter() const
{
    return letter;
}

int Square::getNumber() const
{
    return number;
}

#endif //CPP_SQUARE_H
