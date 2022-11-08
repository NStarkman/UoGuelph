A3exe: createTweet.o displayTweets.o searchTweets.o countStopWords.o deleteTweet.o saveTweet.o loadTweet.o sortID.o addNodeToList.o mainA3.o swap.o getCount.o clearList.o headerA3.h helper.h
	gcc -Wall -std=c99 createTweet.o displayTweets.o searchTweets.o countStopWords.o deleteTweet.o saveTweet.o loadTweet.o sortID.o addNodeToList.o swap.o getCount.o clearList.o mainA3.o -o A3exe -g
createTweet.o: createTweet.c headerA3.h 
	gcc -Wall -std=c99 -c createTweet.c -g
displayTweets.o: displayTweets.c headerA3.h
	gcc -Wall -std=c99 -c displayTweets.c -g
searchTweets.o: searchTweets.c headerA3.h 
	gcc -Wall -std=c99 -c searchTweets.c -D_GNU_SOURCE -g
countStopWords.o: countStopWords.c headerA3.h
	gcc -Wall -std=c99 -c countStopWords.c -g
deleteTweet.o: deleteTweet.c headerA3.h
	gcc -Wall -std=c99 -c deleteTweet.c -g
saveTweet.o: saveTweet.c headerA3.h
	gcc -Wall -std=c99 -c saveTweet.c -g
loadTweet.o: loadTweet.c headerA3.h
	gcc -Wall -std=c99 -c loadTweet.c -g
sortID.o: sortID.c headerA3.h helper.h
	gcc -Wall -std=c99 -c sortID.c -g
addNodeToList.o: addNodeToList.c headerA3.h
	gcc -Wall -std=c99 -c addNodeToList.c -g
swap.o: swap.c headerA3.h helper.h
	gcc -Wall -std=c99 -c swap.c -g
getCount.o: getCount.c headerA3.h helper.h
	gcc -Wall -std=c99 -c getCount.c -g
clearList.o: clearList.c headerA3.h helper.h
	gcc -Wall -std=c99 -c clearList.c -g
mainA3.o: mainA3.c headerA3.h helper.h
	gcc -Wall -std=c99 -c mainA3.c -g
clean: 
	rm *.o A3exe