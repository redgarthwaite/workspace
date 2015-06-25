//-----------------------------------------------------------------------------
// File: SimpleClient.cpp
// Description: Implements the SimpleClient class described in SimpleClient.h
//-----------------------------------------------------------------------------
//------------------------
// C o n s t r u c t o r
//------------------------
SimpleClient::SimpleClient(const char* ip, const unsigned port)
{
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


//----------------------------------------------------
// C o n s t a n t   m e m b e r   f u n c t i o n s
//----------------------------------------------------
void Socket::connect()
{
	int ret;
	ret = connect(sid, (struct sockaddr*)&addr, sizeof(addr));
	if (ret < 0)
		ohnoes("Cannot connect to server.");
}


//--------------------------------------------------
// M u t a t o r   m e m b e r   f u n c t i o n s
//--------------------------------------------------






