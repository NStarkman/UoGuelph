CC=gcc
CFLAGS=-c -Wall
LIB = -lm

all: P1 P12 P2 P22

P1: P1.o
	$(CC) P1.o -o P1 $(LIB)

P12: P12.o
	$(CC) P12.o -o P12 $(LIB)

P2: P2.o P2Extra.o
	$(CC) P2.o P2Extra.o -o P2 $(LIB)

P22: P22.o P2Extra.o
	$(CC) P22.o P2Extra.o -o P22 $(LIB)

P2.o: P2.c P2.h P2Extra.h
	$(CC) $(CFLAGS) P2.c $(LIB)

P22.o: P22.c P2.h P2Extra.h
	$(CC) $(CFLAGS) P22.c $(LIB)

P1.o: P1.c P1.h 
	$(CC) $(CFLAGS) P1.c $(LIB)

P12.o: P12.c P1.h
	$(CC) $(CFLAGS) P12.c $(LIB)

P2Extra.o: P2Extra.c P2Extra.h
	$(CC) $(CFLAGS) P2Extra.c $(LIB)

clean:
	rm -rf *o P1 P12 P2 P22