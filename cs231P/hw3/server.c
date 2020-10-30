#include <unistd.h> 
#include <stdio.h>
#include <netinet/in.h>
 
int main(int argc, char const *argv[]) 
{ 
	int socket_file_descriptor, incomming_socket; 
	char buffer[1024] = { 0 };
	
	// setup address
	struct sockaddr_in address;
	address.sin_family = AF_INET; 
	address.sin_addr.s_addr = INADDR_ANY; 
	address.sin_port = htons(8080); 
	int address_length = sizeof(address);
	
	// creation socket file descriptor.
	if ((socket_file_descriptor = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
		printf("failed to setup setup socket");
		return -1;
	}
	
	// bind the socket to address and port
	if (bind(socket_file_descriptor, (struct sockaddr *)&address, sizeof(address)) < 0 ) {
		printf("failed to bind the address"); 
		return -1;
	}

	// start listening to incomming connections requests
	if (listen(socket_file_descriptor, 3) < 0) {
		printf("failed to start listening to incomming connections");
		return -1;
	}

	// create incomming socket connection's file descriptor by accepting incomming connection request.
	if ((incomming_socket = accept(socket_file_descriptor, (struct sockaddr *)&address, (socklen_t*)&address_length)) < 0 ) { 
		printf("failed to accept incomming socket connections");
		return -1;
	}

	// read incomming message
	read(incomming_socket, buffer, 1024); 	
	printf("successfully received message: %s \n", buffer); 

	return 0;
} 
