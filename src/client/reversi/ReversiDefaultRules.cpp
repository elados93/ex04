
// Created by Elad Aharon & Shahar Palmor.
// ID: 311200786 307929927
//

#include <iostream>
#include "ReversiDefaultRules.h"

ReversiDefaultRules::ReversiDefaultRules() {}
ReversiDefaultRules::~ReversiDefaultRules() {}

possible_outcome ReversiDefaultRules::makeMove(GameState &gameState, Point &p, owner symbol) {

    // Not in the board.
    if (!(*gameState.board).isInBoard(p)) {
        return OUT_OF_BOUND;
    }

    // The cell is occupied.
    if (!(*gameState.board).isCellEmpty(p)) {
        return OCCUPIED_CELL;
    }

    // Not one of the possible options.
    if (!isAlreadyContains(gameState, p, symbol)) {
        return ILLEGAL_MOVE;
    }

    // Check all the possible directions of the point and mark the required cells.
    vector<Point*> possibleMoves = (symbol == PLAYER_1 ? gameState.vec1 : gameState.vec2);
    vector<Point*> flowVec = getPointFromVec(p, possibleMoves)->getDirVector();

    for (unsigned int i = 0; i < flowVec.size(); i++) {
        int dRow = flowVec.at(i)->getX();
        int dCol = flowVec.at(i)->getY();

        Point currentPoint(p);
        Cell currentCell;

        // Mark the cell in the right direction until you first meet the player symbol.
        do {
            (*gameState.board).markCell(currentPoint, symbol);
            currentPoint.setX(currentPoint.getX() + dRow);
            currentPoint.setY(currentPoint.getY() + dCol);
            if ((*gameState.board).isInBoard(currentPoint)) {
                currentCell = (*gameState.board).getCell(currentPoint);
            } else {
                break;
            }
        } while (currentCell.getSymbol() != symbol);
    }

    return SUCCESS;
}

vector<Point *> * ReversiDefaultRules::getPossibleMoves(GameState &gameState, owner symbol) {
    return symbol == PLAYER_1 ? (&gameState.vec1) : (&gameState.vec2);
}

void ReversiDefaultRules :: makePossibleMoves(GameState &gameState, owner symbol) {

    // Free all the previous allocations of the possible points.
    freePointsInVec(gameState, symbol);

    int row = (*gameState.board).getRow();
    int col = (*gameState.board).getCol();

    for(int i = 0;i < row;i++) {
        for(int j = 0;j < col;j++) {
            Point p(i, j);
            owner currentSymbol = (*gameState.board).getCell(p).getSymbol();
            if (currentSymbol == symbol)  // Check only the relevant cells.
                checkSurround(gameState, p, symbol);
        }
    }
}

void ReversiDefaultRules :: checkSurround(GameState &gameState, Point &p, owner symbol) {
    int r = p.getX();
    int c = p.getY();
    int dRow = -1;
    int dCol;

    for (int i = 0; i < 3; i++) {
        dCol = -1;
        for (int j = 0; j < 3; j++) {

            // Make sure not to check the current cell again.
            if (dRow == 0 && dCol == 0) {
                dCol++;
                continue;
            }

            Point currentPoint(r + dRow, c + dCol);
            if ((*gameState.board).isInBoard(currentPoint)) {
            
                Cell currentCell = (*gameState.board).getCell(currentPoint);
                owner otherSymbol = currentCell.getSymbol();

                // Check if the near cell belongs to the other player.
                if (isLegal(gameState, currentPoint) && otherSymbol != symbol && currentCell.isCellActive()) 
                    moveAlong(gameState, currentPoint, otherSymbol, dRow, dCol);
            }
            dCol++;
        }
        dRow++;
    }
}

void ReversiDefaultRules :: moveAlong(GameState &gameState, Point &p ,owner symbol, int dRow, int dCol) {
    Cell currentCell = (*gameState.board).getCell(p);
    owner currentSymbol = (symbol == PLAYER_1 ? PLAYER_2 : PLAYER_1);

    while(isLegal(gameState, p) && currentCell.getSymbol() == symbol) {

        // Advance the current point.
        p.setX(p.getX() + dRow);
        p.setY(p.getY() + dCol);
        if ((*gameState.board).isInBoard(p)) {
            // Advance the current cell.
            currentCell = (*gameState.board).getCell(p);
        } else {
            break;
        }
    }

    // Check if the cell isn't active.
    if (!currentCell.isCellActive()) {

        // Check if the potential point isn't already in the vector.
        bool check = this->isAlreadyContains(gameState, p, currentSymbol);
        Point *flowPoint = new Point(dRow * -1, dCol * -1);
        if (!check) {
            Point *wantedPoint = new Point(p);
            wantedPoint->insertFlowPoint(flowPoint);

            if (symbol == PLAYER_1) {
                gameState.vec2.push_back(wantedPoint);
            }

            if (symbol == PLAYER_2) {
                gameState.vec1.push_back(wantedPoint);
            }
        } else {
            vector <Point *> *currentPlayerVector = getPossibleMoves(gameState, currentSymbol);
            // Although the points is in the vector, it might have another direction to move along.
            Point *pointToAddFlow = getPointFromVec(p, *currentPlayerVector);
            pointToAddFlow->insertFlowPoint(flowPoint);
        }
    }
}

void ReversiDefaultRules :: freePointsInVec(GameState &gameState, owner symbol) {
    if (symbol == PLAYER_1) {
        for (unsigned int i = 0; i < gameState.vec1.size(); i++) {
            delete(gameState.vec1.at(i));
        }
        gameState.vec1.clear();
    }

    if (symbol == PLAYER_2) {
        for (unsigned int i = 0; i < gameState.vec2.size(); i++) {
            delete(gameState.vec2.at(i));
        }
        gameState.vec2.clear();
    }

}

bool ReversiDefaultRules:: isLegal(GameState &gameState, Point &p) const{
    return (*gameState.board).isInBoard(p);
}

Point* ReversiDefaultRules :: getPointFromVec(Point &point, vector<Point*> vec) const {
    for (unsigned int i = 0; i < vec.size(); ++i) {
        if (vec.at(i)->isEqual(point)) {
            return vec.at(i);
        }
    }
    return NULL; // If the point isn't in the vector return null.
}

bool ReversiDefaultRules :: isAlreadyContains(GameState &gameState, Point &p, owner symbol) {

    if (symbol == PLAYER_1) {
        for (unsigned int i = 0; i < gameState.vec1.size(); i++) {

            // Check if the point already exists.
            if (p.isEqual(*(gameState.vec1.at(i)))) {
                return true;
            }
        }
    } else {
        if (symbol == PLAYER_2) {
            for (unsigned int i = 0; i < gameState.vec2.size(); i++) {

                // Check if the point already exists.
                if (p.isEqual(*(gameState.vec2.at(i)))) {
                    return true;
                }
            }
        }
    }

    return false;
}
