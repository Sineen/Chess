//
// Created by jherskow on 1/8/18.
//

#ifndef CPP_SQUARE_H
#define CPP_SQUARE_H

#define SQUARE_SET Square , squareHasher , squareComparator

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

	bool compareSquareTo(const Square& square1) const;

};

struct squareHasher
{
    std::size_t operator()(const Square & square) const
    {
        return (hash<int>()(square.getLetter()) ^ (hash<int>()(square.getNumber()) << 1)) >> 1;
    }
};


// Custom comparator that compares square
struct squareComparator
{
    bool
    operator()(const Square & square1, const Square & square2) const
    {
        return square1.compareSquareTo(square2);
    }
};


#endif //CPP_SQUARE_H
