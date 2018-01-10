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
    this->square=square;
    this->letter = square.letter;
    this->number = square.number;
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
    set<Square> squares = set<Square>();

    // do NE

    for (int i = number, j = letter; i<7, j<7; ++i, ++j)
    {
        if (board.squares[i][j].isEmpty){ squares.emplace(board.squares[i][j]); }
        else if (board.squares[i][j].getPiece().color != color ){
            squares.emplace(board.squares[i][j]);
            break;
        }
        else // this is a friendly piece
        {
            break;
        }
    }

    // do SE

    for (int i = i = number, j = letter; i<7, j<7; ++i, ++j)
    {
        if (board.squares[i][j].isEmpty){ squares.emplace(board.squares[i][j]); }
        else if (board.squares[i][j].getPiece().color != color ){
            squares.emplace(board.squares[i][j]);
            break;
        }
        else // this is a friendly piece
        {
            break;
        }
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
