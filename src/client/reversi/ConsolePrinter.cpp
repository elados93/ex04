
// Created by Elad Aharon & Shahar Palmor.
// ID: 311200786 307929927
//

#include <iostream>
#include "ConsolePrinter.h"

using namespace std;

ConsolePrinter::ConsolePrinter(Board &board1, Player &player1, Player &player2) : board(board1), player1(player1),
                                                                                 player2(player2) {}

ConsolePrinter::~ConsolePrinter() {}

void ConsolePrinter::printBoard() {
    int row = this->board.getRow();
    int col = this->board.getCol();

    cout << "Current board:" << endl << endl;

    // Print the numbers of the columns.
    cout << " |";
    for (int i = 1; i <= col; i++) {
        cout << ' ' << i << " |";
    }
    cout << endl;

    // Print a line of commas.
    printCommas();

    // Print each line of the board.
    for (int i = 0; i < row; i++)  {
        printLine(i);
    }
}

// Print a line of commas.
void ConsolePrinter :: printCommas() const {
    int col = this->board.getCol();

    cout << "--";
    // Print commas as separators
    for (int i = 0; i < col; i++) {
        cout << "----";
    }
    cout << endl;
}

// Print a given line of the board.
void ConsolePrinter :: printLine(int currentRow) const {
    int col = this->board.getCol();

    // Print the number of the row at the start
    cout << currentRow + 1 << '|';

    for (int currentCol = 0; currentCol < col; currentCol++) {
        Point p(currentRow, currentCol);

        owner symbolToCheck = this->board.getCell(p).getSymbol();

        if (symbolToCheck == PLAYER_1) {
            cout << ' ' << this->player1.getSymbol() << " |";
        } else  if (symbolToCheck == PLAYER_2) {
                cout << ' ' << this->player2.getSymbol() << " |";
            } else {
            cout << "   |";
            }
    }
    cout << endl;

    printCommas();
}

void ConsolePrinter::printNextPlayerMove(Player &p, vector<Point *> v)  {

    cout << p.getSymbol() << ": It's your move." << endl;

    // Check if there are any possible moves at all.
    if (v.empty()) {
        cout << "No possible moves. Play passes back to the other player. Press any key to continue." << endl;
    }
    else {

        // Print the possible moves of the player.
        if (v.size() == 1) {
            cout << "Your possible move is: ";
        } else {
            cout << "Your possible moves: ";
        }

        for (unsigned int i = 0; i < v.size(); ++i) {
            cout << v.at(i)->toString() << " ";
        }

        cout << endl << "Please enter your move row, col: \n";
    }
}

void ConsolePrinter::printLastMove(Player &player, Point *point)  {

    // If the point is null the last player didn't play.
    if (point == NULL || point->isEqual(Point(-1, -1))) {
        cout << player.getSymbol() << " didn't played." << endl;
    } else {
        cout << player.getSymbol() << " played " << (*point).toString() << endl;
    }

}

void ConsolePrinter::printOutOfBound() const {
    cout << "Point out of bound! enter a valid point" << endl;
}

void ConsolePrinter::printOccupiedCell() const {
    cout << "Occupied cell! enter a valid point" << endl;
}

void ConsolePrinter::printIllegalMove() const {
    cout << "Illegal move! enter a valid point" << endl;
}

void ConsolePrinter::printEndOfGame(Player &p, status status1) {
    if (status1 == WIN) {
        cout << p.getSymbol() << " Won! congrats! Press any key to continue." << endl;
    } else {
        cout << "Draw! Press any key to continue.";
    }
}

void ConsolePrinter::printError(possible_outcome outcome) {
    switch (outcome) {
        case OUT_OF_BOUND: printOutOfBound();
            break;
        case ILLEGAL_MOVE : printIllegalMove();
            break;
        case OCCUPIED_CELL : printOccupiedCell();
            break;
        default:
            break;
    }
}

void ConsolePrinter::printMenu() {
    cout << "Welcome to Reversi Game! :)" << endl << endl;
    cout << "Choose an opponent type:" << endl;
    cout << "1. a human local player" << endl;
    cout << "2. an AIPlayer" << endl;
    cout << "3. a remote player" << endl << endl;
}

void ConsolePrinter::printInformingGameStarted(owner currentOwner) {
    if(currentOwner == PLAYER_1){
        cout << "Waiting for Player #2 move" << endl << endl;
    }
    else{
        cout << "Game started, waiting for player #1 move" << endl << endl;
    }

}

void ConsolePrinter::printWaitingForOtherPlayer(owner currentOwner) {
    if(currentOwner == PLAYER_1){
        cout << "Waiting for Player #2 move" << endl << endl;
    }
    else{
        cout << "waiting for player #1 move" << endl << endl;
    }
}
