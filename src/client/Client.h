
// Created by Elad Aharon & Shahar Palmor.
// ID: 311200786
//

#ifndef EX04_CLIENT_H
#define EX04_CLIENT_H

class Client {
public:
    Client(const char *serverIP, int serverPort);
    void connectToServer();
    void sendPoint(int x, int y);
    int getPriority();
    int getClientSocket() const;

    int priority;
private:
    const char *serverIP;
    int serverPort;
    int clientSocket;
};


#endif //EX04_CLIENT_H
