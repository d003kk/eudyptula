CC=gcc
CFLAGS=-I.
DEPS = 

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

test: test.o 
