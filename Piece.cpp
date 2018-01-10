//
// Created by jherskow on 1/8/18.
//

#include "Piece.h"

set<Square> Piece::_getPawns(Board board)
{
    return set<Square>();
}

Piece::Piece(piece_type type, piece_color color, Square square)
{
    this->type=type;
    this->color=color;
    this.square=square;
}

void Piece::setSquare(Square square)
{

}

set<Square> Piece::ReturnSquaresInRange()
{
    return set<Square>();
}

set<Square> Piece::_getDiag(Board& board)
{
    set<Square> squares = set<Square>(){
        set<Square> set = set<Square>();


    }
}

set<Square> Piece::_getRows(Board board)
{
    return set<Square>();
}

set<Square> Piece::_getColumes(Board board)
{
    return set<Square>();
}

set<Square> Piece::_getKnights(Board board)
{
    return set<Square>();
}

set<Square> Piece::_getKing(Board board)
{
    return set<Square>();
}

set<Square> Piece::_getQueen(Board board)
{
    return set<Square>();
}
