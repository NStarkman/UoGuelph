CC = gcc
CFLAGS = -Wall -std=c99 -pedantic 
LDFLAGS = -lm


all: P11 P12 P21 P22 P23

P11: P11.o
	$(CC) $(CFLAGS) -o P11 P11.o $(LDFLAGS)
P12: P12.o
	$(CC) $(CFLAGS) -o P12 P12.o $(LDFLAGS)
P21: P21.o
	$(CC) $(CFLAGS) -o P21 P21.o $(LDFLAGS)
P22: P22.o
	$(CC) $(CFLAGS) -o P22 P22.o $(LDFLAGS)
P23: P23.o
	$(CC) $(CFLAGS) -o P23 P23.o $(LDFLAGS)

clean:
	rm -f *.o P11 P12 P21 P22 P23