
// Created by Elad Aharon on 28/11/17.
// ID: 311200786
//

#ifndef EX04_CLIENT_H
#define EX04_CLIENT_H

class Client {
public:
    Client(const char *serverIP, int serverPort);
    void connectToServer();
    int sendPoint(int arg1, char op, int arg2);
    int getPriority();
    void stop();

private:
    const char *serverIP;
    int serverPort;
    int clientSocket;
    int priority;
};


#endif //EX04_CLIENT_H
