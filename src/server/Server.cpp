
// Created by Elad Aharon on 28/11/17.
// ID: 311200786

#include "Server.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <iostream>
#include <stdio.h>

#define MAX_CONNECTED_CLIENTS 10

using namespace std;

Server::Server(int port): port(port), serverSocket(0) {
    cout << "Server" << endl;
}
void Server::start() {
    // Create a socket point
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1) {
        throw "Error opening socket";
    }

    // Assign a local address to the socket
    struct sockaddr_in serverAddress;
    bzero((void *)&serverAddress,
          sizeof(serverAddress));
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(port);
    if (bind(serverSocket, (struct sockaddr
    *)&serverAddress, sizeof(serverAddress)) == -1) {
        throw "Error on binding";
    }
    // Start listening to incoming connections
    listen(serverSocket, MAX_CONNECTED_CLIENTS);
    // Define the client socket's structures
    struct sockaddr_in clientAddress;
    socklen_t clientAddressLen;
    while (true) {
        cout << "Waiting for #1 client connections..." << endl;
        // Accept a new client connection
        int clientSocket1 = accept(serverSocket, (struct
                sockaddr *)&clientAddress, &clientAddressLen);
        cout << "Client #1 connected" << endl;
        if (clientSocket1 == -1)
            throw "Error on accept client #1";

        cout << "Waiting for #2 client connections..." << endl;
        // Accept a new client connection
        int clientSocket2 = accept(serverSocket, (struct
                sockaddr *)&clientAddress, &clientAddressLen);
        cout << "Client #2 connected" << endl;
        if (clientSocket2 == -1)
            throw "Error on accept client #2";

        giveClientPriority(clientSocket1, clientSocket2); // inform the client's priority

        while (true) { // Play the game with 2 players
            // get from player1 to player2 Ping Pong.

            char *move;
            int n = read(clientSocket1, &move, sizeof(move));
            if (n == -1)
                throw "Error getting message for client #1";
            if(strcmp(move,"END") == 0){
                // Close communication with the client
                close(clientSocket1);
                close(clientSocket2);
            }
            break;
        }



    } // end of listening to clients

}


// Handle requests from a specific client
void Server::handleClient(int clientSocket) {
    int arg1, arg2;
    char op;
    while (true) {
        // Read new exercise arguments
        int n = read(clientSocket, &arg1, sizeof(arg1));
        if (n == -1) {
            cout << "Error reading arg1" << endl;
            return;
        }
        if (n == 0) {
            cout << "Client disconnected" << endl;
            return;
        }
        n = read(clientSocket, &op, sizeof(op));
        if (n == -1) {
            cout << "Error reading operator" << endl;
            return;
        }

        n = read(clientSocket, &arg2, sizeof(arg2));
        if (n == -1) {
            cout << "Error reading arg2" << endl;
            return;
        }
        cout << "Got exercise: " << arg1 << op << arg2 <<
             endl;
        int result = 25;
        // Write the result back to the client
        n = write(clientSocket, &result, sizeof(result));
        if (n == -1) {
            cout << "Error writing to socket" << endl;
            return;
        }
    }
}

void Server::stop() {
    close(serverSocket);
}

void Server::giveClientPriority(int socket1, int socket2) {
    // Write the priority of the #1 client
    int priority1 = 1;
    int n1 = write(socket1, &priority1, sizeof(priority1));
    if (n1 == -1) {
        cout << "Error writing to #1 socket" << endl;
        return;
    }

    // Write the priority of the #2 client
    int priority2 = 2;
    int n2 = write(socket2, &priority2, sizeof(priority2));
    if (n2 == -1) {
        cout << "Error writing to #2 socket" << endl;
        return;
    }
}
