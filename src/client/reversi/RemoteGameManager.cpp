
// Created by Elad Aharon on 01/12/17.
// ID: 311200786
//

#include <iostream>
#include <unistd.h>
#include <cstring>
#include <cstdlib>
#include "RemoteGameManager.h"
#include "HumanPlayer.h"

RemoteGameManager::RemoteGameManager(GameState &gameState, Player &player1, Player &player2, Printer &printer,
                                     GameRules &gameRules, Client client1) :
        GameManager(gameState, player1, player2,
                    printer, gameRules, false), clientDetails(client1) {

}

void RemoteGameManager::run() {
    status status1 = checkStatus();

    while (status1 == RUNNING) {
        playOneTurn();
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
    int socket = clientDetails.getClientSocket();
    int n = write(socket, &buffer, sizeof(buffer));
    if (n == -1)
        throw "Error sending end of game to server";
}

void RemoteGameManager::playOneTurn() {
    printer.printBoard();
    vector<Point *> playerPossibleMoves;

    owner currentOwner, otherOwner; // Representing the enum for the current player.
    Player *otherPlayer = &player1;
    if (clientDetails.priority == 1) {// in case the player is player_1
        playerPossibleMoves = gameRules.getPossibleMoves(gameState, PLAYER_1);
        currentOwner = PLAYER_1;
        otherOwner = PLAYER_2;
        otherPlayer = &player2;
    } else { // in case the player is player_1
        playerPossibleMoves = gameRules.getPossibleMoves(gameState, PLAYER_2);
        currentOwner = PLAYER_2;
        otherOwner = PLAYER_1;
        otherPlayer = &player1;
    }


    // If the possible moves vector is empty send -1 to the server.
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
        int socketCopy = clientDetails.getClientSocket();
        int n = write(socketCopy, &noMove, sizeof(noMove));
        if (n == -1) {
            throw "Can't send no move back to server";
        }
        return;
    }
    //first run ever in the two clients game
    if (firstRun) {
        if (currentOwner == PLAYER_1) {

            // The first turn in the game player1 play.
            printer.printNextPlayerMove(*currentPlayer, playerPossibleMoves);

            // Get a point from the player.
            lastMove = new Point(currentPlayer->getMove(gameState));
            gameRules.makeMove(gameState, *lastMove, currentOwner);
            // sending the move to the server
            clientDetails.sendPoint(lastMove->getX(), lastMove->getY());
        }
        // First run for second player
        if (currentOwner == PLAYER_2) {
            // updating the board according the other players move
            if (translatePointFromServer() == 1) {
                gameRules.makeMove(gameState, *lastMove, otherOwner);
                gameRules.makePossibleMoves(gameState, currentOwner);
            }
            if (lastMove != NULL)
                delete (lastMove);
            // making a move for the current player.
            lastMove = new Point(player1.getMove(gameState));
            gameRules.makeMove(gameState, *lastMove, currentOwner);
            clientDetails.sendPoint(lastMove->getX(), lastMove->getY());
        }
    } // end of first run
    else {
        //  a regular move in which we update the board first and than play by the current player.
        if (translatePointFromServer() != -1)
            printer.printLastMove(*otherPlayer, lastMove);

        gameRules.makeMove(gameState, *lastMove, otherOwner);
        gameRules.makePossibleMoves(gameState, currentOwner);

        printer.printNextPlayerMove(*currentPlayer, playerPossibleMoves);

        if (lastMove != NULL)
            delete (lastMove);

        lastMove = new Point(currentPlayer->getMove(gameState));
        gameRules.makeMove(gameState, *lastMove, currentOwner);
        clientDetails.sendPoint(lastMove->getX(), lastMove->getY());
    }
    // making sure the o player will not have a first run
    firstRun = false;
}

void RemoteGameManager::setCurrentPlayer(int playerNumber) {
    if (playerNumber == 1)
        currentPlayer = &player1;
    if (playerNumber == 2)
        currentPlayer = &player2;
}

int RemoteGameManager::translatePointFromServer() {

    char *xValue, *yValue;
    char dummyComma;
    int socket = clientDetails.getClientSocket();

    // Read new move arguments from Src client.
    int n = read(socket, &xValue, sizeof(xValue));
    if (n == -1)
        throw "Error reading x value from Src client";

    if (strcmp(xValue, "-1") == 0) {

        if (lastMove != NULL)
            delete (lastMove);

        lastMove = new Point(-1, -1);
        return -1;
    }

    // Get the comma separator
    n = read(socket, &dummyComma, sizeof(dummyComma));
    if (n == -1)
        throw "Error reading dummy comma from Src client";

    // Get the y value
    n = read(socket, &yValue, sizeof(yValue));
    if (n == -1)
        throw "Error reading y value from Src client";

    if (lastMove != NULL)
        delete (lastMove);

    lastMove = new Point(atoi(xValue), atoi(yValue));
    return 1;
}

