//
// Created by jherskow on 1/8/18.
//

#include "Game.h"
#include "Board.h"
#define MAKE_MOVE ": Please enter your move:"
#define WHITE_NAME "Enter white player name:"
#define BLACK_NAME "Enter black player name:"
#define WIN "won!"

using namespace std;

Game::Game()
{
    whitePlayer = setName(white);
    blackPlayer = setName(black);
    Board board();
}

string Game::setName(piece_color color)
{
    string name;

    if ( color == white )
    {
        cout << WHITE_NAME  << endl;
    }
    else if (color == black)
    {
        cout << BLACK_NAME << endl;
    }
    cin >> name;

    return name;
}

string Game::getName(piece_color color) const
{
    if ( color == white )
    {
        return whitePlayer;
    }
    return blackPlayer;
}

void Game::switchPlayer()
{
    if ( curPlayer == white )
    {
        curPlayer = black;
    }
    curPlayer = white;
}

void Game::askForMove()
{

    cout << Game::getName(curPlayer) << MAKE_MOVE << endl;
    cin >> nextMove;
}

void Game::win(piece_color color) const
{
    Board::printBoard();
    cout << WIN << endl;
}

int Game::makeMove(string& move)
{


    Piece *oldSource, *oldDest;


    // todo check if in check
                // todo - if in check at start - check all moves by piece
                // todo - if no good moves - other player won!
                // todo - if there is good moves - announce check!


    if (move == "o-o"){
        if (!board.CanSmallCastle(curPlayer)){
            return 1;
        }
        // save original positions
        // todo small castle

    }else if(move == "o-o-o"){
        if (!board.CanLargeCastle(curPlayer)){
            return 1;
        }
        // save original positions
        //todo large castle

    }
    //otherwise this is a regular, 4-char move
    string srcStr = move.substr(0,1);
    string dstStr = move.substr(2,3);

    Square& src = board(srcStr);
    Square& dst = board(dstStr);

    // make sure source is not-empty and player color
    if (src.isEmpty()) {return 1;}
    Piece* playingPiece = src.getPiece();
    if (src.getPiece()->getColor() != curPlayer) {return 1;}

    //make a list of places
    set<Square> legalDestinations = playingPiece->ReturnSquaresInRange();

    //if illegal
    if(legalDestinations.find(dst)){
        return 1;
    }

    // else move is legal movement - we must make sure it does not lead to check
    oldSource = src.getPiece();
    oldDest = dst.getPiece();

    // do move
    //todo do move

    if (board.isCheck())


}


