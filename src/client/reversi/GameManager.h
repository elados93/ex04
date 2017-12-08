
// Created by Elad Aharon & Shahar Palmor.
// ID: 311200786 307929927
//

#ifndef EX02_GAMEMANAGER_H
#define EX02_GAMEMANAGER_H

#include "Board.h"
#include "Printer.h"
#include "GameRules.h"
#include "Player.h"

class GameManager {
public:
    GameManager(GameState &gameState, Player &player1, Player &player2, Printer &printer,
                GameRules &gameRules, bool aiPlayer); // Constructor

    /**
     * Run the game until there is a winner or draw situation.
     */
    virtual void run();

protected:
    GameState &gameState;
    Player &player1; // Reference to player 1.
    Player &player2; // Reference to player 2.
    Printer &printer; // Reference to the printer.
    GameRules &gameRules; // Reference to the game rules with the game logic.
    Player *currentPlayer; // Pointer to the current player.
    bool firstRun; // Boolean switch if it's the first turn.
    Point *lastMove; // Pointer to the last player move, NULL if there isn't one.
    bool isAIPlayer; // True if the second player is AIPlayer.

    /**
     * Return the current status of the game. The game will end if the board
     * is full or the players has no more moves to play. The status may be
     * WIN, DRAW or RUNNING.
     * @return The current status of the game.
     */
    status checkStatus();

    owner getWinner() const;

    /**
     * Play one turn of the game, starts with input from the current player.
     * Check the inputs validation and act accordingly.
     */
    void playOneTurn();

    /**
     * The function keep on getting input from the user until it's valid.
     * The function prints messages with respect to the input.
     * @param result The result of the last input.
     */
    void inputUntilValid(possible_outcome result);
};


#endif //EX02_GAMEMANAGER_H
