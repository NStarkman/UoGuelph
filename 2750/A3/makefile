CC = clang
CFLAGS = -Wall -std=c99 -pedantic 
LDFLAGS = -shared
SWIG = swig
SWIGFLAGS = -python
PYTHON_PATH = /usr/include/python3.7m

all: libmol.so _molecule.so

mol.o: mol.c mol.h
	$(CC) $(CFLAGS) -c -fpic $< -o $@

libmol.so: mol.o
	$(CC) $(LDFLAGS) $< -o $@

molecule_wrap.c molecule.py: molecule.i mol.h
	$(SWIG) $(SWIGFLAGS) $<

molecule_wrap.o: molecule_wrap.c
	$(CC) $(CFLAGS) -c -I $(PYTHON_PATH) -fpic -dynamiclib $< -o $@

_molecule.so: molecule_wrap.o libmol.so
	$(CC) $(LDFLAGS) $< -fpic -L. -lmol -o $@

clean:
	rm -f *.o *.pyc *.so
