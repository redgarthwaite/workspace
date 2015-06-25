//-----------------------------------------------------------------------------
// File: thread_server.cpp
// Description: Instantiates a server that uses threads and mutexes to handle
//              client interactions
//-----------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>					// for socket(), bind(), listen(), ...
#include <netinet/in.h>					// for sockaddr_in
#include <arpa/inet.h>					// for htons()
#include <string.h>						// for memset()
#include <pthread.h>					// for threading functions

// macro definitions
#define MAX_CONNECTIONS 5
#define BUFFER_SIZE 100
#define NO_SEND_OR_RECEIVE 2			// one way to shutdown() client conn.

// function prototypes
void ohnoes(const char* msg);
void* THREAD_handle_client(void* arg);

// structure to be passed to thread
struct args
{
	int client_s;	
};

// global variables
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;	// threads[], etc lock
pthread_t threads[MAX_CONNECTIONS];					// handles clients
struct args thread_data[MAX_CONNECTIONS];			// args to pass to threads
int clientsConnected = 0;							// # clients currently conn


//-----------------------------------------------------------------------------
// Function: main
// Program starts here
//-----------------------------------------------------------------------------
int main(int argc, char** argv)
{
	int server_s;							// the server's socket
	int client_s;							// the client's socket
	int port;								// port # that server serves on
	struct sockaddr_in server_addr;			// server's address (structure)
	char responseBuffer[BUFFER_SIZE];		// char[] holds responses to client

	// check commandline parameters
	if (argc != 1+1)
		ohnoes("Usage: thread_server <port number>");

	// set the thread values in threads[] to be (nothing)
	for(int i = 0; i < MAX_CONNECTIONS; i++)
		threads[i] = 0;

	// setup the socket
	port = atoi(argv[1]);
	if ( (server_s = socket(PF_INET, SOCK_STREAM, 0)) < 0)
		ohnoes("Error: Could not create socket");

	// construct local address for server
	memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(port);
	server_addr.sin_addr.s_addr = htons(INADDR_ANY);
	
	// bind the server to the local address
	if (bind(server_s,(struct sockaddr*)&server_addr,sizeof(server_addr)) != 0)
		ohnoes("Error: Could not bind to local address");
		
	// listen for incoming connections
	if (listen(server_s, MAX_CONNECTIONS) != 0)
		ohnoes("Error: Could not listen for incoming connections");
	printf("SERVER IS RUNNING\n");
	printf("  Now accepting connections on port %d\n", port);
		
	// handle incoming connections (create new thread for each connection)
	while (1)
	{
		int client_s;							// client socket
		struct sockaddr_in clientAddr;			// struct holds client info
		unsigned cal = sizeof(clientAddr);		// size of clientAddr in bytes
		int bytesRead = 0;
		int bytesSent = 0;

		// accept connection from the client
		client_s = accept(server_s, (struct sockaddr*)&clientAddr, &cal);
		printf("  New client connected.\n");

		// find an available thread for the client, if there is one
		int threadIndex = -1;
		for (int i = 0; i < MAX_CONNECTIONS; i++)
		{
			// acquire the lock so nothing else can modify locked variables
			pthread_mutex_lock(&lock);
			
			// search for available thread
			if (threads[i] == 0)
				threadIndex = i;

			// release lock
			pthread_mutex_unlock(&lock);
		}

		// if no threads are available, send client a msg and close connection
		if (threadIndex == -1)
		{
			sprintf(responseBuffer, "No threads availeble. Shoo now--GIT!");
			bytesSent = send(client_s, responseBuffer, BUFFER_SIZE, 0);
			if (bytesSent < 0)
				ohnoes("Error in sending 'go away' response to client");
			printf("  No threads avaialble. Shutting down client conn.\n");
			shutdown(client_s, NO_SEND_OR_RECEIVE);
		}
		else
		{
			// create a new thread to deal with the client
			printf("  Creating thread to handle new client.\n");
			int ret;
			pthread_t* threadPtr = &threads[threadIndex];
			thread_data[threadIndex].client_s = client_s;
			void* arg = &thread_data[threadIndex];
			ret = pthread_create(threadPtr, NULL, THREAD_handle_client, arg);
			if (ret != 0)
				ohnoes("Error in creating thread to handle client");
		}

		// announce how many clients are currently connected
		pthread_mutex_lock(&lock);
		printf("  Notice: %d clients are now connected\n", clientsConnected);
		pthread_mutex_unlock(&lock);
	}

	// we should never get here, but good practice == good
	shutdown(server_s, NO_SEND_OR_RECEIVE);
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


//-----------------------------------------------------------------------------
// Function: THREAD_handle_client()
// Input (arg): A void-pointer to a structure of arguments
// Postcondition: The thread has serviced the client in whatever way requested
//-----------------------------------------------------------------------------
void* THREAD_handle_client(void* arg)
{
	struct args* data;
	char buffer[BUFFER_SIZE];
	char responseBuffer[BUFFER_SIZE];
	int bytesSent = 0;
	int bytesReceived = 0;
	int client_s;

	// typecast arg to an args struct
	data = (struct args*) arg;
	client_s = data->client_s;

	// update number of clients connected to system
	pthread_mutex_lock(&lock);
	clientsConnected += 1;
	pthread_mutex_unlock(&lock);

	// send "connected" acknowledgement to client
	sprintf(buffer, "CONNECTED");
	bytesSent = send(client_s, buffer, BUFFER_SIZE, 0);
	if (bytesSent < 0)
	{
		printf("Error in thread while sending 'CONNECTED' response\n");
		return 0;
	}

	// interact with client until server receives "GOODBYE"
	while (1)
	{
		// get string from client
		bytesReceived = recv(client_s, buffer, BUFFER_SIZE, 0);
		if (bytesReceived < 0)
		{
			printf("Error in thread while receiving from client. Sad panda\n");
			return 0;
		}

		// check to see if we should shutdown connection
		printf("  Received from client: [\"%s\"]\n", buffer);
		if (strcmp(buffer, "GOODBYE") == 0)
			break;

		// modify the string (WARNING: potential buffer overflow)
		sprintf(responseBuffer, "RECEIVED STRING: '%s'", buffer);

		// send the modified string back to the client
		bytesSent = send(client_s, responseBuffer, BUFFER_SIZE, 0);
		if (bytesSent < 0)
		{
			printf("Error in thread in sending modified response to client\n");
			return 0;
		}
	}

	// shutdown the client connection and end thread
	shutdown(client_s, NO_SEND_OR_RECEIVE);
	
	// decrement the number of clients connected
	printf("  client disconnected\n");
	pthread_mutex_lock(&lock);
	clientsConnected -= 1;
	pthread_mutex_unlock(&lock);
}



