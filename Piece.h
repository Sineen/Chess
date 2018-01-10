//
// Created by jherskow on 1/8/18.
//

#ifndef CPP_PIECE_H
#define CPP_PIECE_H

#include <map>
#include <set>
#include "Square.h"
#include "Board.h"

using namespace std;

enum piece_type{
    queen, king, bishop, knight, rook, pawn
};

enum piece_color{
    black, white
};


class Piece
{

public:

    piece_type type;
    piece_color color;
    piece_color enemyColor;
    Square& square;
    Board& board;
    bool hasMoved;
    int letter, number;  // board locations of piece be filed with the original spot


    /**
     * just an empty constuctor;
     */
    Piece();
    /**
    * @brief Contructor.
    */
    Piece(piece_type type, piece_color color, Square square);

    /**
    * @brief changes the pieces' current square.
    */
    void setSquare(Square square);

    /**
    * @brief Gives a map of places piece can move to.
    */
    set<Square> ReturnSquaresInRange();



private:

    /**
     * @brief returns the squares on diagonals from piece.
     *        stops at board edge, or at friendly piece (not incl.) or enemy piece (incl.)
     */
    set<Square> _getDiag(){}

    /**
     * @brief returns the squares on Rows from piece.
     *        stops at board edge, or at friendly piece (not incl.) or enemy piece (incl.)
     */
    set<Square> _getRows();

    /**
 * @brief returns the squares on Col from piece.
 *        stops at board edge, or at friendly piece
 */
    set<Square> _getColumes(Board board);

    /**
     * @brief returns the squares available to pawns.
     */
    set<Square> _getPawns(Board board);

    /**
     * @brief returns the squares available to Knights.
     */
    set<Square> _getKnights(Board board);

    /**
     * @brief returns the squares available to King.
     */
    set<Square> _getKing(Board board);

    /**
     * @brief returns the squares available to Queen.
     */
    set<Square> _getQueen(Board board);


    int addAndCheckStop(set<Square> &squares, int i, int j);
};


#endif //CPP_PIECE_H
