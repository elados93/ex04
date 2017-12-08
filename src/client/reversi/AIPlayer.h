
// Created by Elad Aharon & Shahar Palmor.
// ID: 311200786 307929927
//

#include "Player.h"
#include "GameRules.h"
#include "GameState.h"

#ifndef EX02_AIPLAYER_H
#define EX02_AIPLAYER_H

/**
 * class AIPlayer for a player of computer type.
 */
class AIPlayer : public Player {

public:
    /**
     * constructor.
     * @param s is the symbol representing the computer player.
     * @param gameRules1 is the logic of the game, that the player must obay to.
     */
    AIPlayer(char s, GameRules &gameRules1);

    /**
     * get move function gets a state of the game and checks for the best move of the player and returns it.
     * @param gameState is the current state of the game right after Player A played.
     * @return the move that the computer players wants to do.
     */
    Point getMove(GameState &gameState);

    /**
     * get the symbol of the computer player.
     * @return the symbol.
     */
    char getSymbol() const;

private:

    // members
    GameRules &gameRules;
    char symbol;

    /**
     * this function play a demo game for the AI player. it gets each state of the AI player and checks for the
     * best move of  Player A after AI played. in order to predict the best move of the AI so that when player A will
     * play after he wont get a lot of points.
     * it gets the best move of the A player for each AI move by scoring the AI moves so that get move wold hold the best move.
     * @param demoGame is the state of the game after one of AI moves.
     * @return the score that represent the best move of AI player.
     */
    int playDemo(GameState &demoGame);
};


#endif //EX02_AIPLAYER_H
