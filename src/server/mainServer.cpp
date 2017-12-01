
// Created by Elad Aharon on 28/11/17.
// ID: 311200786
//

#include "Server.h"
#include <iostream>
#include <stdlib.h>

using namespace std;

int main() {
    Server server(4444);
    try {
        server.start();
    } catch (const char *msg) {
        cout << "Cannot start server. Reason: " << msg << endl;
        exit(-1);
    }
}