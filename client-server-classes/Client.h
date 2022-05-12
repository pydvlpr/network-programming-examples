/** @brief Class Client to connect to server by address and port.
*/
#ifndef _CLIENT_H
#define _CLIENT_H

#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#include <cstring>
#include <iostream>
#include<cstddef>

/**
 * @brief Client to connect to server by IP and port and send messages.
 *
 * IP and Port can be changed for every connection.
 */
class Client {
  public:
    Client();
    ~Client() = default;
    void connectServer();
    void connectServer(const char* serverIP, size_t port);
    int sendMessage(const char* message);
    void setDstPort(size_t port);
    void setDstIP(const char* ip);

  private:
    struct sockaddr_in serv_addr;
    int sock;
    int ipTextToBinary(const char* ip, sockaddr_in& ipaddr);
    int newSocket();
    int establishConnection();
};

#endif