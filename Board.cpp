//
// Created by jherskow on 1/8/18.
//

#include <list>
#include <iostream>
#include <algorithm>
#include "Board.h"

#define FIRST_LINE "\33[0;0m  ABCDEFGH  \33[0m"


/**
* @brief Contructor. - sets the board with pieces
*/
Board::Board()
{

    for (int i = 0; i < 8 ; ++i)
    {
        for (int j = 0; j < 8 ; ++j)
        {
            squares[i][j] = Square(i,j);
        }
    }

    for (int j = 0; j < 8; ++j)
    {
        squares[1][j].setPiece(new Piece(this, &squares[2][j],pawn,white));
    }

    for (int j = 0; j < 8; ++j)
    {
        squares[6][j].setPiece(new Piece(this, &squares[7][j], pawn,black));
    }

    piece_type settingList[8] = {rook,knight,bishop,queen,king,bishop,knight,rook};

    piece_color cur = white;
    int i = 0;
    for (int j = 0; j < 8 ; ++j)
    {
        squares[i][j].setPiece(new Piece(this, &squares[i][j], settingList[j],cur));
    }

    cur = black;
    i = 7;
    for (int j = 0; j < 8; ++j)
    {
        squares[i][j].setPiece(new Piece(this, &squares[i][j], settingList[j],cur));
    }


}


/**
* @brief Try to perform a move
* @return 0 if move successful, 1 if illegal
*/
int Board::Move (Square srcSquare, Square dstSquare, piece_color color)
{

}

//    /**
//    * @brief Gives a map of legal destinations for a specific piece.
//    */
//    map ReturnPieceLegalMoves(Square srcSquare, piece_color color);

/**
* @brief Gives a map of legal destinations for a specific piece.
*/
Square& Board::strToSquare(string letterPair)
{

}

/**
 * print the board
 */
void Board::printBoard()
{
    cout << FIRST_LINE << endl;
    string backGround = BLUE_BACKGROUND;
    string pieceColor = ZERO_TEXT;
	string pieceCodes = " ";
    for (int i = 8; i > 0 ; --i) // becasue we print from top to bottom so we need the last  line in the array
		// todo ask josh how he filled it in
    {
		// prints thenumber in the beging of the line
        cout << "\33[0;0m" << i <<" \33[0m" ;
        for (int j = 0; j < 8 ; ++j)
        {
            if (squares[i][j].isEmpty())
            {
                pieceColor = ZERO_TEXT;
				pieceCodes = " ";
            }
            else
            {
                pieceColor = Board::pieceColorCode(squares[i][j].getPiece()->getColor()); // get the color of teh piece in teh square
				pieceCodes = squares[i][j].getPiece()->pieceCode();
            }
			//print the square
            cout << "\33[" << pieceColor << ";" << backGround << "m" << pieceCodes << " \33[0m";
			 // switching the back ground color to make teh chekboard pattern
            if ( backGround == BLUE_BACKGROUND)
            {
                backGround == GREEN_BACKGROUND;
            }
            else if ( backGround == GREEN_BACKGROUND)
            {
                backGround == BLUE_BACKGROUND;
            }
        }
		// print the number of the check in the last on the line  and goes to a new line
        cout << "\33[0;0m " << i <<"\33[0m" << endl;
    }
}

string pieceColorCode(piece_color color)
{
    if ( color == white)
    {
       return WHITE_TEXT;
    }
    else if ( color == black )
    {
        return BLACK_TEXT;
    }
    else
    {
        return  ZERO_TEXT;
    }
}

/**
* @brief Gives a set of all of a sqaures that contains the  player's pieces
*/
set<Square> Board::returnPlayerPices(piece_color playerColor)
{
	set piecesOnBoard;
	for (auto &square : squares)
	{
		if(square->getPiece()->getColor() == playerColor)
		{
			piecesOnBoard.insert(square);
		}
	}
	return piecesOnBoard;
}

/**
* @brief Gives a set of all of a player's legal Dest
 *      ( used to check if enemy can kill my king)
*/
set<Square> Board::returnPlayerLegalMoves(piece_color playerColor)
{
	set<Square> squaresCanBeLandedOn;
	set<Square> piecesPlayedHas = Board::returnPlayerPices(playerColor);
	set<Square> temp;
	for(auto square : piecesPlayedHas)
	{
		Piece* piece = square.getPiece();
		temp = piece->getSquaresCouldMove();
		squaresCanBeLandedOn.insert(temp.begin(), temp.end());
	}
}

/**
* @brief Return true if player (PlayerToCheck) is in check after move
 *       Should be called only if a move is otherwise legal
*/
bool Board::isCheck (Square srcSquare, Square dstSquare, piece_color playerToCheck)
{
	piece_color  playerInTurn;
	if (playerToCheck == white)
	{
		playerInTurn = black;
	}
	else
	{
		playerInTurn = white;
	}
	set<Square> legalmoves = returnPlayerLegalMoves(playerInTurn);


}

bool Board::isLegal(Square srcSquare, Square dstSquare, piece_color playerToCheck)
{
	bool returnVal1 = false;
	bool returnVal2 = false;
	set<Square> peiecesLocation = returnPlayerPices(playerToCheck);
	//check if soruce actually has its own piece
	for(auto &square : peiecesLocation)
	{
		if (srcSquare.compareSquareTo(square) && srcSquare.getPiece()->getColor() == playerToCheck)
		{
			returnVal1 = true;
			break;
		}
	}
	// no need to continue to check if it was aleady false
	if (returnVal1)
	{
		// src had a peice of the player and was fone
		set<Square> legalmoves = srcSquare.getPiece()->getSquaresCouldMove(); // all places this piece can move too

		// check if dst it a legal move to that piece
		for(auto &squareMove : legalmoves)
		{
			if (dstSquare.compareSquareTo(squareMove))
			{
				returnVal2 = true;
				break;
			}
		}
	}
	return (returnVal1 && returnVal2);
}

/**
* @brief Return true if player (PlayerToCheck) can perform a small castle
*/
bool Board::CanSmallCastle (piece_color PlayerToCheck)
{

}

/**
* @brief Return true if player (PlayerToCheck) can perform a large castle
*/
bool Board::CanLargeCastle (piece_color PlayerToCheck)
{

}

/**
* @brief Returns the square corresponding to the letter code
*/
Square& Board::square(string squareName)
{
    int i =  squareName[0] - 'A';
    int j =  squareName[1] - '0';
    return squares[i][j];
}

