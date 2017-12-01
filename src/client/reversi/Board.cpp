// Created by Elad Aharon & Shahar Palmor on 28/10/17.
// ID: 311200786 307929927

#include "Board.h"

Board::Board(int row, int col) {
    this->row = row;
    this->col = col;

    // Allocate pointers for the board.
    this->matrix = new Cell *[row];
    for (int i = 0; i < row; i++) {
        this->matrix[i] = new Cell[col];
    }

    initBoard(); // Initialize the board
}

Board::Board(const Board &board) {
    this->row = board.row;
    this->col = board.col;

    this->matrix = new Cell *[row];
    for (int i = 0; i < row; i++) {
        this->matrix[i] = new Cell[col];
    }

    // Copy each cell from the parameter.
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            Point p(i, j);
            this->matrix[i][j] = Cell(board.getCell(p));
        }
    }

}

void Board::initBoard() {
    // Initialize all the board with no owners.
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            this->matrix[i][j].setSymbol(NONE);
        }
    }

    // Set the center of the board with the 2 players.
    this->matrix[(row / 2) - 1][(col / 2) - 1].setSymbol(PLAYER_2);
    this->matrix[(row / 2) - 1][(col / 2)].setSymbol(PLAYER_1);
    this->matrix[(row / 2)][(col / 2)].setSymbol(PLAYER_2);
    this->matrix[(row / 2)][(col / 2) - 1].setSymbol(PLAYER_1);

}

bool Board::isCellEmpty(Point &p) const {
    return !this->matrix[p.getX()][p.getY()].isCellActive();
}

bool Board::isBoardFull() const {
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            if (!this->matrix[i][j].isCellActive()) {
                return false;
            }
        }
    }
    return true;
}

bool Board::isInBoard(Point &p) const {

    return ((this->row > p.getX() && p.getX() >= 0) && (this->col > p.getY() && p.getY() >= 0));
}

void Board::markCell(Point &p, owner symbol) {
    this->matrix[p.getX()][p.getY()].setSymbol(symbol);
}

int Board::getRow() const {
    return row;
}

int Board::getCol() const {
    return col;
}

Cell Board::getCell(Point &p) const {
    return this->matrix[p.getX()][p.getY()];
}

Board::~Board() {

    for (int i = 0; i < row; i++) {
        delete (this->matrix[i]);
    }

    delete this->matrix;
}

Board &Board::operator=(const Board &board1) {
    if (&board1 != this) {

        for (int i = 0; i < row; i++) {
            delete (this->matrix[i]);
        }
        delete this->matrix;

        row = board1.row;
        col = board1.col;

        // Allocate pointers for the board.
        this->matrix = new Cell *[row];
        for (int i = 0; i < row; i++) {
            this->matrix[i] = new Cell[col];
        }

        // Copy each cell from the parameter.
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {
                Point p(i, j);
                this->matrix[i][j] = Cell(board1.getCell(p));
            }
        }
    }
    return *this;
}

/**
 *
 * @return  Point that represents the number of cells occupied with the x player and the o player
 * in order to know the substruction between the two.
 */
Point Board::countOwner() {
    int counterX = 0;
    int counterO = 0;

    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            if (matrix[i][j].getSymbol() == PLAYER_1) {
                counterX++;
            } else if (matrix[i][j].getSymbol() == PLAYER_2) {
                counterO++;
            }
        }
    }
    return Point(counterX, counterO);

}


