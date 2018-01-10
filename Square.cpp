//
// Created by jherskow on 1/8/18.
//

#include "Square.h"


Square::~Square()
{

}

Square::Square(int letter, int number)
{
    this->letter = letter;
    this->number = number;
    this->isEmpty = true;
}

void Square::setPiece(Piece *piece)
{
    this->piece = piece;
    isEmpty = false;
}

Piece* Square::getPiece()
{
    if (Square::isEmpty())
    {
        return nullptr;
    }
    return piece;
}


bool Square::isEmpty()
{
    return Square::isEmpty;
}

void Square::deletePiece()
{
    isEmpty = true;
    this->piece = nullptr;
}
