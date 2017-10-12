/*
 * ringbuffer.c
 *
 *  Created on: Oct 10, 2017
 *      Author: h
 */

#include <pthread.h>
#include <semaphore.h>
//#include <time.h>
//#include <stdio.h>
//#include <unistd.h> CHECK WITH GCC!

#define true 1
#define N 8			                    	//N must be 2^i for reseting purposes
#define TEST_BUFFER_SIZE 20	            	//Just testing with a 20 int array.
#define NEXT_IN ((in+1) & (N-1))	    	//Adds 1 to the 'in' index and resets it when it gets to 16
#define NEXT_OUT ((out+1) & (N-1))	    	//Same as NEXT_IN
#define PREVIOUS_IN ((in-1) & (N-1))		// Decrease 'in' by one and resets it when it gets to -1
#define PREVIOUS_OUT ((out+1) & (N-1))		//Same as PREVIOUS_IN

int b[N];			                    	//Declare actual ringbuffer
int in = 0, out = 0;	            		//Declare indexes
											//Declare mutexes and semaphores
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER, lockwr =
  PTHREAD_MUTEX_INITIALIZER, lockre = PTHREAD_MUTEX_INITIALIZER;
sem_t usedsem, freesem;


void init ()
{
  sem_init (&usedsem, 0, 0);
  sem_init (&freesem, 0, N);
}

void enqueue (int value)                	//Enqueue function adds 'value' to the ringbuffer			
{  
  sem_wait (&freesem);		            	//If there's free space in the ringbuffer it can write
											//also decreases 1 to the free space index
  pthread_mutex_lock (&lock);	        	//Locks buffer
  b[in] = value;		                	//Write in the buffer
  in = NEXT_IN;			                	//Increase 'in'
  pthread_mutex_unlock (&lock);	        	//Releases buffer 
  sem_post (&usedsem);	            		// Increment the count of used buffer
}

int dequeue ()                          	//Enqueue function retrieves 'result' from the ringbuffer
{				
  sem_wait (&usedsem);		            	// Waits until there's sth to read
											//also decreases 1 to the used space index
  pthread_mutex_lock (&lock);
  int result = b[out];		            	//Read the buffer
  out = NEXT_OUT;	                   		//Increase 'out'
  pthread_mutex_unlock (&lock);
  sem_post (&freesem);		            	// Increment the count of free spaces

  return result;
}

void *rbwriter (void *arg)                  //RingBufferWriter, writes the contents of 'bufferw' in the ringbuffer 'b'
{				
  printf ("%s starting up...\n", (char *) arg);	//Prints when thread starts
                                            
  int bufferw[TEST_BUFFER_SIZE] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,11, 12, 13,
        14, 15, 16, 17, 18, 19, 20 };       //Arbitrary buffer of 20 consecutive values for testing purposes	
  for (int i = 0; i < TEST_BUFFER_SIZE; i++) //For cycle to write everything in the ringbuffer
    {				
      pthread_mutex_lock (&lockwr);	        //Locks for 1 Writer at a time

      enqueue (bufferw[i]);	                //Call enqueue
      printf ("Writing in buffer[%d] value: %d by thread: %s\n", PREVIOUS_IN, bufferw[i], (char *) arg);	//Print for testing purposes

      pthread_mutex_unlock (&lockwr);
    }
  return NULL;
}

void *rbreader (void *arg)                  //RingBufferReader, reads the contents of the ringbuffer 'b'
{				
  printf ("%s starting up...\n", (char *) arg);

  while (true)                              //Keeps reading!
    {				
      pthread_mutex_lock (&lockre);	        //Locks for 1 Reader at a time 
      int a = dequeue ();	                //Calls dequeue
      printf ("Reading in buffer[%d] value: %d by thread: %s\n", PREVIOUS_OUT, a, (char *) arg);	//Print for testing purposes
      pthread_mutex_unlock (&lockre);
    }

  return NULL;
}

int main ()                                 //Main for testing. It declares 4 threads, 2 for writing and 2 for reading
{				
  init ();                                  //Initialize semaphores

  pthread_t rbw1, rbw2, rbr1, rbr2;
  pthread_create (&rbw1, NULL, rbwriter, "Writer 1");
  pthread_create (&rbw2, NULL, rbwriter, "Writer 2");
  pthread_create (&rbr1, NULL, rbreader, "Reader 1");
  pthread_create (&rbr2, NULL, rbreader, "Reader 2");

  void *result;			                    //Wait for every thread to finish
  pthread_join (rbw1, &result);	            //Had some printing problems 
  pthread_join (rbw2, &result);	            //without this waiting
  pthread_join (rbr1, &result);
  pthread_join (rbr2, &result);

  sem_destroy (&usedsem);	                //Free space of semaphores
  sem_destroy (&freesem);
  return 0;
}
