// Client side C/C++ program to demonstrate Socket
// programming
// adapted from https://www.geeksforgeeks.org/socket-programming-cc/ to C++
#include <arpa/inet.h>
#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <unistd.h>
#define PORT 8080

int main(int argc, char const* argv[])
{

	std::cout << "Starting Client to connect to localhost server." << std::endl;

	int sock = 0, valread;
	struct sockaddr_in serv_addr;
	const char* hello = "Hello from client";
	char buffer[1024] = { 0 };

	// Create new socket
	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		std::cout << "\n Socket creation error \n" << std::endl;
		return -1;
	}

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(PORT);

	// Convert IPv4 and IPv6 addresses from text to binary
	// formf
	if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
		std::cout <<
			"\nInvalid address/ Address not supported" << std::endl;
		return -1;
	}

	// Establish connection to server
	if (connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
		std::cout << "\nConnection Failed" << std::endl;
		return -1;
	}

	send(sock, hello, strlen(hello), 0);
	std::cout << "Hello message sent" << std::endl;
	valread = read(sock, buffer, 1024);
	std::cout <<  buffer << std::endl;
	return 0;
}
