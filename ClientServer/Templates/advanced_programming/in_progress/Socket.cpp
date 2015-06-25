//-----------------------------------------------------------------------------
// File: Socket.cpp
// Description: Implements the Socket class described in Socket.h
//-----------------------------------------------------------------------------
//------------------------------------------------
// C o n s t r u c t o r ,   D e s t r u c t o r
//------------------------------------------------
Socket::Socket(const char* ip, const unsigned port)
{
	// for self-reference
	type = CLIENT;

	// setup socket
	sid = socket(PF_INET, SOCK_STREAM, 0);
	if (sid < 0)
		ohnoes("Cannot create socket for client.");

	// configure the server's address in a special address-holding struct
	memset(&addr, 0, sizeof(addr));						// clear the struct
	addr.sin_family = AF_INET;							// addr family: internet
	addr.sin_port = htons(port);						// server's port
	addr.sin_addr.s_addr = inet_addr(serverIP.c_str());	// IP as an integer
}


Socket::Socket(const unsigned port)
{
	// for self-reference
	type = SERVER;

	// setup socket
	sid = socket(PF_INET, SOCK_STREAM, 0);
	if (sid < 0)
		ohnoes("Cannot create socket for server.");
	
	// configure the server's address in a special address-holding struct
	memset(&addr, 0, sizeof(addr));				// clear the struct
	addr.sin_family = AF_INET;					// addr family: internet
	addr.sin_port = htons(port);				// port to serve on
	addr.sin_addr.s_addr = htons(INADDR_ANY);	// serve to anyone who connects
	
	// establish (finalize) address and port for server and link to socket
	int ret;
	ret = bind(sid, (struct sockaddr*)&addr, sizeof(addr));
	if (ret != 0)
		ohnoes("Could not bind server's {ip, port} to socket.");
}

//----------------------------------------------------
// C o n s t a n t   m e m b e r   f u n c t i o n s
//----------------------------------------------------






//--------------------------------------------------
// M u t a t o r   m e m b e r   f u n c t i o n s
//--------------------------------------------------
void Socket::start()
{

}



