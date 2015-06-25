//-----------------------------------------------------------------------------
// File: mutex.cpp
// Description: Basic use of threads using locks to make use of shared memory
//-----------------------------------------------------------------------------

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

// function prototypes
void* THREAD_write_to_stuff(void* param);

// macros
#define ARRAY_SIZE 100
#define PAUSE_ITERATIONS 100000

// global variables
pthread_mutex_t stuffLock = PTHREAD_MUTEX_INITIALIZER;
char stuff[ARRAY_SIZE + 1];
int stuffIndex = 0;

int main(int argc, char** argv)
{
	// declare thread objects
	pthread_t thread1;
	pthread_t thread2;
	char param1[] = "1";
	char param2[] = "2";
	
	// start the two threads
	pthread_create(&thread1, NULL, THREAD_write_to_stuff, (void*)param1);
	pthread_create(&thread2, NULL, THREAD_write_to_stuff, (void*)param2);

	// wait for thread1 and thread2 to finish before continuing
	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);
	
	// print result
	stuff[ARRAY_SIZE] = '\0';
	printf("Contents of stuff[]:\n");
	printf("  %s\n", stuff);

	return(EXIT_SUCCESS);
}

//-----------------------------------------------------------------------------
// Function: THREAD_write_to_stuff()
// Inputs: None
// Postcondition: The function has written to the stuff array
//-----------------------------------------------------------------------------
void* THREAD_write_to_stuff(void* param)
{
	char* c;
	c = (char*)param;

	// acquire the lock so no one else can acquire one until we release
	pthread_mutex_lock(&stuffLock);

	// write to the stuff array
	for(unsigned i = 0; i < ARRAY_SIZE/2; i++)
	{
		// without locks, this pause time would make the threads alternate
		// writing to the stuff array
		for(unsigned j = 0; j < PAUSE_ITERATIONS; j++) {}
		stuff[stuffIndex] = c[0];
		stuffIndex += 1;
	}

	// release the lock
	pthread_mutex_unlock(&stuffLock);
}

