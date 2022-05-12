/** @brief Class Client to connect to server by address and port.
*/
#include<iostream>
#include "Client.h"

/**
 * @brief Constructor to setup client.
 * Initialization with
 * - IP: 127.0.0.1
 * - Port: 8080
 */
Client::Client(){
  this->sock = {0};
  this->serv_addr.sin_family = AF_INET;
  this->setDstIP("127.0.0.1");
  this->setDstPort(8080);
  std::cout << "Client initialized." << std::endl;
}

/**
 * @brief Create new socket. Returns value depending on success.
 * - Value  1: Success
 * - Value -1: Error
 * @return int
 */
int Client::newSocket(){
  if ((this->sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
    std::cout << "\n Socket creation error \n" << std::endl;
    return -1;
  }
  return 1;
}

/**
 * @brief Set server port to listen on
 * port got stored in network byte order
 * @param port
 */
void Client::setDstPort(size_t port) { 
  this->serv_addr.sin_port = htons(port);
}

/**
 * @brief Set destination IP to connect to.
 * IP got stored in network byte order
 * @param ip
 */
void Client::setDstIP(const char* ip){
  this->ipTextToBinary(ip, this->serv_addr);
}

/**
 * @brief Convert IP text address into binary.
 * Works directly on sockaddr_in attribute of Client class.
 * Returns value depending on success.
 * - Value  1: Success
 * - Value -1: Error
 * @param ip
 * @param addr
 * @return int
 */
int Client::ipTextToBinary(const char* ip, sockaddr_in& addr) {
  if (inet_pton(AF_INET, ip, &addr.sin_addr) <= 0) {
    std::cout << "\nInvalid address/ Address not supported" << std::endl;
    return -1;
  }
  return 1;
}

/**
 * @brief Public method to establish connection to server.
 * Without setting IP and port.
 */
void Client::connectServer(){
  this->establishConnection();
}

/**
 * @brief Public method to establish connection to server.
 * @param serverIP
 * @param port
 */
void Client::connectServer(const char* serverIP, size_t port) {
  this->setDstIP(serverIP);
  this->setDstPort(port);
  this->establishConnection();
}

/**
 * @brief Private method to establish connection to server.
 * Includes creation of socket.
 *
 * Returns value depending on success.
 * - Value  1: Success
 * - Value -1: Error
 * @param serverIP
 * @param port
 */
int Client::establishConnection() {
  this->newSocket();
  if (connect(this->sock, (struct sockaddr*) &this->serv_addr,
              sizeof(this->serv_addr)) < 0) {
    std::cout << "\nConnection Failed" << std::endl;
    return -1;
  }
  return 1;
}

/**
 * @brief Send given message to server.
 *
 * Returns value depending on success.
 * - Value  1: Success
 * - Value -1: Error
 * @param message
 * @return int
 */
int Client::sendMessage(const char* message) {
  if ( !this->sock ){
    std::cout << "No socket available." << std::endl;
    return -1;
  }
  send(this->sock, message, strlen(message), 0);
  std::cout << "Message sent." << std::endl;
  return 1;
}
