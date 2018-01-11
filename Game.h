//
// Created by jherskow on 1/8/18.
//

#ifndef CPP_GAME_H
#define CPP_GAME_H

#include <iostream>
#include "Board.h"

using namespace std;

class Game
{

public:

    string CurPlayer;
    Board board;


    /**
    * @brief Contructor.
    */
    Game();

    /**
    * @brief Driver.
    */
    void playGame();

    /**
     * this function is a getter for the players names
     * @param color the number of player white player  black player
     * @return the name of the player  according to the parameter
     */
    string& getName(piece_color color) const;

    /**
     * @param number the number of the player white player  black player
     * @return sets the name of the  white player  black player
     */
    void setName(piece_color color);

    string askForMove(piece_color color) const;

    void win(piece_color color) const;

private:

    string& whitePlayer;
    string& blackPlayer;
    string nextMove;
    /**
     * @brief Gets a move from the user.
     */
    void _getMove();

};


#endif //CPP_GAME_H
