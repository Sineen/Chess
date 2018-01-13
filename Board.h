//
// Created by jherskow on 1/8/18.
//

#ifndef CPP_BOARD_H
#define CPP_BOARD_H

#include <map>
#include "Square.h"
#include "Piece.h"
#define ZERO_TEXT "0"
#define WHITE_TEXT "37"
#define BLACK_TEXT "30"
#define GREEN_BACKGROUND "42"
#define BLUE_BACKGROUND "46"
#define RED_BACKGROUND "41"


class Board
{
public:

    Square squares[8][8];

    /**
    * @brief Contructor. - sets the board with pieces
    */
    Board();


    /**
    * @brief Try to perform a move
    * @return 0 if move successful, 1 if illegal
    */
    int Move (Square srcSquare, Square dstSquare, piece_color color);

//    /**
//    * @brief Gives a map of legal destinations for a specific piece.
//    */
//    map ReturnPieceLegalMoves(Square srcSquare, piece_color color);

    /**
    * @brief Gives a map of legal destinations for a specific piece.
    */
    Square& strToSquare(string letterPair);

    /**
     * print the board
     */
    void printBoard();

    string pieceColorCode(piece_color color);

    /**
* @brief Return true if player (PlayerToCheck) can perform a small castle
*/
    bool CanSmallCastle (piece_color PlayerToCheck);

    /**
    * @brief Return true if player (PlayerToCheck) can perform a large castle
    */
    bool CanLargeCastle (piece_color PlayerToCheck);
private:


    /**
    * @brief Gives a set of all of a player's pieces
    */
	unordered_set<Square> returnPlayerPices(piece_color playerColor);

    /**
    * @brief Gives a set of all of a player's legal Dest
     *      ( used to check if enemy can kill my king)
    */
    unordered_set<Square> returnPlayerLegalMoves(piece_color playerColor);

    /**
    * @brief Return true if player (PlayerToCheck) is in check after move
     *       Should be called only if a move is otherwise legal
    */
    bool isCheck (Square srcSquare, Square dstSquare, piece_color PlayerToCheck);



    /**
    * @brief Returns the square corresponding to the letter code
    */
    Square& square(std::string squareName);

	bool isLegal(Square srcSquare, Square dstSquare, piece_color playerToCheck);
};


#endif //CPP_BOARD_H
