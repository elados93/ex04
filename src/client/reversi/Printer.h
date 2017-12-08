
// Created by Elad Aharon & Shahar Palmor.
// ID: 311200786 307929927
//

#ifndef EX02_PRINTER_H
#define EX02_PRINTER_H

#include "Board.h"
#include "Player.h"


class Printer {

public:
    virtual ~Printer() {};

    virtual void printBoard() = 0;
    virtual void printNextPlayerMove(Player &p, vector<Point*> v) = 0;
    virtual void printLastMove(Player &player, Point *point) = 0;
    virtual void printEndOfGame(Player &p, status status1) = 0;
    virtual void printError(possible_outcome outcome) = 0;
    virtual void printMenu() = 0;
    virtual void printInformingGameStarted(owner currentOwner) = 0;
    virtual void printWaitingForOtherPlayer(owner currentOwner) = 0;

};



#endif //EX02_PRINTER_H
