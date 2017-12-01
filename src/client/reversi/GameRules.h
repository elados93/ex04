
// Created by Elad Aharon & Shahar Palmor on 29/10/17.
// ID: 311200786 307929927

#ifndef EX02_GAMERULES_H
#define EX02_GAMERULES_H


#include <vector>
#include "Point.h"
#include "GenralDef.h"

using namespace std;

class GameState;

class GameRules {
public:

    virtual ~GameRules() {};
    /**
     *  Make the vector of possible moves of "symbol" and also returns it.
     *  Notice the difference with getPossibleMoves function that's only returns it.
     * @param symbol The player.
     * @return The vector of possible points of symbol.
     */
    virtual vector<Point *> makePossibleMoves(GameState &gameState, owner symbol) = 0;

    /**
 * Returns the possible moves of "symbol"
 * @param symbol The player.
 * @return Possible moves of symbol.
 */
    virtual vector<Point *> getPossibleMoves(GameState &gameState, owner symbol) = 0;

    /**
     * Make a single move of "symbol" at point p.
     * @param p Given point to mark.
     * @param symbol The player who plays.
     * @return Possible outcome of the procedure.
     */
    virtual possible_outcome makeMove(GameState &gameState, Point &p, owner symbol) = 0;
};


#endif //EX02_GAMERULES_H
