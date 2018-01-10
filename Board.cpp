//
// Created by jherskow on 1/8/18.
//

#include <list>
#include "Board.h"

/**
* @brief Contructor. - sets the board with pieces
*/
Board::Board(){

    for (int i = 0; i <8 ; ++i)
    {
        for (int j = 0; j <8 ; ++j)
        {
            squares[i][j] = Square(i,j);
        }
    }

    for (int j = 0; j < 8; ++j)
    {
        squares[1][j].setPiece(Piece(pawn,white,squares[2][j]));
    }

    for (int j = 0; j < 8; ++j)
    {
        squares[6][j].setPiece(Piece(pawn,black,squares[7][j]));
    }

    piece_type settingList[8] = {rook,knight,bishop,queen,king,bishop,knight,rook};

    piece_color cur = white;
    int i = 0;
    for (int j = 0; j <8 ; ++j)
    {
        squares[i][j].setPiece(Piece(settingList[j],cur,squares[i][j]));
    }

    cur = black;
    i = 7;
    for (int j = 0; j < 8; ++j)
    {
        squares[i][j].setPiece(Piece(settingList[j],cur,squares[i][j]));
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
Square Board::strToSquare(string letterPair);

/**
 * print the board
 */
void Board::printBoard();


/**
* @brief Gives a map of all of a player's pieces
*/
set<Piece> Board::ReturnPlayerPices(piece_color playerColor);

/**
* @brief Gives a set of all of a player's legal Dest
 *      ( used to check if enemy can kill my king)
*/
set<Square> Board::ReturnPlayerLegalMoves(piece_color playerColor);

/**
* @brief Return true if player (PlayerToCheck) is in check after move
 *       Should be called only if a move is otherwise legal
*/
bool Board::isCheck (Square srcSquare, Square dstSquare, piece_color PlayerToCheck);

/**
* @brief Return true if player (PlayerToCheck) can perform a small castle
*/
bool Board::CanSmallCastle (piece_color PlayerToCheck);

/**
* @brief Return true if player (PlayerToCheck) can perform a large castle
*/
bool Board::CanLargeCastle (piece_color PlayerToCheck);

/**
* @brief Returns the square corresponding to the letter code
*/
Square& Board::square(string squareName)
{
    int i =  squareName[0] - 'A';
    int j =  squareName[1] - '0';
    return squares[i][j];
}

