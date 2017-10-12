#ifndef RINGBUFFERIO_H_   //Include guard
#define RINGBUFFERIO_H_

#include <ringbuffer.h>
#define TEST_BUFFER_SIZE 20	            //Just testing with a 20 int array.

extern ringbuffer *buffer;

void *rbwriter (void *arg);
void *rbreader (void *arg);

#endif // RINGBUFFERIO_H_
