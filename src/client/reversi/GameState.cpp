
// Created by Elad Aharon & Shahar Palmor on 17/11/17.
// ID: 311200786 307929927
//

#include "GameState.h"

GameState::GameState(Board *board1) : board(board1) {}

GameState::GameState(GameState &gameState) {
    //creates a new board like the board of the game state we get.
    board = new Board(*gameState.board);
    
    // creating the same vectors of the options of the player as the game state parameter.
    for (unsigned int i = 0; i < gameState.vec1.size(); i++) {
        Point *pointToBeAdded = new Point(*gameState.vec1.at(i));
        this->vec1.push_back(pointToBeAdded);
    }

    for (unsigned int i = 0; i < gameState.vec2.size(); i++) {
        Point *pointToBeAdded = new Point(*gameState.vec2.at(i));
        this->vec2.push_back(pointToBeAdded);
    }

}

GameState::~GameState() {
    delete (board);

    for (unsigned int i = 0; i < vec1.size(); i++) {
        delete (vec1.at(i));
    }
    vec1.clear();

    for (unsigned int i = 0; i < vec2.size(); i++) {
        delete (vec2.at(i));
    }
    vec2.clear();

}

bool GameState::compare2Vectors(vector<Point *> &v1, vector<Point *> &v2) const {
    bool boolTerm = true;
    for (unsigned int i = 0; i < v1.size(); ++i) {
        for (unsigned int j = 0; j < v2.size(); ++j) {
            if (!v1.at(i)->isEqual(*v2.at(j)))
                boolTerm = false;
            else {
                boolTerm = true;
                break;
            }
        }
        if (!boolTerm)
            break;
    }

    for (unsigned int i = 0; i < v2.size(); ++i) {
        for (unsigned int j = 0; j < v1.size(); ++j) {
            if (!v2.at(i)->isEqual(*v1.at(j)))
                boolTerm = false;
            else {
                boolTerm = true;
                break;
            }
        }
        if (!boolTerm)
            break;
    }
    return boolTerm;
}

GameState &GameState::operator=(const GameState &copyGameState) {
    if (this != &copyGameState) {

        delete (board);

        for (unsigned int i = 0; i < vec1.size(); i++) {
            delete (vec1.at(i));
        }
        vec1.clear();

        for (unsigned int i = 0; i < vec2.size(); i++) {
            delete (vec2.at(i));
        }
        vec2.clear();

        // Initialzing the new game state.
        board = new Board(*copyGameState.board);

        for (unsigned int i = 0; i < copyGameState.vec1.size(); i++) {
            Point *p = new Point(*copyGameState.vec1.at(i));
            vec1.push_back(p);
        }

        for (unsigned int i = 0; i < copyGameState.vec2.size(); i++) {
            Point *p = new Point(*copyGameState.vec2.at(i));
            vec2.push_back(p);
        }

    }

    return *this;
}

Board *GameState::getBoard() const {
    return board;
}
