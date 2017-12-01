
// Created by Elad Aharon on 28/11/17.
// ID: 311200786

#include "Client.h"
#include "reversi/Board.h"
#include "reversi/GameState.h"
#include "reversi/HumanPlayer.h"
#include "reversi/AIPlayer.h"
#include "reversi/ConsolePrinter.h"
#include "reversi/GameManager.h"
#include <iostream>

using namespace std;

int main() {

    Board *board = new Board(4, 4);
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
            ConsolePrinter printer3(*board, p1, p3);
            GameManager game3(gameState1, p1, p3, printer3, *gameRules, false);

            int row, col;
            char dummy;

            Client client("127.0.0.1", 4444);
            try {
                client.connectToServer();
            } catch (const char *msg) {
                cout << "Failed to connect to server. Reason: " << msg << endl;
                return 0;
            }

            client.getPriority();

            while (true) { // while the game is running


                cout << "Enter a point (e.g. 3,4):";
                cin >> row >> dummy >> col;

                cout << "Sending point: " << row << dummy
                     << col << endl;
                try {
                    int result = client.sendPoint(row, dummy, col);
                    cout << "Result: " << result << endl;
                } catch (const char *msg) {
                    cout << "Failed to send point to server. Reason: " << msg << endl;
                }

                break;
            }
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