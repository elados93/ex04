
// Created by Elad Aharon on 28/11/17.
// ID: 311200786
//

#ifndef EX04_SERVER_H
#define EX04_SERVER_H


class Server {
public:
    Server(int port);
    void start();
    void stop();
private:
    int port;
    int serverSocket; // the socket's file descriptor
    void handleClient(int clientSocket);

    void giveClientPriority(int socket1, int socket2);
};


#endif //EX04_SERVER_H
