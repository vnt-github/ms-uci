// Client side C/C++ program to demonstrate Socket programming 
#include <stdio.h>
#include <arpa/inet.h>
#include <string.h>

int main(int argc, char const *argv[]) 
{ 
	int socket_file_descriptor = 0;
	const char *message = "Hello from the other side";

	// setup address
	struct sockaddr_in address;
	address.sin_family = AF_INET; 
	address.sin_port = htons(8080); 

	// creation socket file descriptor.
	if ((socket_file_descriptor = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		printf("failed to setup setup socket");
		return -1;
	}
	
	// IPv4 addresse to binary conversion
	if(inet_pton(AF_INET, "127.0.0.1", &address.sin_addr) <= 0 ) {
		printf("invalid address, error converting to binary"); 
		return -1;
	}

	// setup connections to send message to the socket specied by socket file descriptor.
	if (connect(socket_file_descriptor, (struct sockaddr *)&address, sizeof(address)) < 0) {
		printf("failed to setup connection"); 
		return -1;
	}

	// send message
	send(socket_file_descriptor, message, strlen(message) , 0); 
	printf("message sent succesfully\n");

	return 0; 
} 
