//-----------------------------------------------------------------------------
// File: Socket.h
// Description: Definition of a Socket, which is a class which abstracts
//              away the complexity of TCP socket handling and comes with
//              a small library of functions/functionality that aids in data
//              transfer
//-----------------------------------------------------------------------------

#ifndef __SOCKET_H__
#define __SOCKET_H__

// necessary socket & network libraries
#include <sys/socket.h>		// for socket(), bind(), accept(), listen(), ...
#include <netinet/in.h>		// for sockaddr_in struct
#include <arpa/inet.h>		// for htons()
#include <string.h>			// for memset()

// setup sockets/etc to be a client or a server
enum {CLIENT, SERVER};

// macro definitions
#define BUFFER_SIZE 1000	// max # bytes to send/recv in one burst

// class definition
class Socket
{
private:
	unsigned type;					// either CLIENT or SERVER (see enum above)
	int sid;						// socket id
	struct sockaddr_in addr;		// struct to hold address information
	string serverIP;				// IP of server (to connect to if client)
	int port;						// port of server (to connect to if client)
	unsigned int MAX_CONNECTIONS;	// max # of simult. client conn. (if server)
	
	// error-printing function
	ohnoes(const char* msg);
	ohnoes(string msg) { ohnoes(msg.c_str(); }

public:
	// constructor, destructor
	Socket(const char* ip, const unsigned port);		// setup a client
	Socket(const unsigned port);						// setup a server
	~Socket();
	
	// constant member functions
	
	
	// mutator member functions
	void connect();						// client-specific: connect to server
	void start();						// server-specific: start server
	void shutdown();					// shutdown connection
		


};

#endif
