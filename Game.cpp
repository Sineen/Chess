//
// Created by jherskow on 1/8/18.
//

#include <unordered_set>
#include "Game.h"
#include "Board.h"
#define MAKE_MOVE ": Please enter your move:"
#define WHITE_NAME "Enter white player name:"
#define BLACK_NAME "Enter black player name:"
#define CHECK "\33[37;41mCheck!\33[0m"
#define ILLEGAL "\33[37;41millegal move\33[0m"
#define WIN "won!"

using namespace std;

Game::Game()
{
    whitePlayer = setName(white);
    blackPlayer = setName(black);
    curPlayer = white;
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

void Game::win()
{
    cout << getName(curPlayer)<< WIN << endl;
}

int Game::makeMove()
{
    piece_color otherPlayer = (curPlayer==white)? black: white;

    // if in check
    if(board.isCheck(curPlayer)){

        // see if checkmate
        bool isCheckmate = seeIfCheckmate();

        if (isCheckmate){
            switchPlayer();
            win();
            return 100;
        }else{
            // there are good moves
            // announce check! and continue
            cout  << CHECK << endl;
        }
    }

    // check if castle
    if (nextMove == "o-o"){

        if (!board.smallCastle(curPlayer)){
            return 1;
        }
        return 0;

    }else if(nextMove == "o-o-o"){

        if (!board.largeCastle(curPlayer)){
            return 1;
        }
        return 0;

    }else{
        //otherwise this is a regular, 4-char move
        string srcStr = nextMove.substr(0,1);
        string dstStr = nextMove.substr(2,3);

        Square src = board.stringToSquare(srcStr);
        Square dst = board.stringToSquare(dstStr);

        if(!board.isLegal(src,dst,curPlayer)) return 1;


        // else move is legal movement - we must make sure it does not lead to check!
        if (board.isCheck(src,dst,curPlayer)){
            return 1;
        }

        //do move
        board.move(src, dst);
    }


    // were done.
    return 0;

}

void Game::playGame()
{
    int status = 0;
    while (status == 0){
        board.printBoard();   //todo check print
        status = moveCycle();
        switchPlayer();
    }

}

int Game::moveCycle()
{
    askForMove();

    int status = makeMove();
    while(status == 1){
        cout <<  ILLEGAL << endl;
        status = makeMove();
    }
    if(status == 100){
        return 1;
    }
    return 0;
}

int main()
{
    Game game;

    game.playGame();

    delete game;

    return 0;

}

bool Game::seeIfCheckmate()
{
///checged

    // get pieces
    unordered_set<Square, squareHasher, squareComparator> myPieces = board.returnPlayerPices(curPlayer);

    // get moves for each
    for(Square each :myPieces)
    {

        // get legal destinations for the Piece
        unordered_set<Square , squareHasher , squareComparator> legalDests = each.getPiece()->getSquaresCouldMove();
        // get the square for the piece
//        Square& *piecesSquare = each.getSquare();

        // check all of the dests to see if they get us out of check
        for(Square possibleDest : legalDests )
        {
            if (!board.isCheck(each, possibleDest, curPlayer))
            {
                return false;
            }
        }
    }

    return true;
}