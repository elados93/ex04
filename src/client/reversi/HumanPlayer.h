
// Created by Elad Aharon & Shahar Palmor on 03/11/17.
// ID: 311200786 307929927
//

#ifndef EX02_HUMANPLAYER_H
#define EX02_HUMANPLAYER_H

#include "Point.h"
#include "Player.h"
#include "GameState.h"


class HumanPlayer : public Player{
public:
    HumanPlayer(char s);

    /**
     * Get the move from the user according to the rules of the game.
     * @return The valid input point from user.
     */
    Point getMove(GameState &gameState);
    char getSymbol() const;

private:
    char symbol;
};


#endif //EX02_HUMANPLAYER_H
