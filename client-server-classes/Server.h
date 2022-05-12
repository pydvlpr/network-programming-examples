/** @brief Class Server to listening on given port
 */
#ifndef SERVER_H
#define SERVER_H

#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <cstdlib>
#include <cstring>
#include <iostream>

/**
 * @brief Server listening on given port.
 * To be prepared fist bevor listening.
 * Preperation steps in specifc private methods.
 */
class Server{
  public:
    Server();
    ~Server() = default;
    void prepare(int port);
    void startListening(bool infinite);

   private:
    int server_fd;
    int new_socket;
    struct sockaddr_in svr_addr;
    int opt;
    int addrlen;
    char buffer[4096];
    int msgCnt;    
    void newSocket();
    void setSrvSocketOpt();
    void setPort(int port);
    void bindSrvSocket();
    void listening();
    void acceptConnection();
    void readBuffer();
    void printStatus();
};

#endif