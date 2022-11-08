starkmanNathanA1: starkmanNathanA1.o main.o 
	gcc -Wall -std=c99 starkmanNathanA1.o main.o -o starkmanNathanA1 
starkmanNathanA1.o: starkmanNathanA1.c starkmanNathanA1.h 
	gcc -Wall -std=c99 -c starkmanNathanA1.c   
main.o: main.c starkmanNathanA1.h 
	gcc -Wall -std=c99 -c main.c 
clean: 
	rm *.o starkmanNathanA1