//-----------------------------------------------------------------------------
// File: client2.cpp
// Description: Interacts with server2.cpp by connecting to the server and
//              repeatedly sending user-entered strings back and forth until
//				the client types "GOODBYE"
//-----------------------------------------------------------------------------

#include <stdlib.h>							// for exit()
#include <stdio.h>							// for standard I/O
#include <string.h>							// for memset()
#include <sys/socket.h>						// for socket(), connect(), ...
#include <netinet/in.h>						// for sockaddr_in struct
#include <arpa/inet.h>						// for inet_addr(), htons()

// macro definitions
#define BUFFER_SIZE 100

// function prototypes
void ohnoes(const char* msg);

//-----------------------------------------------------------------------------
// Function: main()
// Program starts here
//-----------------------------------------------------------------------------
int main(int argc, char** argv)
{
	int server_s;									// socket to server
	char* serverIP;									// IP address of server
	int port;										// server's operating port
	struct sockaddr_in serverAddr;					// server's address
	char buffer[BUFFER_SIZE];
	int bytesSent = 0;
	int bytesReceived = 0;

	// check commandline input
	if (argc != 1+2)
	{
		printf("Usage: %s <server IP> <server port>\n", argv[0]);
		exit(0);
	}
	
	// set the port on which the server is running
	serverIP = argv[1];
	port = atoi(argv[2]);
	
	// create a socket
	server_s = socket(PF_INET, SOCK_STREAM, 0);
	if (server_s < 0)
		ohnoes("Error while creating socket");

	// configure the server's address
	memset(&serverAddr, 0, sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(port);
	serverAddr.sin_addr.s_addr = inet_addr(serverIP);

	// connect to the server
	int ret;
	printf("Connecting to server: [%s:%d]...", serverIP, port);
	ret = connect(server_s, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
	if (ret < 0)
		ohnoes("Error in connecting to the server");
	else
		printf("CONNECTED.\n");

	while (1)
	{
		// get connection status message from the server
		bytesReceived = recv(server_s, buffer, BUFFER_SIZE, 0);
		if (bytesReceived < 0)
			ohnoes("Error while receiving msg from server");
		buffer[bytesReceived] = '\0';
		
		// check contents of message
		buffer[bytesReceived] = '\0';
		if (strcmp(buffer, "No threads availeble. Shoo now--GIT!") == 0)
		{
			shutdown(server_s, 2);
			ohnoes("Server reports no available threads. Sad panda...");
		}
		else
		{
			// print message received from server
			printf("Message received from server: [\"%s\"]", buffer);
			
			// get message to send to server
			printf("\nMessage to server >>");
			if (fgets(buffer, BUFFER_SIZE, stdin) == NULL)
				ohnoes("Error while getting user input to send to server");

			// send message to the server
			buffer[strlen(buffer)-1] = '\0';
			bytesSent = send(server_s, buffer, BUFFER_SIZE, 0);
			if (bytesSent < 0)
				ohnoes("Error while sending message to the server");
				
			// if message was "GOODBYE", exit while loop and shut down conn.
			if (strcmp(buffer, "GOODBYE") == 0)
			{
				printf("So long... *nostalgia*\n");
				break;
			}
		}
	}
	
	// shutdown connection to server
	shutdown(server_s, 2);
	
	return(EXIT_SUCCESS);
}


//-----------------------------------------------------------------------------
// Function: ohnoes()
// Input (msg): A c-string error messag to print out
// Postcondition: The function has printed an error message and terminated
//-----------------------------------------------------------------------------
void ohnoes(const char* msg)
{
	printf("%s\n", msg);
	exit(1);
}

