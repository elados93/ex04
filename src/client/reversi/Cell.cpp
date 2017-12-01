// Created by Elad Aharon & Shahar Palmor on 28/10/17.
// ID: 311200786 307929927

#include "Cell.h"

Cell ::Cell() {
    this->isActive = false;
    this->symbol = NONE;
}

bool Cell::isCellActive() const {
    return this->isActive;
}

void Cell::setSymbol(owner s) {
    if (s != NONE) {
        this->isActive = true;
    }
    this->symbol = s;
}

owner Cell::getSymbol() const {
    return this->symbol;
}

Cell::Cell(const Cell &cell) {
    this->symbol = cell.symbol;
    this->isActive = cell.isActive;
}


