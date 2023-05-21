CC = clang
CFLAGS = -Wall -std=c99 -pedantic 
LDFLAGS = -shared
SWIG = swig
SWIGFLAGS = -python
PYTHON_PATH = /usr/include/python3.7m
PORT = 57811

all: libmol.so _molecule.so server

mol.o: mol.c mol.h
	$(CC) $(CFLAGS) -c -fpic $< -o $@

libmol.so: mol.o
	$(CC) $(LDFLAGS) $< -o $@

molecule_wrap.c molecule.py: molecule.i mol.h
	$(SWIG) $(SWIGFLAGS) $<

molecule_wrap.o: molecule_wrap.c
	$(CC) $(CFLAGS) -c -I $(PYTHON_PATH) -fpic $< -o $@

_molecule.so: molecule_wrap.o libmol.so
	$(CC) $(LDFLAGS) $< -fpic -L. -lmol -o $@

server: server.py MolDisplay.py _molecule.so
	python3 $< $(PORT)

clean:
	rm -f *.o *.pyc *.so
