//
// Created by jherskow on 1/8/18.
//

#ifndef CPP_BOARD_H
#define CPP_BOARD_H

#include <map>
#include "Square.h"
#include "Piece.h"

using namespace std;

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
    Square strToSquare(string letterPair);

    /**
     * print the board
     */
    void printBoard();

private:


    /**
    * @brief Gives a map of all of a player's pieces
    */
    set<Piece> ReturnPlayerPices(piece_color playerColor);

    /**
    * @brief Gives a set of all of a player's legal Dest
     *      ( used to check if enemy can kill my king)
    */
    set<Square> ReturnPlayerLegalMoves(piece_color playerColor);

    /**
    * @brief Return true if player (PlayerToCheck) is in check after move
     *       Should be called only if a move is otherwise legal
    */
    bool isCheck (Square srcSquare, Square dstSquare, piece_color PlayerToCheck);

    /**
    * @brief Return true if player (PlayerToCheck) can perform a small castle
    */
    bool CanSmallCastle (piece_color PlayerToCheck);

    /**
    * @brief Return true if player (PlayerToCheck) can perform a large castle
    */
    bool CanLargeCastle (piece_color PlayerToCheck);

    /**
    * @brief Returns the square corresponding to the letter code
    */
    Square& square(string squareName);


};


#endif //CPP_BOARD_H