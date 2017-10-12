# ringbuffer
## Ring buffer multi-threading exercise

Code is a bit overcomment.
To run type:

>gcc -Wall -pthread -o ringbuffertest.out main.c

>./ringbuffertest.out

#### Comments on behaviour

```
Reader 1 starting up...                                                                                                                                                                       
Writer 1 starting up...                                                                                                                                                                       
Writing in buffer[0] value: 1 by thread: Writer 1  
Writing in buffer[1] value: 2 by thread: Writer 1                                                                                                                                             
Writing in buffer[2] value: 3 by thread: Writer 1 
	.
	.
	.
Writing in buffer[7] value: 8 by thread: Writer 1                                                                                                                                             
Writing in buffer[0] value: 9 by thread: Writer 1                                                                                                                                             
Reader 2 starting up...                                                                                                                                                                       
Writer 2 starting up...                                                                                                                                                                       
Reading in buffer[0] value: 1 by thread: Reader 1 
```

It looks like `Reader 1` is reading the wrong value but it's actually
reading the correct one. The scheduler gives the processor to the 
other threads between the `dequeue()` call from `Reader` 1 and its `printf()`
thus making this small "visual" bug.

```
	.
	.
	.
Writing in buffer[7] value: 12 by thread: Writer 2                                                                                                                                          
Reading in buffer[0] value: 13 by thread: Reader 1                                                                                                                                          
Writing in buffer[0] value: 13 by thread: Writer 2                                                                                                                                          
Reading in buffer[1] value: 14 by thread: Reader 1                                                                                                                                          
Writing in buffer[1] value: 14 by thread: Writer 2 
	.
	.
	.
```

Same, but the other way round. `Reader` and `Writer` don't lock each
other thus causing this. The idea was to see the semaphore working
so using the same mutex in writer and reader didn't make sense.
