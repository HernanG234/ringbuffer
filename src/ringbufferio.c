#include <stdio.h>

#include "ringbuffer.h"
#include "ringbufferio.h"

void *rbwriter (void *arg){                 //RingBufferWriter, writes the contents of 'bufferw' in the ringbuffer 'b'
				
  printf ("%s starting up...\n", (char *) arg);	//Prints when thread starts
                                            
  	  	  	  	  	  	  	  	  	  	  	  	//Arbitrary buffer of 20 consecutive values for testing purposes
  int bufferw[TEST_BUFFER_SIZE] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,11, 12, 13, 14, 15, 16, 17, 18, 19, 20 };
  for (int i = 0; i < TEST_BUFFER_SIZE; i++){ //For cycle to write everything in the ringbuffer   
      enqueue (buffer, bufferw[i]);	                //Call enqueue
      printf ("Writing in buffer[%d] value: %d by thread: %s\n", PREVIOUS_IN, bufferw[i], (char *) arg);	//Print for testing purposes
    }
  return NULL;
}

void *rbreader (void *arg){                 //RingBufferReader, reads the contents of the ringbuffer 'b'
  printf ("%s starting up...\n", (char *) arg);

  while (true){                              //Keeps reading!			
      int a = dequeue (buffer);	                //Calls dequeue
      printf ("Reading in buffer[%d] value: %d by thread: %s\n", PREVIOUS_OUT, a, (char *) arg);	//Print for testing purposes
    }

  return NULL;
}
