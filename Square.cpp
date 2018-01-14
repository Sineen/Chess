//
// Created by jherskow on 1/8/18.
//

#include "Square.h"


Square::Square(int number, int letter)
{
    this->letter = letter;
    this->number = number; //todo check
    this-> piece = nullptr;
    this->isEmptty = true;
    this->color = ((letter%2==0 && number%2==0) || (letter%2!=0 && number%2!=0) ) ? black: white;
    //TODO WHY Square is black or white  not green or blue ?????
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

piece_color Square::getColor() const
{
    return color;
}

int Square::getNumber() const
{
    return number;
}

bool Square::compareSquareTo(const Square& square1) const
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

Square::Square()
{
    letter = 0;
    number = 0;
}

