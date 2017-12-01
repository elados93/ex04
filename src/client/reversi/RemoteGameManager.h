
// Created by Elad Aharon on 01/12/17.
// ID: 311200786
//

#ifndef EX04_REMOTEGAMEMANAGER_H
#define EX04_REMOTEGAMEMANAGER_H


#include "GameManager.h"

class RemoteGameManager : public GameManager {

public:
    RemoteGameManager(GameState &gameState, Player &player1, Player &player2, Printer &printer,
                      GameRules &gameRulesm, int socket1);

private:
    void run();
    void playOneTurn();

    int socket;

};


#endif //EX04_REMOTEGAMEMANAGER_H
