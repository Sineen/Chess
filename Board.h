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
    void Move (Square srcSquare, Square dstSquare);

    /**
    * @brief Try to perform a move
    * @return 0 if move successful, 1 if illegal
    */
    void UnMove ();

    /**
     * print the board
     */
    void printBoard();

    /**
    * @brief Returns the square corresponding to the letter code
    */
    Square& stringToSquare(std::string squareName);

    /**
    * @brief Return true if player (PlayerToCheck) is in check after move
    *       Should be called only if a move is otherwise legal
    */
    bool isCheck (Square srcSquare, Square dstSquare, piece_color PlayerToCheck);

    /**
    * @brief Return true if player (PlayerToCheck) is in check after move
    *       Should be called only if a move is otherwise legal
    */
    bool isCheck(piece_color PlayerToCheck);


    /**
    * @brief Gives a set of all of a player's pieces
    */
    unordered_set<Piece> returnPlayerPices(piece_color playerColor);

    /**
* @brief Return true if player (PlayerToCheck) can perform a small castle
*/
    bool CanSmallCastle (piece_color PlayerToCheck);

    /**
    * @brief Return true if player (PlayerToCheck) can perform a large castle
    */
    bool CanLargeCastle (piece_color PlayerToCheck);
    // getters
    const Square &getLastSource() const;

    const Square &getLastDistination() const;

    ///setters
    void setLastSource(const Square &lastSource);

    void setLastDistination(const Square &lastDistination);

private:

    Square lastSource;
    Square lastDistination;
    bool undidMove = false;

    string pieceColorCode(piece_color color);

    /**
    * @brief Gives a set of all of a player's legal Dest
     *      ( used to check if enemy can kill my king)
    */
    unordered_set<Square> returnPlayerLegalMoves(piece_color playerColor);


	/**
	 *
	 * @param srcSquare the source square
	 * @param dstSquare  teh distenation square
	 * @param playerToCheck  the player making the move  which color
	 * @return  true if he had a peice in his suc square and the dst square was a legal move to it
	 */
	bool isLegal(Square srcSquare, Square dstSquare, piece_color playerToCheck);
};


#endif //CPP_BOARD_H
