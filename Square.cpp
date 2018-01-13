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
    this-> piece = nullptr;
    this->isEmptty = true;
}

void Square::setPiece(Piece *piece)
{
    this->piece = piece;
    isEmptty = false;
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
    return Square::isEmptty;
}

void Square::deletePiece()
{
    isEmptty = true;
    this->piece = nullptr;
}
