//
// Created by jherskow on 1/8/18.
//

#include "Game.h"


using namespace std;

void Game::setName(piece_color color)
{
    if ( color == white )
    {
        cout << "Enter white player name:"  << endl;
        cin >> whitePlayer;
    }
    else if (color == black)
    {
        cout << "Enter black player name:"  << endl;
        cin >> blackPlayer;
    }
    else
    {
        cerr <<" this is and ERROR in your request not a valid color ";
    }
}

string Game::getName(piece_color color) const
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
        return "this cant happen"; // what should we return in this case ?
    }
}
