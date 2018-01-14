//
// Created by jherskow on 1/8/18.
//

#ifndef CPP_PIECE_H
#define CPP_PIECE_H

#include <map>
#include <set>
#include "Square.h"
#include "Board.h"
#define QUEEN "\u265B"
#define KING "\u265A"
#define BISHOP "\u265D"
#define KNIGHT "\u265E"
#define ROOK "\u265C"
#define PAWN "\u265F"

using namespace std;


enum piece_type
{
    queen, king, bishop, knight, rook, pawn
};

enum piece_color
{
    black, white
};


class Piece
{


private:
	piece_type type;
	piece_color color;
	Square* square;
	Board* board;
	bool hasMoved;
//    int letter, number;  // board locations of piece be filed with the original spot

	/**
  * @brief returns the squares on diagonals from piece.
  *        stops at board edge, or at friendly piece (not incl.) or enemy piece (incl.)
  */
	unordered_set<SQUARE_SET> _getBishop(){}

	/**
	 * @brief returns the squares on Rows from piece.
	 *        stops at board edge, or at friendly piece (not incl.) or enemy piece (incl.)
	 */
	unordered_set<SQUARE_SET> _getRook();

	/**
	 * @brief returns the squares available to pawns.
	 */
	unordered_set<SQUARE_SET> _getPawns();

	/**
	 * @brief returns the squares available to Knights.
	 */
	unordered_set<SQUARE_SET> _getKnights();

	/**
	 * @brief returns the squares available to King.
	 */
	unordered_set<SQUARE_SET> _getKing();

	/**
	 * @brief returns the squares available to Queen.
	 */
	unordered_set<SQUARE_SET> _getQueen();

	int addAndCheckStop(unordered_set<SQUARE_SET> &squares, int i, int j);

	void checkAndAddIj(unordered_set<SQUARE_SET> &squares, int i, int j);


public:

    /**
    * @brief Contructor.
    */
    Piece(Board* board, Square* square,piece_type type, piece_color color);

	/**
	 * getters
	 * @return
	 */
	piece_type getType() const;

	piece_color getColor() const;

	Square* getSquare() const;

	Board* getBoard() const;

	/**
	 *
	 * @return true if the move has not been moved at all
	 */
	bool isHasMoved() const;

	/**
	 * setteres
	 */
	void setType(piece_type type);

	void setColor(piece_color color);

	void setSquare(Square *square);

	void setBoard(Board *board);

	/**
	 * if the piece moved and hasmoved was false make it true
	 * @param hasMoved
	 */
	void setHasMoved(bool hasMoved);

	/**
	 *
	 * @return the string with  breakin the beging for each piece it returnes the number that would print the picture of that piece
	 */
	string pieceCode();

	/**
	 *
	 * @return a set of squares that a specific piece can move too
	 */
	unordered_set<SQUARE_SET> getSquaresCouldMove();

};


#endif //CPP_PIECE_H
