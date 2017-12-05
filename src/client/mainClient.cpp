
// Created by Elad Aharon & Shahar Palmor on 28/11/17.
// ID: 311200786

#include "Client.h"
#include "reversi/Board.h"
#include "reversi/GameState.h"
#include "reversi/HumanPlayer.h"
#include "reversi/AIPlayer.h"
#include "reversi/ConsolePrinter.h"
#include "reversi/GameManager.h"
#include "reversi/RemoteGameManager.h"
#include <iostream>
#include <fstream>

Client * getClientFromFile();

using namespace std;

int main() {

    Board *board = new Board();
    GameState gameState1(board);
    ReversiDefaultRules *gameRules = new ReversiDefaultRules();

    HumanPlayer p1('x');
    AIPlayer pAI('o', *gameRules);
    HumanPlayer p3('o');

    ConsolePrinter *menuConsole = new ConsolePrinter(*board, p1, p3);
    menuConsole->printMenu(); // Print the 3 options to the client.
    delete (menuConsole);

    int inputAIGameOrNot;
    cin >> inputAIGameOrNot;

    switch (inputAIGameOrNot) {
        case 1: {
            ConsolePrinter printer1(*board, p1, p3);
            GameManager game1(gameState1, p1, p3, printer1, *gameRules, false);
            game1.run(); // Run the game vs local human.
            break;
        }
        case 2: {

            ConsolePrinter printer2(*board, p1, pAI);
            GameManager game2(gameState1, p1, pAI, printer2, *gameRules, true);
            game2.run(); // Run the game vs Computer.
            break;
        }
        case 3: {
            Client *client = getClientFromFile();
            try {
                client->connectToServer();
            } catch (const char *msg) {
                cout << "Failed to connect to server. Reason: " << msg << endl;
                return 0;
            }
            ConsolePrinter printer3(*board, p1, p3);
            int priorityClient = client->getPriority();
            printer3.printInformingGameStarted(client->priority == 1 ? PLAYER_1 : PLAYER_2);
            RemoteGameManager game3(gameState1, p1, p3, printer3, *gameRules, *client);
            game3.setCurrentPlayer(priorityClient);

            game3.run();
            delete(client);
            break;
        }

        default: {
            cout << "Enter a valid option! :(" << endl;
            main();
            break;
        }

    }

    delete (gameRules);

    return 0;
}

Client *getClientFromFile() {
    ifstream inFile;
    inFile.open("../settings.txt");
    if (!inFile)
        throw "Error opening the settings file!";
    else {
        int port;
        string dummy, ip;

        inFile >> dummy;
        inFile >> dummy;
        inFile >> ip;
        inFile >> dummy;
        inFile >> dummy;

        inFile >> port;

        Client *client = new Client(ip.c_str(), port);
        inFile.close();
        return client;
    }
}
