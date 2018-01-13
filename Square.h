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
    piece_color color;

public:

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

    piece_color getColor() const;

    int getNumber() const;

	bool compareSquareTo(Square square2);

};





#endif //CPP_SQUARE_H
