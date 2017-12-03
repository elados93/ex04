
// Created by Elad Aharon & Shahar Palmor on 03/11/17.
// ID: 311200786 307929927
//

#ifndef EX02_CONSOLEPRINTER_H
#define EX02_CONSOLEPRINTER_H


#include "Printer.h"
#include "Player.h"

class ConsolePrinter : public Printer {
public:
    ConsolePrinter(Board &board1, Player &player1, Player &player2); // Constructor.
    ~ConsolePrinter();

    void printBoard();

    /**
     * Prints the all the possible moves of the given player which are given as arguments.
     * The function also support empty vector as no possible moves message.
     * @param p The current player.
     * @param v The possible points of p.
     */
    void printNextPlayerMove(Player &p, vector<Point *> v);

    /**
     * Gets the previous player and his last move ant prints it.
     * @param player The previous player.
     * @param point The last move of the player.
     */
    void printLastMove(Player &player, Point *point);

    /**
     * Gets a possible error and prints it accordingly.
     * @param outcome The error should be printed.
     */
    void printError(possible_outcome outcome);

    /**
     * Gets the winner and a possible status, may be WIN or DRAW.
     * Prints a message according to the arguments.
     * @param p The player who won.
     * @param status1 The status of the game, WIN or DRAW.
     */
    void printEndOfGame(Player &p, status status1);

    /**
  * Print the start menu of the game.
  */
    void printMenu();

    void printInformingGameStarted(owner currentOwner);

    void printWaitingForOtherPlayer(owner currentOwner);

private:
    Board &board;
    Player &player1; // A reference to player 1 from GameManager.
    Player &player2; // A reference to player 2 from GameManager.

    /**
     * Prints a line of commas for the board.
     */
    void printCommas() const;

    /**
     * Prints one line by a given "currentRow" argument.
     * With respect to the number of the number of he row.
     * @param currentRow The row to be printed.
     */
    void printLine(int currentRow) const;

    /**
     * Prints out of bound message.
     * The function called from printError function.
     */
    void printOutOfBound() const;

    /**
     * Prints occupied cell message.
     * The function called from printError function.
     */
    void printOccupiedCell() const;

    /**
     * Prints illegal move message.
     * The function called from printError function.
     */
    void printIllegalMove() const;

};


#endif //EX02_CONSOLEPRINTER_H
