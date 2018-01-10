//
// Created by jherskow on 1/8/18.
//

#include <algorithm>
#include "Piece.h"


Piece::Piece(piece_type type, piece_color color, Square& square)
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

set<Square> Piece::_getDiag()
{
    set<Square> squares = set<Square>();

    // do NE
    for (int i = number, j = letter; i<8, j<8; ++i, ++j){
        if (addAndCheckStop(squares, i, j) == 1){break;}
    }

    // do SE
    for (int i = number, j = letter; i>=0, j<8; --i, ++j){
        if (addAndCheckStop(squares, i, j) == 1){break;}
    }

    // do SW
    for (int i = number, j = letter; i>=0, j>=0; --i, --j){
        if (addAndCheckStop(squares, i, j) == 1){break;}
    }

    // do NW
    for (int i = number, j = letter; i<8, j>=0; ++i, --j){
        if (addAndCheckStop(squares, i, j) == 1){break;}
    }

    return squares;
}

set<Square> Piece::_getRows()
{
    set<Square> squares = set<Square>();

    // do N
    for (int i = number, j = letter; i<8; ++i){
        if (addAndCheckStop(squares, i, j) == 1){break;}
    }

    // do S
    for (int i = number, j = letter; i>=0; --i){
        if (addAndCheckStop(squares, i, j) == 1){break;}
    }

    // do E
    for (int i = number, j = letter; j<8; ++j){
        if (addAndCheckStop(squares, i, j) == 1){break;}
    }

    // do W
    for (int i = number, j = letter; j>=0; --j){
        if (addAndCheckStop(squares, i, j) == 1){break;}
    }

    return squares;
}

set<Square> Piece::_getPawns()
{
    set<Square> squares = set<Square>();
    int i = number, j=letter;

    // if there is a row in front of pawn
    if(i<7){

        //add space if empty
        if (board.squares[i+1][j].isEmpty()){
            squares.insert(board.squares[i][j]);
        }

        // if NE diagonal exists and is occupied by enemy, add it
        if(j<7){
            if(!board.squares[i+1][j+1].isEmpty()){
                if(!board.squares[i+1][j+1].getPiece()->color != color){
                    squares.insert(board.squares[i+1][j+1]);
                }

            }

        }

        // if NW diagonal exists and is occupied by enemy, add it
        if(j>0){
            if(!board.squares[i+1][j-1].isEmpty()){
                if(!board.squares[i+1][j-1].getPiece()->color != color){
                    squares.insert(board.squares[i+1][j-1]);
                }

            }

        }
    }

    return squares;
}

set<Square> Piece::_getKnights(Board board)
{
    set<Square> squares = set<Square>();

    // i change 2, j change 1
    for (int i = -2; i <=2 ; i+=4)
    {
        for (int j = -1; j <=1 ; j+=2)
        {
            checkAndAddIj(squares, number+i, letter+j);
        }
    }
    // i change 1, j change 2
    for (int i = -1; i <=1 ; i+=2)
    {
        for (int j = -2; j <=2 ; j+=4)
        {
            checkAndAddIj(squares, number+i, letter+j);
        }
    }

    return squares;
}

set<Square> Piece::_getKing(Board board)
{
    set<Square> squares = set<Square>();
    for (int i = -1; i <=1 ; ++i)
    {
        for (int j = -1; j <=1 ; ++j)
        {
            if(!(i==0 && j==0))
            checkAndAddIj(squares, number+i, letter+j);
        }
    }
    return squares;

}

set<Square> Piece::_getQueen(Board board)
{
    set<Square> squares = set<Square>();
    set<Square> rowPlaces = _getRows();
    set<Square> diagPlaces = _getDiag();
    set_union(rowPlaces.begin(),rowPlaces.end(),diagPlaces.begin(),
              diagPlaces.end(), squares.end());

    return squares;
}

int  Piece::addAndCheckStop(set<Square> &squares, int i, int j){
    if (board.squares[i][j].isEmpty()){
        squares.insert(board.squares[i][j]);
        return 0;
    }
    else if (board.squares[i][j].getPiece()->color != color ){
        squares.insert(board.squares[i][j]);
        return 1;
    }
    else // this is a friendly piece
    {
        return 1;
    }
}

void  Piece::checkAndAddIj(set<Square> &squares, int i, int j){
    if (i>=0 && i<8 && j>=0 && j<8)
    {
        if (board.squares[i][j].isEmpty()){
            squares.insert(board.squares[i][j]);
        }
        else if (board.squares[i][j].getPiece()->color != color)
        {
            squares.insert(board.squares[i][j]);
        }
    }
}
