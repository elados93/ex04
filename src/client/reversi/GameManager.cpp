
// Created by Elad Aharon & Shahar Palmor on 03/11/17.
// ID: 311200786 307929927
//

#include <iostream>
#include "GameManager.h"

using namespace std;


GameManager::GameManager(GameState &gameState1, Player &player1, Player &player2, Printer &printer,
                         GameRules &gameRules, bool aiPlayer) : gameState(gameState1), player1(player1),
                                                                player2(player2), printer(printer),
                                                                gameRules(gameRules),
                                                                currentPlayer(), isAIPlayer(aiPlayer) {
    this->currentPlayer = &this->player1;
    this->lastMove = NULL;
    this->firstRun = true;
    this->isAIPlayer = aiPlayer;
}

owner GameManager::getWinner() const {
    int p1Counter = 0, p2Counter = 0;
    int row = gameState.board->getRow();
    int col = gameState.board->getCol();

    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            Point p(i, j);
            if (gameState.board->getCell(p).getSymbol() == PLAYER_1)
                p1Counter++;
            else
                p2Counter++;
        }
    }
    if (p1Counter > p2Counter)
        return PLAYER_1;

    if (p1Counter < p2Counter)
        return PLAYER_2;

    return NONE;
}

status GameManager::checkStatus() {
    gameRules.makePossibleMoves(gameState, PLAYER_1);
    gameRules.makePossibleMoves(gameState, PLAYER_2);

    bool isFirstEmpty = gameState.vec1.empty();
    bool isSecondEmpty = gameState.vec2.empty();

    if (gameState.board->isBoardFull() || (isFirstEmpty && isSecondEmpty)) {
        owner result = getWinner();
        if (result == NONE)
            return DRAW;
        else
            return WIN;

    }

    return RUNNING;
}

void GameManager::run() {
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
}

void GameManager::playOneTurn() {

    if (isAIPlayer && currentPlayer == &player1) // Print the board for player1 v.s the AIPlayer.
        printer.printBoard();
    if (!isAIPlayer) // Print the board normally when 2 humans play.
        printer.printBoard();

    possible_outcome result;
    vector<Point *> playerPossibleMoves;

    if (currentPlayer == &player1) {
        playerPossibleMoves = gameRules.getPossibleMoves(gameState, PLAYER_1);
    } else {
        playerPossibleMoves = gameRules.getPossibleMoves(gameState, PLAYER_2);
    }

    // If the game v.s the computer and it's player1 turn OR 2 humans are playing aware they have no move.
    if ((!isAIPlayer && playerPossibleMoves.empty()) ||
        (isAIPlayer && playerPossibleMoves.empty() && currentPlayer == &player1)) {
        printer.printLastMove(*currentPlayer, lastMove);
        printer.printNextPlayerMove(*currentPlayer, playerPossibleMoves);
        char dummy; // Input any key from the user
        cin >> dummy;

        if (lastMove != NULL) {
            delete (lastMove);
        }

        lastMove = NULL;
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
        result = gameRules.makeMove(gameState, *lastMove, PLAYER_1);
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
            result = gameRules.makeMove(gameState, *lastMove, PLAYER_1);
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

    // If the result isn't well defined check again.
    if (result != SUCCESS) {
        inputUntilValid(result);
    }
}

void GameManager::inputUntilValid(possible_outcome result) {
    owner currentP;

    if (currentPlayer == &player1) {
        currentP = PLAYER_1;
    } else {
        currentP = PLAYER_2;
    }

    while (result != SUCCESS) {
        printer.printError(result);
        if (lastMove != NULL) {
            delete (lastMove);
        }
        lastMove = new Point(currentPlayer->getMove(gameState));
        result = gameRules.makeMove(gameState, *lastMove, currentP);
    }
}




