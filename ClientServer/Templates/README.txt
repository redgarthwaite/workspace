All of the files here are things that I wrote to familiarize myself with
advanced programming techniques in C++ that seem to be fairly common in the
workplace. I wish UCR had taught them to us better while we were there.

#-----------------------------------------------------------
# In progress and not necessarily working (i.e. don't use)
#-----------------------------------------------------------
thread_server.cpp


#----------------------------
# Basic Client-Server setup
#----------------------------
A basic client-server setup. Run the server first so that it is ready to
accept connections from the client. Run the client and type a string to be
sent to the server. The server modifies the string and sends it back to the
client. The client prints the string and exits the program. The server remains
ready to accept further client connections (forever until it is CTRL+C closed)

Files:
	client.cpp
	server.cpp
	
Usage:
	make
	server <port>
	client <server's IP> <server port>
	
Example:
	make
	server 14441
	(type "ifconfig", press ENTER, and get your IP address from eth0)
	client 10.13.167.101 14441


#------------------
# Basic threading
#------------------
A basic use of threading. The program creates one thread that prints a message
and returns. The second thread waits for some user input, prints it to the
display, and returns. The main function waits for both threads to return before
continuing.

Files:
	threads.cpp
	
Usage:
	threads
	
Example:
	make
	threads

	
#----------------
# Basic Mutexes
#----------------
A program that uses two threads that share a single global array. One thread
writes fifty '1' characters to the current index of the array. The other thread
writes fifty '2' characters to the current index of the array. Enabling locks
causes expected behavior: One thread writes fifty '1's and then the next thread
writes fifty '2's. Disabling locks results in the threads alternatingly
grabbing access of the array and the result is a partial alternating series of
'1's and '2's.

Files:
	mutex.cpp

Usage:
	mutex <use locks? 1 or 0>

Example:
	make
	mutex 1				# this will enable locks
	mutex 0				# this will disable locks



