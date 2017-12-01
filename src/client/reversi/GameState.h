
// Created by Elad Aharon & Shahar Palmor on 17/11/17.
// ID: 311200786 307929927

#ifndef EX02_GAMESTATE_H
#define EX02_GAMESTATE_H

#include "ReversiDefaultRules.h"
#include "Board.h"
/**
 * class GameState - show a specific state of the game - with a specific board, and options for
 * both of the players.
 */
class GameState {

public:
    /**
     * constructor.
     * @param board1
     */
    GameState(Board *board1);

    /**
     * copy constructor.
     * @param gameState
     */
    GameState(GameState &gameState);

    /**
     * destructor.
     */
    virtual ~GameState();

    /**
     * operator  =  to create a new game state as the one we got as a paramter
     * @param copyGameState is the the game state to compare.
     * @return a new game state with th same data.
     */
    GameState& operator = (const GameState& copyGameState);

    bool compare2Vectors(vector<Point *> &v1, vector<Point *> &v2) const;

    Board *getBoard() const;

    /**
     * making game state a friend of some classes so that they can use the game state members.
     */
    friend class ReversiDefaultRules;
    friend class AIPlayer;
    friend class GameManager;

private:
    //members.
    Board *board;
    vector<Point*> vec1; // Vector with all the possible points of player 1.
    vector<Point*> vec2; // Vector with all the possible points of player 2.
};


#endif //EX02_GAMESTATE_H
