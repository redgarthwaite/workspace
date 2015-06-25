//-----------------------------------------------------------------------------
// File: threads.cpp
// Description: A simple program that makes use of threads
//-----------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

void* THREAD_thread1(void* arg);
void* THREAD_thread2(void* arg);

int main(int argc, char** argv)
{
	pthread_t	thread1;
	pthread_t	thread2;
	char msg1[] = "Thread1";
	char msg2[] = "Thread2";

	// create the threads
	int ret;
	ret = pthread_create(&thread1, NULL, THREAD_thread1, (void*)msg1);
	if (ret != 0)
		printf("Error creating thread1\n");
	ret = pthread_create(&thread2, NULL, THREAD_thread2, (void*)msg2);
	if (ret != 0)
		printf("Error creating thread2\n");
	
	// wait for thread1 and thread2 to finish
	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);
	
	printf("Both threads returned successfully\n");
	
	return(EXIT_SUCCESS);
}

//-----------------------------------------------------------------------------
// Thread Function: THREAD_thread1()
// Input (arg): A blob (i.e. void*) of data to use
//-----------------------------------------------------------------------------
void* THREAD_thread1(void* arg)
{
	char* msg;
	msg = (char*)arg;
	printf("Welcome to Thread1. I'd just like to say: %s\n", msg);
}

//-----------------------------------------------------------------------------
// Thread Function: THREAD_thread2()
// Input (arg): A blob (i.e. void*) of data to use
//-----------------------------------------------------------------------------
void* THREAD_thread2(void* arg)
{
	char buffer[100];

	// get some input and echo it back
	printf("Welcome to Thread2\n");
	fgets(buffer, 100, stdin);					// get some input from user
	buffer[strlen(buffer)-1] = '\0';			// null-terminate last char of buffer
	
	printf("Thanks for typing \"%s\"\n", buffer);
}



