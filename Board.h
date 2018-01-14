//
// Created by jherskow on 1/8/18.
//

#ifndef CPP_BOARD_H
#define CPP_BOARD_H

#include <map>
#include "Square.h"
#include "Piece.h"
//maybe add 'm' after all background colors and add ';' after all text
#define ZERO_TEXT "0"
#define WHITE_TEXT "37"
#define BLACK_TEXT "30"
#define GREEN_BACKGROUND "42"
#define BLUE_BACKGROUND "46"
#define RED_BACKGROUND "41"
#define FIRST_LINE "  ABCDEFGH  "
#define BEGIN_LINE "\33["
#define END_LINE "\33[0m"


class Board
{
private:

    Square* lastSource;
    Square* lastDistination;
    bool undidMove = false;
    bool lastPieceMoved;

    string pieceColorCode(piece_color color);

    /**
    * @brief Gives a set of all of a player's legal Dest
     *      ( used to check if enemy can kill my king)
    */
    unordered_set<Square , squareHasher , squareComparator> returnPlayerLegalMoves(piece_color playerColor);

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
    void move(Square& srcSquare, Square& dstSquare);

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
    Square& stringToSquare(std::string& squareName);

    /**
    * @brief Return true if player (PlayerToCheck) is in check after move
    *       Should be called only if a move is otherwise legal
    */
    bool isCheck (Square& src, Square& dst, piece_color PlayerToCheck);

    /**
    * @brief Return true if player (PlayerToCheck) is in check after move
    *       Should be called only if a move is otherwise legal
    */
    bool isCheck(piece_color PlayerToCheck);


    /**
    * @brief Gives a set of all of a player's pieces
    */
    unordered_set<Square , squareHasher , squareComparator> returnPlayerPices(piece_color playerColor);

    /**
* @brief Return true if player (PlayerToCheck) can perform a small castle
*/
    bool smallCastle(piece_color PlayerToCheck);

    /**
    * @brief Return true if player (PlayerToCheck) can perform a large castle
    */
    bool largeCastle(piece_color PlayerToCheck);

    void setLastSource(Square *lastSource);

    void setLastDistination(Square *lastDistination);


    /**
     *
     * @param srcSquare the source square
     * @param dstSquare  teh distenation square
     * @param playerToCheck  the player making the move  which color
     * @return  true if he had a peice in his suc square and the dst square was a legal move to it
     */
    bool isLegal(Square& src, Square& dst, piece_color playerToCheck);


//    void printLine(string backgroundColor, string textColor, string text);  maybe do this

};


#endif //CPP_BOARD_H
