//-----------------------------------------------------------------------------
// File: SimpleClient.h
// Description: Defines a simple Client, which is a class designed to connect
//              over the Internet to a Server
//-----------------------------------------------------------------------------

#ifndef __SIMPLECLIENT_H__
#define __SIMPLECLIENT_H__

// necessary socket & network libraries
#include <sys/socket.h>		// for socket(), bind(), accept(), listen(), ...
#include <netinet/in.h>		// for sockaddr_in struct
#include <arpa/inet.h>		// for htons()
#include <string.h>			// for memset()

// macro definitions
#define BUFFER_SIZE 1000	// max # bytes to send/recv in one burst

class SimpleClient
{
private:
	int sid;						// socket id
	struct sockaddr_in addr;		// struct to hold address information
	string serverIP;				// IP of server (to connect to if client)
	int port;						// port of server (to connect to if client)
	string buffer;					// holds messages from server
	
	// error-printing function
	ohnoes(const char* msg) { cout << "Error: " << msg << endl; exit(1); }
	ohnoes(string msg) { ohnoes(msg.c_str(); }

public:
	// constructor, destructor
	SimpleClient(const char* ip, const unsigned port);
	~SimpleClient() {}

	// constant member functions


	// modification member functions
	void connect();						// connect to server
	void shutdown();					// shutdown connection to server
	int send(string msg);				// send (msg) to server
	int recv();							// block until msg received from server
	
	// overloaded operators
	ostream& operator <<(ostream& out, 
	
	
	
};



