CC = gcc
CFLAGS = -Wall -std=c99 -pedantic 
LDFLAGS = -lm

all: P11 P12 P2

P11: P11.o
	$(CC) $(CFLAGS) -o P11 P11.o $(LDFLAGS)

P12: P12.o
	$(CC) $(CFLAGS) -o P12 P12.o $(LDFLAGS)

P2:  P2.o
	$(CC) $(CFLAGS) -o P2 P2.o $(LDFLAGS)

clean:
	rm -f *.o P11 P12 P2