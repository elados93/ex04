
// Created by Elad Aharon & Shahar Palmor.
// ID: 311200786 307929927
//

#include <iostream>
#include <limits>
#include "HumanPlayer.h"
using namespace std;

HumanPlayer :: HumanPlayer(char s) {
    this->symbol = s;
};

Point HumanPlayer::getMove(GameState &gameState) {
    int x,y;
    char dummy;

    while (true) {
        cin >> x >> dummy >> y;

        if (!cin.fail()) {
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //skip bad input
            return Point(x - 1, y - 1);
        }

        // user didn't input a number
        cout << "Please enter numbers only." << endl;
        cin.clear(); // reset fail bit
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //skip bad input
    }
}

char HumanPlayer::getSymbol() const {
    return symbol;
}




