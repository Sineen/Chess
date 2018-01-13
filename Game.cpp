//
// Created by jherskow on 1/8/18.
//

#include <unordered_set>
#include "Game.h"
#define MAKE_MOVE ": Please enter your move:"
#define WHITE_NAME "Enter white player name:"
#define BLACK_NAME "Enter black player name:"
#define ILLEGAL "Illegal Move!" // todo change to requestef
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
    int quit = 0;
    piece_color otherPlayer = (curPlayer==white)? black: white;

    // todo check if in check
    if(board.isCheck(curPlayer)){ //todo make func w this sgnature


        // get pieces
		unordered_set<Piece> myPieces = board.returnPlayerPices(curPlayer);

        // get moves for each
        for(Piece each :myPieces){

            // get legal destinations for the Piece
            unordered_set<Square> legalDests = each.getSquaresCouldMove();
            // get the square for the piece
            Square& *piecesSquare = each.getSquare();

            // check all of the dests to see if they get us out of check
            for(Square possibleDest : legalDests ){
                if (! board.isCheck(*piecesSquare,possibleDest,curPlayer)){
                    quit =1;
                    break;
                }

            }
            if (quit==1) break;
        }

        if (quit == 0){
            switchPlayer();
            win();
            return 100;
        }

        // todo - otherwise.  there is good moves - announce check! and continue

    }

    if (nextMove == "o-o"){
        if (!board.CanSmallCastle(curPlayer)){
            return 1;
        }
        // save original positions
        // todo small castle


    }else if(nextMove == "o-o-o"){
        if (!board.CanLargeCastle(curPlayer)){
            return 1;
        }
        // save original positions
        //todo large castle

    }
    //otherwise this is a regular, 4-char move
    string srcStr = nextMove.substr(0,1);
    string dstStr = nextMove.substr(2,3);

    Square src = board.stringToSquare(srcStr);
    Square dst = board.stringToSquare(dstStr);

    if(!board.isLegal(src,dst,curPlayer)) return 1;


    // else move is legal movement - we must make sure it does not lead to check
    if (board.isCheck(src,dst,curPlayer)){
        return 1;
    }

    //todo do move

    // if ok, were done.
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
        cout << "\33[" << W_TXT_RD_BK  << ILLEGAL << " \33[0m\n";
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