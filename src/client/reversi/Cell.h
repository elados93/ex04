// Created by Elad Aharon & Shahar Palmor.
// ID: 311200786 307929927

#ifndef EX02_CELL_H
#define EX02_CELL_H

#include "GenralDef.h"

class Cell {
public:
    Cell(); // Constructor
    Cell(const Cell &cell); // Destructor

    bool isCellActive() const;
    owner getSymbol() const;
    void setSymbol(owner s);

private:
    owner symbol; // The player owns the cell, if there is one.
    bool isActive; // True or false if the cell is active.
};


#endif //EX02_CELL_H
