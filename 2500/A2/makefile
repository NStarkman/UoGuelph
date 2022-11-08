noStringsAttached: starkmanNathanA2.o main.o 
	gcc -Wall -std=c99 starkmanNathanA2.o main.o -o bin/noStringsAttached
starkmanNathanA2.o: src/starkmanNathanA2.c include/starkmanNathanA2.h 
	gcc -Wall -std=c99 -c src/starkmanNathanA2.c   
main.o: src/main.c include/starkmanNathanA2.h 
	gcc -Wall -std=c99 -c src/main.c 
clean: 
	rm *.o bin/noStringsAttached