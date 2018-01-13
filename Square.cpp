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

int Square::getLetter() const
{
    return letter;
}

int Square::getNumber() const
{
    return number;
}

bool Square::compareSquareTo(Square square1)
{
	if ( square1.getLetter() == this->getLetter())
	{
		if(square1.getNumber() == this->getNumber())
		{
			return true;
		}
	}
	return false;
}
