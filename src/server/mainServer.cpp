
// Created by Elad Aharon & Shahar Palmor.
// ID: 311200786

#include "Server.h"
#include <stdlib.h>

using namespace std;

int main() {
    int port;
    port = Server::getPortFromFile("settings.txt");
    Server server(port);
    try {
        server.start();
    } catch (const char *msg) {
        cout << "Cannot start server. Reason: " << msg << endl;
        exit(-1);
    }
}
