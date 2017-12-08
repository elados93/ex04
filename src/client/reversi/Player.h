// Created by Elad Aharon & Shahar Palmor.
// ID: 311200786 307929927

#ifndef EX02_PLAYER_H
#define EX02_PLAYER_H

#include "GameState.h"

class Player {
public:
    virtual char getSymbol() const = 0;
    virtual Point getMove(GameState &gameState) = 0;
};


#endif //EX02_PLAYER_H
