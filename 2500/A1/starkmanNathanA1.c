#include "starkmanNathanA1.h"


/******
 openFileForReading: Opens the file and preps it for reading
 In: fileName
 Out: fp or NULL
 Post: File is opened for reading for later functions
*******/
FILE * openFileForReading(char * fileName) {
  //The pointer for the file
  FILE * fp;
  fp = fopen(fileName, "r");
  if (fp != NULL) {
    return fp;
  }
  return NULL;
}

/******
 readMovies: 
 In: file, movieNames
 Out: 0 or 1 to represent either failed or successful exit, respectfully
 Post: movieNames becomes populated with the names of the movies
*******/
int readMovies(FILE * file, char movieNames[NUMBER_MOVIES][MAX_STR]) {
  if (file == NULL) {
    return 0;
  }
  //Ensures that only 3 are in the movies.txt file
  int count = 0;
  int count2 = 0;
  //index of the movies of the list
  int index = 0;
  char text[MAX_STR];
  while (fgets(text, sizeof(text), file)) {
    count++;
    if (count > NUMBER_MOVIES) {
      count2 = 1;
    }
  }
  if (count < NUMBER_MOVIES) {
    count2 = 1;
  }
  rewind(file);
  if (count2 == 1) {
    return 0;
  } else {
    while (fgets(text, sizeof(text), file)) {
      strcpy(movieNames[index], text);
      index++;

    }
  }
  
  // FOR PRINTING TO ENSURE THERE IS NO NEWLINE
  for (int i = 0; i < NUMBER_MOVIES; i++) {
      //length of the word to remove the newline
    int length = strlen(movieNames[i]);
    movieNames[i][length - 1] = '\0';
  }
  return 1;
}

/******
 readReviews: reads the reviews from the review file and puts them into the reviewStruct array
 In: file, reviews
 Out: 0 or 1 to represent either failed or successful exit, respectfully
 Post: reviews is filled with the names of the reviewers and their reviews
*******/
int readReviews(FILE * file, struct reviewStruct reviews[NUMBER_REVIEWERS]) {
  int count = 0;
  //List amount checker
  int count2 = 0;
  //index of the reviews 
  int index = 0;
  char names[MAX_STR];
  while (fgets(names, sizeof(names), file)) {
    count++;
    if (count > NUMBER_REVIEWERS) {
      count2 = 1;
    }
  }
  if (count < NUMBER_REVIEWERS) {
    count2 = 1;
  }
  rewind(file);
  if (count2 == 1) {
    return 0;
  } else {
    char array[4][MAX_STR];
    while (fgets(names, sizeof(names), file)) {
      char * value;
      value = strtok(names, " ");
      //index of the array of letters
      int index2 = 0;
      while (value != NULL) {

        strcpy(array[index2], value);
        value = strtok(NULL, " ");
        index2++;

      }
      strcpy(reviews[index].reviewer, array[0]);
      if ((array[1][0] == 'Y') || (array[1][0] == 'y')) {
        reviews[index].feedback[0] = 1;
      } else {
        reviews[index].feedback[0] = 0;
      }
      if (array[2][0] == 'Y' || array[2][0] == 'y') {
        reviews[index].feedback[1] = 1;
      } else {
        reviews[index].feedback[1] = 0;
      }
      if ((array[3][0] == 'Y') || (array[3][0] == 'y')) {
        reviews[index].feedback[2] = 1;
      } else {
        reviews[index].feedback[2] = 0;
      }
      index++;
    }
  }
  return 1;

}

/******
 getMostCriticalReviewers: Finds the reviewers with the most negative movie reviews
 In: reviewStruct reviews, charvmostCritialReviewers
 Out: the amount of people with the most negative reivews
 Post: Populates mostCriticalReviwers with the names of the reviewers with the most popular reviews
*******/
int getMostCriticalReviewers(struct reviewStruct reviews[NUMBER_REVIEWERS], char mostCriticalReviewers[NUMBER_REVIEWERS][MAX_STR]) {
  //Array of reviewer negative amounts
  int array[NUMBER_REVIEWERS];
  //The actual lowest number
  int lowest = 0;
  for (int i = 0; i < NUMBER_REVIEWERS; i++) {
      //sum of the reviews based on their numbers
    int sum = reviews[i].feedback[0] + reviews[i].feedback[1] + reviews[i].feedback[2];
    array[i] = sum;
  }
  for (int i = 0; i < NUMBER_REVIEWERS; i++) {
    if (i == 0) {
      lowest = array[i];
    } else {
      if (array[i] < lowest) {
        lowest = array[i];
      }
    }
  }
  //Amount of people with the lowest index
  int criticalIndex = 0;
  for (int i = 0; i < NUMBER_REVIEWERS; i++) {
    if (array[i] == lowest) {
      strcpy(mostCriticalReviewers[criticalIndex], reviews[i].reviewer);
      criticalIndex++;

    }

  }
  return criticalIndex;

}

/******
 getMostRecommendedMovies: Finds the movie with the most positive reviews
 In: char MovieNames, reviewStruct reviews, char mostRecommendedMovies
 Out: the amount of movies with the highest amount of recommendations
 Post: populates mostRecommendedMovies with the names of the movies with the most recommends
*******/
int getMostRecommendedMovies(const char movieNames[NUMBER_MOVIES][MAX_STR],const struct reviewStruct reviews[NUMBER_REVIEWERS], char mostRecommendedMovies[NUMBER_MOVIES][MAX_STR]) {
  // The sum of the reviews being either zero or one
  int sum[NUMBER_MOVIES];
  //Index of the Sum Array
  int index = 0;
  //The highest number for the movies
  int highest;
  for (index = 0; index < NUMBER_MOVIES; index++) {
    sum[index] = 0;
    for (int i = 0; i < NUMBER_REVIEWERS; i++) {
      sum[index] += reviews[i].feedback[index];
    }
  }
  for (int i = 0; i < NUMBER_MOVIES; i++) {
    if (i == 0) {
      highest = sum[i];
    } else {
      if (sum[i] > highest) {
        highest = sum[i];
      }
    }
  }
  // amount of movies with the most recommendations
  int index2=0;
  for (int i = 0; i < NUMBER_MOVIES; i++) {
    if (sum[i]==highest){
      strcpy(mostRecommendedMovies[index2], movieNames[i]);
      index2++;
    }
  }

  return index2;

}

/******
 EnumerateMovie: Seperates the movie names into words and counts the letters
 In: char movie, int charCounts
 Out: Returns the amount of words in the movie title
 Post: Populates charCounts with the amount of letters per words
*******/
int enumerateMovie(const char movie[MAX_STR], int charCounts[MAX_WORDS]){
  //The movie name used to seperate into characters
  char movieName[MAX_STR];
  strcpy(movieName, movie);
  //the pointer to each letter
  char * value;
      value = strtok(movieName, " ");
      //index for charCounts
      int index2 = 0;
      while (value != NULL) {
        charCounts[index2]=0;
        charCounts[index2] = strlen(value);
        value = strtok(NULL, " ");
        index2++;
      }
  return index2;
}

/******
 predictMovie: 
 In: char movie
 Out: returns the value of the movie prediction
 Post: returns the value of the movie prediction
*******/
int predictMovie(const char movie[MAX_STR]) {
  //the array of letters for the words
  int words[MAX_WORDS];
  //The score of the movie
  int movieNumber=0;
  //the amount of words in the movie name
  int numWords = enumerateMovie(movie, words);
  printf("%d\n", numWords);
  if (numWords==1){
    movieNumber += -2;
  }
  else if (numWords>1){
    //Checks the value of the words if it is even or odd
    int total = 0;
    for (int i=0; i<numWords; i++){
      total +=words[i]%2;
    }
    if (total==0){
      movieNumber +=1;
    }
  }
  else if (numWords>2){
    movieNumber +=-1;
  }
  //Checks if the words are even
  int firstCount=words[0];
  int checker = 0;
  for (int i=0;i < numWords; i++){
    if (words[i]!=firstCount){
      checker = 1;
      break;
    }
  }
  if (checker == 0){
    movieNumber +=2;
  }

  if (movieNumber >2){
    return 2;
  }
  else if (movieNumber<-2){
    return -2;
  }
  
  return movieNumber;

}