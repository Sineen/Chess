
#include <algorithm>
#include <unordered_set>
#include "Piece.h"
using namespace std;


Piece::Piece(Board *board, Square *square, piece_type type, piece_color color)
{

	Piece::setBoard(board);
    Piece::setSquare(square);
	Piece::setType(type);
	Piece::setColor(color);
}


unordered_set<Square , squareHasher , squareComparator> Piece::_getBishop()
{
	unordered_set<Square , squareHasher , squareComparator> squares;

    // do NE
    for (int i = square->getNumber(), j = square->getLetter(); i < 8, j < 8; ++i, ++j){
        if (addAndCheckStop(squares, i, j) == 1){break;}
    }

    // do SE
    for (int i = square->getNumber(), j = square->getLetter(); i >= 0, j < 8; --i, ++j){
        if (addAndCheckStop(squares, i, j) == 1){break;}
    }

    // do SW
    for (int i = square->getNumber(), j = square->getLetter(); i >= 0, j >= 0; --i, --j){
        if (addAndCheckStop(squares, i, j) == 1){break;}
    }

    // do NW
    for (int i = square->getNumber(), j = square->getLetter(); i < 8, j >= 0; ++i, --j){
        if (addAndCheckStop(squares, i, j) == 1){break;}
    }

	//todo add if it hasn ot moved yet it can be switched between it and the king caselling
    return squares;
}

unordered_set<Square , squareHasher , squareComparator> Piece::_getRook()
{
    unordered_set<Square , squareHasher , squareComparator> squares;

    // do N
    for (int i = square->getNumber(), j = square->getLetter(); i < 8; ++i){
        if (addAndCheckStop(squares, i, j) == 1){break;}
    }

    // do S
    for (int i = square->getNumber(), j = square->getLetter(); i >= 0; --i){
        if (addAndCheckStop(squares, i, j) == 1){break;}
    }

    // do E
    for (int i = square->getNumber(), j = square->getLetter(); j < 8; ++j){
        if (addAndCheckStop(squares, i, j) == 1){break;}
    }

    // do W
    for (int i = square->getNumber(), j = square->getLetter(); j >= 0; --j){
        if (addAndCheckStop(squares, i, j) == 1){break;}
    }

    return squares;
}

unordered_set<Square , squareHasher , squareComparator> Piece::_getPawns()
{
	//todo fix direction and add if it has not moved ( first move it can go two steps to the front
	unordered_set<Square , squareHasher , squareComparator> squares;
    int i = square->getNumber(), j = square->getLetter();

    // if there is a row in front of pawn
    if(i<7){

        //add space if empty
        if (board->squares[i+1][j].isEmpty()){
            squares.insert(board->squares[i][j]);
        }

        // if NE diagonal exists and is occupied by enemy, add it
        if(j<7){
            if(!board->squares[i+1][j+1].isEmpty()){
                if(!board->squares[i+1][j+1].getPiece()->color != color){
                    squares.insert(board->squares[i+1][j+1]);
                }

            }

        }

        // if NW diagonal exists and is occupied by enemy, add it
        if(j>0){
            if(!board->squares[i+1][j-1].isEmpty()){
                if(!board->squares[i+1][j-1].getPiece()->color != color){
                    squares.insert(board->squares[i+1][j-1]);
                }
            }
        }
    }

    return squares;
}

unordered_set<Square , squareHasher , squareComparator> Piece::_getKnights()
{
    unordered_set<Square , squareHasher , squareComparator> squares;

    // i change 2, j change 1
    for (int i = -2; i <= 2 ; i += 4)
    {
        for (int j = -1; j <= 1 ; j += 2)
        {
            checkAndAddIj(squares, square->getNumber() + i, square->getLetter() + j);
        }
    }
    // i change 1, j change 2
    for (int i = -1; i <= 1 ; i += 2)
    {
        for (int j = -2; j <= 2 ; j += 4)
        {
            checkAndAddIj(squares, square->getNumber() + i, square->getLetter() + j);
        }
    }

    return squares;
}

unordered_set<Square , squareHasher , squareComparator> Piece::_getKing()
{
    unordered_set<Square , squareHasher , squareComparator> squares;
    for (int i = -1; i <= 1 ; ++i)
    {
        for (int j = -1; j <= 1 ; ++j)
        {
            if(!(i == 0 && j == 0))
            checkAndAddIj(squares, square->getNumber() + i, square->getLetter() + j);
        }
    }
    return squares;

}

unordered_set<Square , squareHasher , squareComparator> Piece::_getQueen()
{
    unordered_set<Square , squareHasher , squareComparator> squares;
    unordered_set<Square , squareHasher , squareComparator> rowPlaces = _getRook();
    unordered_set<Square , squareHasher , squareComparator> diagPlaces = _getBishop();
    set_union(rowPlaces.begin(),rowPlaces.end(),diagPlaces.begin(),
              diagPlaces.end(), squares.end());

    return squares;
}

int  Piece::addAndCheckStop(unordered_set<Square , squareHasher , squareComparator> &squares, int i, int j){
    if (board->squares[i][j].isEmpty()){
        squares.insert(board->squares[i][j]);
        return 0;
    }
    else if (board->squares[i][j].getPiece()->color != color ){
        squares.insert(board->squares[i][j]);
        return 1;
    }
    else // this is a friendly piece
    {
        return 1;
    }
}

void  Piece::checkAndAddIj(unordered_set<Square , squareHasher , squareComparator> &squares, int i, int j){
    if (i >= 0 && i < 8 && j >= 0 && j <8 )
    {
        if (board->squares[i][j].isEmpty()){
            squares.insert(board->squares[i][j]);
        }
        else if (board->squares[i][j].getPiece()->color != color)
        {
            squares.insert(board->squares[i][j]);
        }
    }
}

piece_type Piece::getType() const
{
    return type;
}

piece_color Piece::getColor() const
{
    return color;
}

Square* Piece::getSquare() const
{
    return square;
}

Board* Piece::getBoard() const
{
    return board;
}

bool Piece::isHasMoved() const
{
    return hasMoved;
}


void Piece::setType(piece_type type)
{
    Piece::type = type;
}

void Piece::setColor(piece_color color)
{
    Piece::color = color;
}

void Piece::setSquare(Square *square)
{
    Piece::square = square;
}

void Piece::setBoard(Board *board)
{
    Piece::board = board;
}

void Piece::setHasMoved(bool hasMoved)
{
    Piece::hasMoved = hasMoved;
}


string Piece::pieceCode()
{
	switch (getType())
	{
		//    queen, king, bishop, knight, rook, pawn

		case queen:
			return QUEEN;
		case king:
			return KING;
		case bishop:
			return BISHOP;
		case knight:
			return KNIGHT;
		case rook:
			return ROOK;
		case pawn:
			return PAWN;
		default:
			return nullptr;
	}
}

unordered_set<Square , squareHasher , squareComparator> Piece::getSquaresCouldMove()
{
	unordered_set<Square , squareHasher , squareComparator> squareCouldMoveTo;
	switch (getType())
	{
		case queen:
			squareCouldMoveTo = _getQueen();
			break;
		case king:
			squareCouldMoveTo = _getKing();
			break;
		case rook:
			squareCouldMoveTo = _getRook();
			break;
		case bishop:
			squareCouldMoveTo = _getBishop();
			break;
		case knight:
			squareCouldMoveTo = _getKnights();
			break;
		case pawn:
			squareCouldMoveTo = _getPawns();
			break;
	}

	return squareCouldMoveTo;
}
