
// Created by Elad Aharon & Shahar Palmor
// ID: 311200786 307929927
//

#ifndef EX04_REMOTEGAMEMANAGER_H
#define EX04_REMOTEGAMEMANAGER_H


#include "GameManager.h"
#include "../Client.h"

class RemoteGameManager : public GameManager {

public:
    RemoteGameManager(GameState &gameState, Player &player1, Player &player2, Printer &printer,
                      GameRules &gameRules, Client &client1);

    /**
     * giving the current player his priority according to his client socket.
     * @param playerNumber is the priority.
     */
    void setCurrentPlayer(int playerNumber);

    /**
     * run each game of each client.
     */
    void run();

    /**
 * get the port of the connection with the server from the file.
 * @return the port.
 *//*
    static Client *getClientFromFile(string fileName);*/

private:
    /**
     * play a single turn of one client. notice that we will do two turns, one for each client.
     */
    void playOneTurn();

    Client clientDetails;

    /**
     * this function reads 2 integers from the server and translate it to a real move on the board.
     * playOneTurn func will execute the move.
     * Point lastMove - is getting update by the move of the other player.
     * @return 1 if reading a point was a success, or -1 in case the other client had no moves.
     */
    int translatePointFromServer();

};


#endif //EX04_REMOTEGAMEMANAGER_H
