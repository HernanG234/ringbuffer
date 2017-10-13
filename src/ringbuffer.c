#include <stdlib.h>

#include "ringbuffer.h"

ringbuffer* initbuffer(int N){
	ringbuffer *buffer = malloc(sizeof(ringbuffer));
	buffer->N = N;
	buffer->b = calloc(N,sizeof(int));
	buffer->in = 0;
	buffer->out = 0;
	pthread_mutex_init(&buffer->lock, NULL);
	sem_init (&buffer->usedsem, 0, 0);
	sem_init (&buffer->freesem, 0, N);
	return buffer;
}

void enqueue (ringbuffer *buffer, int value){                //Enqueue function adds 'value' to the ringbuffer
 
  sem_wait (&buffer->freesem);		            //If there's free space in the ringbuffer it can write
                                        //also decreases 1 to the free space index
  pthread_mutex_lock (&buffer->lock);	        //Locks buffer
  buffer->b[buffer->in] = value;		                //Write in the buffer
  buffer->in = NEXT_IN;			                //Increase 'in'
  pthread_mutex_unlock (&buffer->lock);	        //Releases buffer
  sem_post (&buffer->usedsem);	            	// Increment the count of used buffer
}

int dequeue (ringbuffer *buffer){                              //Enqueue function retrieves 'result' from the ringbuffer
	
  sem_wait (&buffer->usedsem);		                // Waits until there's sth to read
                                            //also decreases 1 to the used space index
  pthread_mutex_lock (&buffer->lock);
  int result = buffer->b[buffer->out];		                //Read the buffer
  buffer->out = NEXT_OUT;	                    	//Increase 'out'
  pthread_mutex_unlock (&buffer->lock);
  sem_post (&buffer->freesem);		                // Increment the count of free spaces

  return result;
}
