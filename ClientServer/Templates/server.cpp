//-----------------------------------------------------------------------------
// File: server.cpp
// Description: A simple client that connects to a server and repeatedly
//              sends mesasges, receiving responses for each message
//-----------------------------------------------------------------------------

#define BUFFER_SIZE 100

#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>							// for socket(), bind(), ...
#include <netinet/in.h>							// for sockaddr_in struct
#include <arpa/inet.h>							// for htons()
#include <string.h>								// for memset()

int main(int argc, char** argv)
{
	int server_s;								// server's socket ID
	int port;									// port that server runs on
	struct sockaddr_in serverAddr;				// local address
	int ret;									// used to check return values
	const int MAXCONNECTIONS = 5;				// maximum # client connections
	char buffer[BUFFER_SIZE];					// holds msgs to send/recv
	
	// check commandline options
	if (argc != 1+1)
	{
		printf("Usage: %s <port>\n", argv[0]);
		exit(1);
	}
	
	// set port for server to run on
	port = atoi(argv[1]);
	
	// create the socket
	server_s = socket(PF_INET, SOCK_STREAM, 0);
	if (server_s < 0)
	{
		printf("Error in creating socket.\n");
		exit(1);
	}
	
	// construct local address
	memset(&serverAddr, 0, sizeof(serverAddr));
	serverAddr.sin_family		= AF_INET;				// Address Family
	serverAddr.sin_port			= htons(port);			// port to run on
	serverAddr.sin_addr.s_addr	= htons(INADDR_ANY);	// any interface
	
	// bind the server to the local address settings
	ret = bind(server_s, ((struct sockaddr*) &serverAddr), sizeof(serverAddr));
	if (ret != 0)
	{
		printf("Error in binding to socket\n");
		exit(1);
	}
	
	// listen for incoming connections
	ret = listen(server_s, MAXCONNECTIONS);
	if (ret < 0)
	{
		printf("Error while listening for incoming connections\n");
		exit(1);
	}
	
	// handle incoming connections
	printf("SERVER RUNNING:\n");
	printf("  Now accepting incoming connections on port %d\n", port);
	while (1)
	{
		int client_s;								// client socket
		struct sockaddr_in clientAddr;				// client address structure
		unsigned int cal = sizeof(clientAddr);		// client address length
		int bytesRead = 0;							// number of bytes received
		int bytesSent = 0;

		// accept connection from client
		client_s = accept(server_s, (struct sockaddr*)&clientAddr, &cal);
		
		// read in whatever is sent
		bytesRead = recv(client_s, buffer, BUFFER_SIZE, 0);
		if (bytesRead < 0)
		{
			printf("Error while reading\n");
			break;
		}
		buffer[bytesRead] = '\0';
		
		// output received data
		printf("  Received some data: \"%s\"", buffer);

		// acknowledge what was sent
		char responseBuffer[10 + BUFFER_SIZE];	// "Received: " = 10 characters
		sprintf(responseBuffer, "Received: %s\n", buffer);
		bytesSent = send(client_s, responseBuffer, 10+BUFFER_SIZE, 0);
		if (bytesSent < 0)
		{
			printf("Error while sending response\n");
			break;
		}
		printf("  (response sent back to client)\n");

		// close the connection
		shutdown(client_s, 2);				// stop sending/receiving data
	}

	// shutdown the server	
	shutdown(server_s, 2);					// stop sending/receiving data

	return(EXIT_SUCCESS);
}












