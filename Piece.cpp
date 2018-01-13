
#include <algorithm>
#include "Piece.h"
using namespace std;


Piece::Piece(piece_type type, piece_color color, Square& square)
{
    board = Board();
    Piece::setSquare(square);
	Piece::setType(type);
	Piece::setColor(color);
	Piece::setLetter(letter);
    Piece::setNumber(number);
}


set<Square> Piece::ReturnSquaresInRange()
{
    return set<Square>();
}

set<Square> Piece::_getBishop()
{
    set<Square> squares = set<Square>();

    // do NE
    for (int i = number, j = letter; i < 8, j < 8; ++i, ++j){
        if (addAndCheckStop(squares, i, j) == 1){break;}
    }

    // do SE
    for (int i = number, j = letter; i >= 0, j < 8; --i, ++j){
        if (addAndCheckStop(squares, i, j) == 1){break;}
    }

    // do SW
    for (int i = number, j = letter; i >= 0, j >= 0; --i, --j){
        if (addAndCheckStop(squares, i, j) == 1){break;}
    }

    // do NW
    for (int i = number, j = letter; i < 8, j > =0; ++i, --j){
        if (addAndCheckStop(squares, i, j) == 1){break;}
    }

	//todo add if it hasn ot moved yet it can be switched between it and the king caselling
    return squares;
}

set<Square> Piece::_getRook()
{
    set<Square> squares = set<Square>();

    // do N
    for (int i = number, j = letter; i < 8; ++i){
        if (addAndCheckStop(squares, i, j) == 1){break;}
    }

    // do S
    for (int i = number, j = letter; i >= 0; --i){
        if (addAndCheckStop(squares, i, j) == 1){break;}
    }

    // do E
    for (int i = number, j = letter; j < 8; ++j){
        if (addAndCheckStop(squares, i, j) == 1){break;}
    }

    // do W
    for (int i = number, j = letter; j >= 0; --j){
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

set<Square> Piece::_getKnights()
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

set<Square> Piece::_getKing()
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

set<Square> Piece::_getQueen()
{
    set<Square> squares = set<Square>();
    set<Square> rowPlaces = _getRook();
    set<Square> diagPlaces = _getBishop();
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

piece_type Piece::getType() const
{
    return type;
}

piece_color Piece::getColor() const
{
    return color;
}

Square &Piece::getSquare() const
{
    return square;
}

Board &Piece::getBoard() const
{
    return board;
}

bool Piece::isHasMoved() const
{
    return hasMoved;
}

int Piece::getLetter() const
{
    return letter;
}

int Piece::getNumber() const
{
    return number;
}

void Piece::setType(piece_type type)
{
    Piece::type = type;
}

void Piece::setColor(piece_color color)
{
    Piece::color = color;
}

void Piece::setSquare(Square &square)
{
    Piece::square = square;
}

void Piece::setBoard(Board &board)
{
    Piece::board = board;
}

void Piece::setHasMoved(bool hasMoved)
{
    Piece::hasMoved = hasMoved;
}

void Piece::setLetter(int letter)
{
    Piece::letter = letter;
}

void Piece::setNumber(int number)
{
    Piece::number = number;
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

set<Square> Piece::getSquaresCouldMove()
{
	set<Square> squareCouldMoveTo;
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

	return set<Square>();
}
