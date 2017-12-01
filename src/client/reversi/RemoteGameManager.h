
// Created by Elad Aharon on 01/12/17.
// ID: 311200786
//

#ifndef EX04_REMOTEGAMEMANAGER_H
#define EX04_REMOTEGAMEMANAGER_H


#include "GameManager.h"
#include "../Client.h"

class RemoteGameManager : public GameManager {

public:
    RemoteGameManager(GameState &gameState, Player &player1, Player &player2, Printer &printer,
                      GameRules &gameRules, Client client1);

    void setCurrentPlayer(int playerNumber);
    void run();

private:
    void playOneTurn();
    Client clientDetails;
    int translatePointFromServer();

};


#endif //EX04_REMOTEGAMEMANAGER_H
