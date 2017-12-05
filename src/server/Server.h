
// Created by Elad Aharon & Shahar Palmor.
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
    int handleClient(int clientSocketSrc, int clientSocketDsc, int srcPriority);

    void giveClientPriority(int socket1, int socket2);
};


#endif //EX04_SERVER_H
