
// Created by Elad Aharon & Shahar Palmor.
// ID: 311200786
//

#include "Server.h"
#include <iostream>
#include <stdlib.h>
#include <fstream>

int getPortFromFile();

using namespace std;

int main() {
    int port = getPortFromFile();
    Server server(port);
    try {
        server.start();
    } catch (const char *msg) {
        cout << "Cannot start server. Reason: " << msg << endl;
        exit(-1);
    }
}

/**
 * get the port of the connection with the server from the file.
 * @return the port.
 */
int getPortFromFile() {
    ifstream inFile;
    inFile.open("../settings.txt");
    if (!inFile)
        throw "Error opening the settings file!";
    else {
        int port;
        string dummy;

        inFile >> dummy;
        inFile >> dummy;
        inFile >> dummy;
        inFile >> dummy;
        inFile >> dummy;

        inFile >> port;

        inFile.close();
        return port;
    }
}