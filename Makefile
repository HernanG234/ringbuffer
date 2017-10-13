IDIR =include
CC=gcc
CFLAGS=-I$(IDIR)

ODIR=obj
LIBS=-lm -lpthread

OBJ = src/ringbuffertest.o src/ringbuffer.o src/ringbufferio.o

ringbuffertest: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)

.PHONY: clean

clean:
	rm -f ringbuffertest src/*.o *~ core $(INCDIR)/*~
