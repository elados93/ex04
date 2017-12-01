
// Created by Elad Aharon on 28/11/17.
// ID: 311200786
//

#include "Client.h"
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>

using namespace std;

Client::Client(const char *serverIP, int serverPort):
        serverIP(serverIP), serverPort(serverPort),
        clientSocket(0) {
    cout << "Client" << endl;
}
void Client::connectToServer() {
    // Create a socket point
    clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == -1) {
        throw "Error opening socket";
    }
    // Get a hostent structure for the given host address
    struct hostent *server;

    struct in_addr address;
    inet_pton(AF_INET, "127.0.0.1", &address);

    server = gethostbyaddr((const void *)&address, sizeof address, AF_INET);

    if (server == NULL) {
        throw "Host is unreachable";
    }
    // Create a structure for the server address
    struct sockaddr_in serverAddress;
    bzero((char *)&serverAddress, sizeof(serverAddress));
    serverAddress.sin_family = AF_INET;
    memcpy((char *)&serverAddress.sin_addr.s_addr, (char *)server->h_addr, server->h_length);
    // htons converts values between host and network byte orders
    serverAddress.sin_port = htons(serverPort);
    // Establish a connection with the TCP server
    if (connect(clientSocket, (struct sockaddr
    *)&serverAddress, sizeof(serverAddress)) == -1) {
        throw "Error connecting to server";
    }
    cout << "Connected to server" << endl << "Waiting for the other players..." << endl;
}



int Client::sendPoint(int arg1, char op, int arg2) {
    // Write the exercise arguments to the socket
    int n = write(clientSocket, &arg1, sizeof(arg1));
    if (n == -1)
        throw "Error writing arg1 to socket";

    n = write(clientSocket, &op, sizeof(op));
    if (n == -1) {
        throw "Error writing op to socket";
    }
    n = write(clientSocket, &arg2, sizeof(arg2));

    if (n == -1)
        throw "Error writing arg2 to socket";

    // Read the result from the server
    int result;
    n = read(clientSocket, &result, sizeof(result));
    if (n == -1)
        throw "Error reading result from socket";

    return result;
}

void Client::stop() {
    close(clientSocket);
}

int Client::getPriority() {
    int result;
    int n = read(clientSocket, &result, sizeof(result));
    if (n == -1)
        throw "Error reading priority from server";

    priority = result;
    return priority;
}







