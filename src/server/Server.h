
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
    /**
     * handing a client request, the client is sending a move and the server give the other client the information.
     * @param clientSocketSrc is the client that wants to transfer the info.
     * @param clientSocketDsc is the client reciving the info.
     * @param srcPriority is the priority of the giving info client.
     * @return 1 if the info was transfered correctly. 0 is the game is over.
     */
    int handleClient(int clientSocketSrc, int clientSocketDsc, int srcPriority);

    /**
     * giving each client his priority from the server.
     * @param socket1 is the socket for the first player.
     * @param socket2 is the socket for the second player.
     */
    void giveClientPriority(int socket1, int socket2);
};


#endif //EX04_SERVER_H
