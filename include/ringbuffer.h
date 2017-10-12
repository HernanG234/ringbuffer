#ifndef RINGBUFFER_H_   /* Include guard */
#define RINGBUFFER_H_

#include <pthread.h>
#include <semaphore.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> //CHECK WITH GCC!

#define NEXT_IN ((buffer->in+1) & (buffer->N-1))	    //Adds 1 to the 'in' index and resets it when it gets to 16
#define NEXT_OUT ((buffer->out+1) & (buffer->N-1))	    //Same as NEXT_IN
#define PREVIOUS_IN ((buffer->in-1) & (buffer->N-1))	// Decrease 'in' by one and resets it when it gets to -1
#define PREVIOUS_OUT ((buffer->out-1) & (buffer->N-1))	//Same as PREVIOUS_IN
#define true 1

typedef struct ringbuffer{
	int *b;
	int N;
	int in;
	int out;
	pthread_mutex_t lock;
	pthread_mutex_t lockwr;
	pthread_mutex_t lockre;
	sem_t usedsem;
	sem_t freesem;
}ringbuffer;

ringbuffer* initbuffer(int N);
void enqueue (ringbuffer *buffer, int value);
int dequeue (ringbuffer *buffer);

#endif // RINGBUFFER_H_
