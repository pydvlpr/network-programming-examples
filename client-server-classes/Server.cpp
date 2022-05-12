/** @brief Class Server to listening on given port
 */
#include "Server.h"

/**
 * @brief Constructor doing basic configuration
 */
Server::Server(){
  this->msgCnt = {0};
  this->opt = 1;
  this->buffer[4096] = {0};
  this->svr_addr.sin_family = AF_INET;
  this->svr_addr.sin_addr.s_addr = INADDR_ANY;
  this->svr_addr.sin_port = 0;
  std::cout << "Server initialized" << std::endl;
}

/**
 * @brief Preperating the socket
 * using private methods
 * - newSocket()
 * - setSrvSocketOpt()
 * - setPort()
 * - bindSrvSocket()
 */
void Server::prepare(int port) {
  this->newSocket();
  this->setSrvSocketOpt();
  this->setPort(port);
  this->bindSrvSocket();
}
/**
 *  @brief Create a new socket
 */
void Server::newSocket() {
  if ((this->server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
    std::cerr << "socket failed" << std::endl;
    exit(EXIT_FAILURE);
  }
}

/**
 *  @brief Setting some socket options
 *  - SOL_SOCKET: Make setting options on socket level possible
 *  - SO_REUSEADDR: allow reuse of local addresses, if supported by protocol
 *  - SO_REUSEPORT: Allow multiple sockets listening on same port
 */
void Server::setSrvSocketOpt(){
  if (setsockopt(this->server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
                 &this->opt, sizeof(this->opt))) {
    std::cerr << "setsockopt failed" << std::endl;
    exit(EXIT_FAILURE);
  }
}

/**
 * @brief Set server port to listen on
 * port got stored in network byte order
 * @param port
 */
void Server::setPort(int port) { 
  this->svr_addr.sin_port = htons(port);
  }

/**
 * @brief Bind socket to file handler
 */
void Server::bindSrvSocket() {
  if (bind(this->server_fd, (struct sockaddr*)&this->svr_addr,
           sizeof(this->svr_addr)) < 0) {
    std::cerr << "bind failed" << std::endl;
    exit(EXIT_FAILURE);
  }
}

/**
 * @brief Take steps for Server to listen on given port.
 * Parameter controls inifinte listeing.
 * @param infinite
 */
void Server::startListening(bool infinite) {
  do {
    std::cout << std::boolalpha << "Infinite running: " << infinite << std::endl;
    
    if (this->svr_addr.sin_port == 0) {
      std::cerr << "No port set." << std::endl;
      exit(EXIT_FAILURE);
    }
    this->listening();
    this->acceptConnection();
    this->readBuffer();
    this->msgCnt++;
    this->printStatus();
  } while (infinite);
}

/**
 * @brief Listen on port.
 */
void Server::listening(){
  if (listen(this->server_fd, 3) < 0) {
    std::cerr << "listen failed" << std::endl;
    exit(EXIT_FAILURE);
  }
}

/**
 * @brief Accept incomming connection.
 */
void Server::acceptConnection(){
  if ((this->new_socket = accept(server_fd, (struct sockaddr*)&this->svr_addr,
                                 (socklen_t*)&this->addrlen)) < 0) {
    std::cerr << "accept failed" << std::endl;
    exit(EXIT_FAILURE);
  }
}

/**
 * @brief Read and print incomming data.
 */
void Server::readBuffer() { 
  read(this->new_socket, this->buffer, 4096); 
  std::cout << this->buffer << std::endl;
}

/**
 * @brief Print status about received messages.
 */
void Server::printStatus(){
  std::cout << "Messages received: " << this->msgCnt << std::endl;
}

