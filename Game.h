//
// Created by jherskow on 1/8/18.
//

#ifndef CPP_GAME_H
#define CPP_GAME_H

#include <iostream>
#include "Board.h"
#include "enums.h"

class Game
{
private:

    std::string whitePlayer;
    std::string blackPlayer;
    std::string nextMove;
    piece_color curPlayer;

    /**
     * @brief Gets a move from the user.
     */
    void askForMove();

    int makeMove();

    void switchPlayer();

    int moveCycle();

    bool seeIfCheckmate();

public:
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
    std::string getName(piece_color color) const;

    /**
     * @param number the number of the player white player  black player
     * @return sets the name of the  white player  black player
     */
    std::string setName(piece_color color);

    void win();

};


#endif //CPP_GAME_H
