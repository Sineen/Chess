//
// Created by jherskow on 1/8/18.
//

#include <list>
#include <iostream>
#include <algorithm>
#include <unordered_set>
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
 * print the board
 */
void Board::printBoard()
{
    cout << FIRST_LINE << endl;
    string backGround;
    string pieceColor = ZERO_TEXT;
	string pieceCodes = " ";
    for (int i = 8; i > 0 ; --i) // becasue we print from top to bottom so we need the last  line in the array
		// todo ask josh how he filled it in
    {
		// prints thenumber in the beging of the line
        cout << "\33[0;0m" << i <<" \33[0m" ;
        for (int j = 0; j < 8 ; ++j)
        {
            backGround = squares[i][j].getColor() == black ? GREEN_BACKGROUND : BLUE_BACKGROUND;
            if (squares[i][j].isEmpty())
            {
                pieceColor = ZERO_TEXT;
				pieceCodes = " ";
            }
            else
            {
                pieceColor = pieceColorCode(squares[i][j].getPiece()->getColor()); // get the color of teh piece in teh stringToSquare
				pieceCodes = squares[i][j].getPiece()->pieceCode();
            }
			//print the stringToSquare
            cout << "\33[" << pieceColor << ";" << backGround << "m" << pieceCodes << " \33[0m";
        }
		// print the number of the check in the last on the line  and goes to a new line
        cout << "\33[0;0m " << i <<"\33[0m" << endl;
    }
}

string Board::pieceColorCode(piece_color color)
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
unordered_set<Piece> Board::returnPlayerPices(piece_color playerColor)
{
	unordered_set<Piece> piecesOnBoard = unordered_set<Piece>();
	for (auto &square : squares)
	{
		if(square->getPiece()->getColor() == playerColor)
		{
			piecesOnBoard.insert(*(square->getPiece()));
		}
	}
	return piecesOnBoard;
}

/**
* @brief Gives a set of all of a player's legal Dest
 *      ( used to check if enemy can kill my king)
*/
unordered_set<Square> Board::returnPlayerLegalMoves(piece_color playerColor)
{
	unordered_set<Square> squaresCanBeLandedOn = unordered_set<Square>();
	unordered_set<Piece> piecesPlayedHas = Board::returnPlayerPices(playerColor);
	unordered_set<Square> temp = unordered_set<Square>();
	for(Piece piece : piecesPlayedHas)
	{
		temp = piece.getSquaresCouldMove();
		squaresCanBeLandedOn.insert(temp.begin(), temp.end());
	}
}





/**
* @brief Return true if player (PlayerToCheck) can perform a small castle
*/
bool Board::CanSmallCastle (piece_color PlayerToCheck)
{
    int row = (PlayerToCheck == white)? 0: 7;
    int kAndR[2] = {4,7};
    int spaces[5] = {4,5,6,7};
    piece_color enemyColor = (PlayerToCheck==white) ? black : white;

    for(int col: kAndR){
        // make sure king and rook are there and unmoved
        if (squares[row][col].isEmpty()) return false;
        if (squares[row][col].getPiece()->getType() != king) return false;
        if (squares[row][col].getPiece()->isHasMoved()) return false;
    }

    //make sure all pices and spaces are not threaened
    unordered_set<Square> threatened = returnPlayerLegalMoves(enemyColor);
    for(int col: spaces){
        if ( !(threatened.find(squares[row][col]) == threatened.end()) ){ return false;}
    }

    return true;
}

/**
* @brief Return true if player (PlayerToCheck) can perform a large castle
*/
bool Board::CanLargeCastle (piece_color PlayerToCheck)
{
    int row = (PlayerToCheck == white)? 0: 7;
    int kAndR[2] = {4,0};
    int spaces[5] = {4,3,2,1,0};

    piece_color enemyColor = (PlayerToCheck==white) ? black : white;

    for(int col: kAndR){
        // make sure king and rook are there and unmoved
        if (squares[row][col].isEmpty()) return false;
        if (squares[row][col].getPiece()->getType() != king) return false;
        if (squares[row][col].getPiece()->isHasMoved()) return false;
    }

    //make sure all pices and spaces are not threaened
    unordered_set<Square> threatened = returnPlayerLegalMoves(enemyColor);
    for(int col: spaces){
        if ( !(threatened.find(squares[row][col]) == threatened.end()) ){ return false;}
    }

    return true;
}

/**
* @brief Returns the square corresponding to the letter code
*/
Square& Board::stringToSquare(string squareName)
{
    int i =  squareName[0] - 'A';
    int j =  squareName[1] - '0';
    return squares[i][j];
}


// todo CONSRUCION ZONE ===================================================================



bool Board::isLegal(Square srcSquare, Square dstSquare, piece_color playerToCheck)
{
    if (srcSquare.isEmpty())
    {
        return false;
    }
    bool returnVal1 = false;
    bool returnVal2 = false;
    unordered_set<Piece> pieces = returnPlayerPices(playerToCheck);
    //check if soruce actually has its own piece
    for(auto &piece : pieces)
    {
        if (srcSquare.compareSquareTo(*(piece.getSquare())) && srcSquare.getPiece()->getColor() ==
                                                               playerToCheck)
        {
            returnVal1 = true;
            break;
        }
    }
    // no need to continue to check if it was aleady false
    if (returnVal1)
    {
        // src had a peice of the player and was fone
        unordered_set<Square> legalmoves = srcSquare.getPiece()->getSquaresCouldMove(); // all places this piece can move too

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
* @brief Does a move, deleting pice if eaten
*/
void Board::Move (Square srcSquare, Square dstSquare, piece_color color)
{
    //todo do
}

/**
* @brief Un-Does a move, reviving piece using variaBle lastPiece if one was eaten
*/
void Board::UnMove (Square srcSquare, Square dstSquare, piece_color color)
{
    //todo do
}


bool Board::isCheck(piece_color PlayerToCheck){
    //todo make




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
    unordered_set<Square> legalMoves = returnPlayerLegalMoves(playerInTurn);

    // todo write

}