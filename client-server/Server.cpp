// Server side C/C++ program to demonstrate Socket
// programming
// adapted from https://www.geeksforgeeks.org/socket-programming-cc/ to C++
#include <netinet/in.h>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <sys/socket.h>
#include <unistd.h>
#define PORT 8080

int main(int argc, char const* argv[])
{

	std::cout << "Server listening on localhost at port " << PORT << std::endl;

	int server_fd, new_socket, valread;
	struct sockaddr_in address;
	int opt = 1;
	int addrlen = sizeof(address);
	char buffer[1024] = { 0 };
	const char* hello = "Hello from server";

	// Creating socket file descriptor
	if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
		std::cerr << "socket failed" << std::endl;
		exit(EXIT_FAILURE);
	}

	// Forcefully attaching socket to the port 8080
	if (setsockopt(server_fd, SOL_SOCKET,	SO_REUSEADDR | SO_REUSEPORT, 
				&opt, sizeof(opt))) {
		std::cerr << "setsockopt" << std::endl;
		exit(EXIT_FAILURE);
	}
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(PORT);

	// Forcefully attaching socket to the port 8080
	if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
		std::cerr << "bind failed" << std::endl;
		exit(EXIT_FAILURE);
	}
	
	// Listening for connections
	if (listen(server_fd, 3) < 0) {
		std::cerr << "listen" << std::endl;
		exit(EXIT_FAILURE);
	}
	
	// Establish connection
	if ((new_socket = accept(server_fd, 
				(struct sockaddr*)&address, (socklen_t*)&addrlen)) < 0) {
		std::cerr << "accept" << std::endl;
		exit(EXIT_FAILURE);
	}

	read(new_socket, buffer, 1024);
	std::cout << buffer << std::endl;
	send(new_socket, hello, strlen(hello), 0);
	std::cout << "Response message sent"<< std::endl;
	return 0;
}
