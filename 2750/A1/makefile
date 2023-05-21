CC = clang
CFLAGS = -std=c99 -Wall -pedantic 
LIBS = -lm

all: libmol.so mol.o

libmol.so: mol.o mol.h
	$(CC) $(CFLAGS) mol.o -shared $(LIBS) -o libmol.so

mol.o: mol.c mol.h
	$(CC) $(CFLAGS) -c mol.c -fPIC -o mol.o

clean:
	rm -f *.o *.so