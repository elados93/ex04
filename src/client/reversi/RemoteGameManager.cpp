
// Created by Elad Aharon Shahar Palmor
// ID: 311200786

#include <iostream>
#include <unistd.h>
#include <cstdlib>
#include "RemoteGameManager.h"
#include <string.h>
#include <sstream>
#include <fstream>

RemoteGameManager::RemoteGameManager(GameState &gameState, Player &player1, Player &player2, Printer &printer,
                                     GameRules &gameRules, Client &client1) :
        GameManager(gameState, player1, player2,
                    printer, gameRules, false), clientDetails(client1) {}

void RemoteGameManager::run() {
    status status1 = checkStatus();

    while (status1 == RUNNING) {
        playOneTurn();
        status1 = checkStatus();
    }

    printer.printBoard();
    printer.printLastMove(*currentPlayer, lastMove);

    owner winner = getWinner();
    owner currentOwner = currentPlayer == &player1 ? PLAYER_1 : PLAYER_2;
    if (checkStatus() == WIN) {
        if (winner == PLAYER_1)
            printer.printEndOfGame(player1, status1);
        if (winner == PLAYER_2)
            printer.printEndOfGame(player2, status1);
    }

    if (status1 == DRAW)
        printer.printEndOfGame(player1, DRAW);

    // Get any key to terminate the game
    string dummy;
    getline(cin, dummy);

    // The looser needs to send the END OF GAME message
    if (currentOwner != winner) {
        int stopGame = -2;
        int socket = clientDetails.getClientSocket();
        int n = write(socket, &stopGame, sizeof(stopGame));
        if (n == -1)
            throw "Error sending end of game to server";
    }

    delete (lastMove);
}

void RemoteGameManager::playOneTurn() {

    vector<Point *> *playerPossibleMoves;

    owner currentOwner, otherOwner; // Representing the enum for the current player & other player.
    Player *otherPlayer; // Representing the pointer to the other player.

    if (clientDetails.priority == 1) {// in case the player is player_1
        playerPossibleMoves = gameRules.getPossibleMoves(gameState, PLAYER_1);
        currentOwner = PLAYER_1;
        otherOwner = PLAYER_2;
        otherPlayer = &player2;
    } else { // in case the player is player_2
        playerPossibleMoves = gameRules.getPossibleMoves(gameState, PLAYER_2);
        currentOwner = PLAYER_2;
        otherOwner = PLAYER_1;
        otherPlayer = &player1;
    }

    //first run ever in the two clients game
    if (firstRun) {
        
        printer.printBoard();
        
        if (currentOwner == PLAYER_1) {

            // The first turn in the game player1 play.
            printer.printNextPlayerMove(*currentPlayer, *playerPossibleMoves);

            // Get a point from the player.
            lastMove = new Point(currentPlayer->getMove(gameState));
            gameRules.makeMove(gameState, *lastMove, currentOwner);
            printer.printBoard();
            // sending the move to the server
            clientDetails.sendPoint(lastMove->getX(), lastMove->getY());
        }
        // First run for second player
        if (currentOwner == PLAYER_2) {
            printer.printWaitingForOtherPlayer(currentOwner);
            // updating the board according the other players move
            if (translatePointFromServer() == 1) {
                gameRules.makeMove(gameState, *lastMove, otherOwner);
                gameRules.makePossibleMoves(gameState, currentOwner);
                printer.printBoard(); // print the board after the changes of player1
            }
            
            printer.printLastMove(*otherPlayer, lastMove); //prints other player last move
            printer.printNextPlayerMove(*currentPlayer, *playerPossibleMoves);
            if (lastMove != NULL)
                delete (lastMove);
            // making a move for the second player.
            lastMove = new Point(player1.getMove(gameState));
            gameRules.makeMove(gameState, *lastMove, currentOwner);
            printer.printBoard();
            clientDetails.sendPoint(lastMove->getX(), lastMove->getY());
        }
    } // end of first run
    else {
        // a regular move in which we update the board first and than play by the current player.
        printer.printWaitingForOtherPlayer(currentOwner);
        if (translatePointFromServer() == -1) {
            // In case the game end after the opponent move.
            if (checkStatus() != RUNNING)
                return;
        } else  {
            gameRules.makeMove(gameState, *lastMove, otherOwner);
            // In case the game end after the opponent move.
            if (checkStatus() != RUNNING)
                return;
        } // The other player played something
        
        
        
        printer.printBoard(); // print the board after the changes of player1

        printer.printLastMove(*otherPlayer, lastMove);

        // If the possible moves vector is empty send -1 to the server.
        if (playerPossibleMoves->empty()) {
            printer.printNextPlayerMove(*currentPlayer, *playerPossibleMoves); // sending empty vector and print "NO MOVE"
            string dummy; // Input any key from the user
            getline(cin, dummy);

            if (lastMove != NULL)
                delete (lastMove);

            lastMove = NULL;
            clientDetails.sendPoint(-1, -1);
        } else { // The player has at least one move.
            gameRules.makePossibleMoves(gameState, currentOwner);
            printer.printNextPlayerMove(*currentPlayer, *playerPossibleMoves);

            if (lastMove != NULL)
                delete (lastMove);

            lastMove = new Point(currentPlayer->getMove(gameState));
            gameRules.makeMove(gameState, *lastMove, currentOwner);
            printer.printBoard();
            clientDetails.sendPoint(lastMove->getX(), lastMove->getY());
        }
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

    int xValue, yValue;
    int socket = clientDetails.getClientSocket();

    // Read new move arguments from Src client.
    int n = read(socket, &xValue, sizeof(xValue));
    if (n == -1)
        throw "Error reading x value from Src client";

    // -1 meaning the player has no moves.
    if (xValue == -1) {

        if (lastMove != NULL)
            delete (lastMove);

        lastMove = new Point(-1, -1);
        return -1;
    }

    // Get the y value
    n = read(socket, &yValue, sizeof(yValue));
    if (n == -1)
        throw "Error reading y value from Src client";

    if (lastMove != NULL)
        delete (lastMove);

    
    lastMove = new Point(xValue, yValue);
    return 1;
}

Client * getClientFromFile(string fileName) {
    try {
        const char *serverSettingsFileName = fileName.c_str();
        ifstream fileInput(serverSettingsFileName);
        if (fileInput == NULL)
            perror("Error while open the server settings file");

        string IPString;
        string portString;
        getline(fileInput, IPString);
        getline(fileInput, portString);
        IPString = IPString.replace(0, sizeof("serverIP = ") - 1, "");
        IPString = IPString.replace(0, 0, "");
        portString = portString.replace(0, sizeof("port = ") - 1, "");
        stringstream stringstream1(portString);
        int port = 0;
        stringstream1 >> port;
        char *writable = new char[IPString.size() + 1];
        std::copy(IPString.begin(), IPString.end(), writable);
        writable[IPString.size()] = '\0';
        return new Client(writable, port);
    } catch (char* ex) {
        cout << "error while reading settings file";
        exit(-1);
    }
}

