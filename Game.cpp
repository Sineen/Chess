//
// Created by jherskow on 1/8/18.
//

#include "Game.h"
#define MAKE_MOVE ": Please enter your move:"
#define WHITE_NAME "Enter white player name:"
#define BLACK_NAME "Enter black player name:"
#define WIN "won!"

using namespace std;

void Game::setName(piece_color color)
{
    if ( color == white )
    {
        cout << WHITE_NAME  << endl;
        cin >> whitePlayer;
    }
    else if (color == black)
    {
        cout << BLACK_NAME << endl;
        cin >> blackPlayer;
    }
    else
    {
        cerr <<" this is and ERROR in your request not a valid color ";
    }
}

string& Game::getName(piece_color color) const
{
    if ( color == white )
    {
        return Game::whitePlayer;
    }
    else if (color == black)
    {
        return Game::blackPlayer;
    }
    else
    {
        cerr <<" this is and ERROR in your request not valid color";
        return (string &) nullptr; // what should we return in this case ?
    }
}

string Game::askForMove(piece_color color) const
{

    cout << Game::getName(color) << MAKE_MOVE << endl;
    cin >> nextMove;
    return  nextMove;
}

void Game::win(piece_color color) const
{
    Board::printBoard();
    cout << WIN << endl;
}


