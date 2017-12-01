
// Created by Elad Aharon on 01/12/17.
// ID: 311200786
//

#include <iostream>
#include <unistd.h>
#include "RemoteGameManager.h"

RemoteGameManager::RemoteGameManager(GameState &gameState, Player &player1, Player &player2, Printer &printer,
                                     GameRules &gameRules, int socket1) :
                                     GameManager(gameState, player1, player2,
                                                 printer, gameRules, false), Client(client1) {}

void RemoteGameManager::run() {
    status status1 = checkStatus();

    while (status1 == RUNNING) {
        playOneTurn();
        if (currentPlayer == &player1) {
            currentPlayer = &player2;
        } else {
            currentPlayer = &player1;
        }
        status1 = checkStatus();
    }

    printer.printBoard();
    printer.printLastMove(*currentPlayer, lastMove);

    if (checkStatus() == WIN) {
        owner winner = getWinner();
        if (winner == PLAYER_1)
            printer.printEndOfGame(player1, status1);

        if (winner == PLAYER_2)
            printer.printEndOfGame(player2, status1);

        char dummy;
        cin >> dummy;
    }

    if (status1 == DRAW)
        printer.printEndOfGame(player1, DRAW);

    delete (lastMove);

    char buffer[4] = "END";
    int n = write(clientDetails.getClientSocket(), &buffer, sizeof(buffer));
    if (n == -1)
        throw "Error sending end of game to server";
}

void RemoteGameManager::playOneTurn() {
    printer.printBoard();
    vector<Point *> playerPossibleMoves;

    if (currentPlayer == &player1) {
        playerPossibleMoves = gameRules.getPossibleMoves(gameState, PLAYER_1);
    } else {
        playerPossibleMoves = gameRules.getPossibleMoves(gameState, PLAYER_2);
    }

    // If the game v.s the computer and it's player1 turn OR 2 humans are playing aware they have no move.
    if (playerPossibleMoves.empty()) {
        printer.printLastMove(*currentPlayer, lastMove);
        printer.printNextPlayerMove(*currentPlayer, playerPossibleMoves); // sending empty vector and print "NO MOVE"
        char dummy; // Input any key from the user
        cin >> dummy;

        if (lastMove != NULL) {
            delete (lastMove);
        }

        lastMove = NULL;
        char *noMove = "-1";
        int n = write(clientDetails.getClientSocket(), &noMove, sizeof(noMove))
        if (n == -1) {
            throw "no move";
        }
        return;
    }

    if (firstRun) {
        // The first turn in the game player1 play.
        printer.printNextPlayerMove(player1, playerPossibleMoves);

        if (lastMove != NULL) {
            delete (lastMove);
        }
        // Get a point from the player.
        lastMove = new Point(player1.getMove(gameState));
        gameRules.makeMove(gameState, *lastMove, PLAYER_1);

        firstRun = false;

        gameRules.makePossibleMoves(gameState, PLAYER_2);
    } else { // It's not the first turn in the game.

        if (currentPlayer == &player1) {

            // Player 1 turn.
            printer.printLastMove(player2, lastMove);
            if (lastMove != NULL) {
                delete (lastMove);
            }

            printer.printNextPlayerMove(player1, playerPossibleMoves);
            lastMove = new Point(player1.getMove(gameState));
            gameRules.makeMove(gameState, *lastMove, PLAYER_1);
            gameRules.makePossibleMoves(gameState, PLAYER_2);

        } else {
            // Player 2 turn.
            if (isAIPlayer) {
                if (lastMove != NULL) {
                    delete (lastMove);
                }

                lastMove = new Point(player2.getMove(gameState));

                if (!lastMove->isEqual(Point(-1, -1))) { // Check the option of AIPlayer which has no moves.
                    result = gameRules.makeMove(gameState, *lastMove, PLAYER_2);
                    gameRules.makePossibleMoves(gameState, PLAYER_1);
                } else
                    result = SUCCESS; // AIPlayer didn't player but the show must go on.
            } else { // The option where player 2 is human.
                printer.printLastMove(player1, lastMove);

                if (lastMove != NULL) {
                    delete (lastMove);
                }

                printer.printNextPlayerMove(player2, playerPossibleMoves);

                lastMove = new Point(player2.getMove(gameState));

                result = gameRules.makeMove(gameState, *lastMove, PLAYER_2);

                gameRules.makePossibleMoves(gameState, PLAYER_1);
            }

        } // End Player2 flow.

    }

}
