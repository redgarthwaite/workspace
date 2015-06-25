//-----------------------------------------------------------------------------
// File: client.cpp
// Description: A simple client that connects to a server and repeatedly
//              sends mesasges, receiving responses for each message
//-----------------------------------------------------------------------------

#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>						// for socket(), connect(), ...
#include <netinet/in.h>						// for sockaddr_in struct
#include <arpa/inet.h>						// for inet_addr(), htons()
#include <string.h>							// for memset()

#define BUFFER_SIZE 100

int main(int argc, char** argv)
{
	int server_s;						// socket ID
	char* serverIP;						// IP address of server
	int serverPort;						// port number of server
	char* msgBuffer;					// buffer to put messages to send in
	int msgBufferLen;					// length of the msgBuffer
	struct sockaddr_in serverAddr;	// struct to hold server's address/port
	int bytesSent = 0;
	int bytesReceived = 0;
	char buffer[BUFFER_SIZE];
	int ret;
	
	// check commandline arguments
	if (argc != 2+1)
	{
		printf("Usage: %s <server IP> <server port>\n", argv[0]);
		exit(0);
	}
	
	// grab the server's address and port
	serverIP = argv[1];
	serverPort = atoi(argv[2]);
	
	// create the socket
	server_s = socket(PF_INET, SOCK_STREAM, 0);
	
	// configure the server's address in a special structure
	memset(&serverAddr, 0, sizeof(serverAddr));
	serverAddr.sin_family		= AF_INET;				// Family: Internet
	serverAddr.sin_port			= htons(serverPort);	// server's port #
	serverAddr.sin_addr.s_addr	= inet_addr(serverIP);	// server ID #

	// connect to the server
	ret = connect(server_s, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
	if (ret < 0)
	{
		printf("Error while trying to connect to server\n");
		exit(1);
	}

	// get text from user to send to the server
	printf("Input some text to send to the server:\n>>");
	fgets(buffer, BUFFER_SIZE, stdin);

	// send data to the server
	//sprintf(buffer, "DATA");
	bytesSent = send(server_s, buffer, BUFFER_SIZE, 0);
	if (bytesSent < 0)
	{
		printf("Error while sending data\n");
		exit(0);
	}
	
	// receive response from server
	bytesReceived = recv(server_s, buffer, BUFFER_SIZE, 0);
	if (bytesReceived < 0)
	{
		printf("Error while receiving data\n");
		exit(1);
	}
	buffer[bytesReceived] = '\0';
	
	// print response
	printf("GOT THIS FROM THE SERVER:\n");
	printf("  \"%s\"", buffer);
	
	// close connection
	shutdown(server_s, 2);						// stop sending/receiving data

	printf("\n~FIN\n");
	return(0);
}
