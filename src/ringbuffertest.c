/*
 * ringbuffer.c
 *
 *  Created on: Oct 10, 2017
 *      Author: h
 */

#include <pthread.h>
#include <semaphore.h>
#include <ringbuffer.h>
#include <ringbufferio.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> //CHECK WITH GCC!

#define true 1

ringbuffer *buffer;

int main(){                                 //Main for testing. It declares 4 threads, 2 for writing and 2 for reading

  buffer = initbuffer(8);

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

  return 0;
}
