//
// Created by jherskow on 1/8/18.
//

#include <list>
#include <iostream>
#include <algorithm>
#include <unordered_set>
#include "Board.h"

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
    cout << BEGIN_LINE << ZERO_TEXT << ";"<< ZERO_TEXT << "m" << FIRST_LINE << END_LINE << endl; // print first line ABCDGH
    string backGround;
    string pieceColor = ZERO_TEXT;
	string pieceCodes = " ";
    for (int i = 8; i > 0 ; --i) // becasue we print from top to bottom so we need the last  line in the array
		// todo ask josh how he filled it in
    {
		// prints thenumber in the beging of the line
        cout << BEGIN_LINE << ZERO_TEXT << ";"<< ZERO_TEXT << "m" << i <<" "<< END_LINE ;
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
            cout << BEGIN_LINE << pieceColor << ";" << backGround << "m" << pieceCodes << " " << END_LINE;
        }
		// print the number of the check in the last on the line  and goes to a new line
        cout << BEGIN_LINE << ZERO_TEXT << ";"<< ZERO_TEXT << "m " << i <<" "<< END_LINE << endl;
    }
    cout << BEGIN_LINE << ZERO_TEXT << ";"<< ZERO_TEXT << "m" << FIRST_LINE << END_LINE << endl; // print last ABCDGH

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
bool Board::smallCastle(piece_color PlayerToCheck)
{
    int row = (PlayerToCheck == white)? 0: 7;
    int kAndR[2] = {4,7};
    int spaces[5] = {4,5,6,7};
    piece_color enemyColor = (PlayerToCheck==white) ? black : white;

    for(int col: kAndR){
        // make sure king and rook are there and unmoved
        if (squares[row][col].isEmpty()) return false;
        if (squares[row][col].getPiece()->isHasMoved()) return false;
    }

    //make sure all pices and spaces are not threaened
    unordered_set<Square> threatened = returnPlayerLegalMoves(enemyColor);
    for(int col: spaces){
        if ( !(threatened.find(squares[row][col]) == threatened.end()) ){ return false;}
    }

    // move rook to final
    move(squares[row][7], squares[row][5]);
    // move king to final
    move(squares[row][4], squares[row][6]);

    return true;
}

/**
* @brief Return true if player (PlayerToCheck) can perform a large castle
*/
bool Board::largeCastle(piece_color PlayerToCheck)
{
    int row = (PlayerToCheck == white)? 0: 7;
    int kAndR[2] = {4,0};
    int spaces[5] = {4,3,2,1,0};

    piece_color enemyColor = (PlayerToCheck==white) ? black : white;

    for(int col: kAndR){
        // make sure king and rook are there and unmoved
        if (squares[row][col].isEmpty()) return false;
        if (squares[row][col].getPiece()->isHasMoved()) return false;
    }

    //make sure all pices and spaces are not threaened
    unordered_set<Square> threatened = returnPlayerLegalMoves(enemyColor);
    for(int col: spaces){
        if ( !(threatened.find(squares[row][col]) == threatened.end()) ){ return false;}
    }

    // move rook to final
    move(squares[row][0], squares[row][3]);
    // move king to final
    move(squares[row][4], squares[row][2]);

    return true;
}

/**
* @brief Returns the square corresponding to the letter code
*/
Square& Board::stringToSquare(string squareName)
{
    int i =  squareName[0] - 'A';
    int j =  squareName[1] - '1';
    return squares[i][j];
}


// todo CONSRUCION ZONE ===================================================================


/**
 * @brief Checks if a move is legal PHYSICALLY (no connection to check)
 */
bool Board::isLegal(Square& src, Square& dst, piece_color playerToCheck)
{

    // make sure source is not-empty and player color
    if (src.isEmpty()) {return false;}
    Piece* playingPiece = src.getPiece();
    if (src.getPiece()->getColor() != playerToCheck) return false;

    //make a list of places
    unordered_set<Square> legalDestinations = playingPiece->getSquaresCouldMove();

    //if illegal
    return !(legalDestinations.find(dst) == legalDestinations.end());
}

/**
* @brief Does a move, deleting piece if eaten
*/
void Board::move(Square srcSquare, Square dstSquare)
{
    lastPieceMoved = srcSquare.getPiece()->isHasMoved();
    setLastDistination(&dstSquare);
    setLastSource(&srcSquare);
    if(!dstSquare.isEmpty())
    {
        dstSquare.deletePiece();
    }
    dstSquare.setPiece(srcSquare.getPiece());
    if (!lastPieceMoved)
    {
        dstSquare.getPiece()->setHasMoved(true);
    }
}

/**
* @brief Un-Does a move, reviving piece using variaBle lastPiece if one was eaten
*/
void Board::UnMove ()
{
    if (!undidMove)
    {
        lastSource->setPiece(lastDistination->getPiece());
        lastDistination->deletePiece();
        lastSource->getPiece()->setHasMoved(lastPieceMoved);
    }
}


bool Board::isCheck(piece_color playerToCheck){

    piece_color  enemyColor = (playerToCheck==white)? black: white;
    int kI=0,kJ=0;
    bool retVal = false;

    // get enemy moves
    unordered_set<Square> enemyDestinations = returnPlayerLegalMoves(enemyColor);

    //find player king
    for (int i = 0; i <8 ; ++i)
    {
        for (int j = 0; j <8 ; ++j)
        {
            if ((!squares[i][j].isEmpty()) &&
                (squares[i][j].getColor() == playerToCheck) &&
                (squares[i][j].getPiece()->getType() == king )){
                kI=i;
                kJ=j;
            }
        }
    }

    // check if player king is reachaBle
    if (enemyDestinations.find(squares[kI][kJ]) != enemyDestinations.end()) retVal = true;

    return retVal;
}


/**
* @brief Return true if player (PlayerToCheck) is in check after move
 *       Should be called only if a move is otherwise legal
*/
bool Board::isCheck (Square src, Square dst, piece_color playerToCheck)
{
    bool retVal = false;

    //do move
    move(src, dst);

    //check if check
    retVal = isCheck(playerToCheck);

    //undo move
    UnMove();

    //return Bool
    return retVal;
}

void Board::setLastSource(Square *lastSource)
{
    Board::lastSource = lastSource;
}

void Board::setLastDistination(Square *lastDistination)
{
    Board::lastDistination = lastDistination;
}


