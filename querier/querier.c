/* querier.c
 * takes parameters pageDirectory and indexFilename where pageDirectory is the pathname of a directory produced by the crawler and indexFilename is the pathname of a file produced by the indexer
 * cs50
 * Ellie Boyd
 * Oct 24 2021
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "webpage.h"
#include "pagedir.h"
#include "index.h"
#include "file.h"
#include "word.h"
#include "counters.h"
#include "mem.h"
#include "hashtable.h"
#include <sys/stat.h>


/* struct definitions */

typedef struct maxNumAndDir
{
  char* pageDir;
  int maxNum;
  counters_t* counter;

} maxNumAndDir_t;

typedef struct docAndCount
{
  int docID;
  int count;

} docAndCount_t;

typedef struct container
{
  docAndCount_t* array;
  int index;
} container_t;

typedef struct moreCounters
{
  counters_t* counter1;
  counters_t* counter2;
} moreCounters_t;

/* function declarations */

static void parseArgs(const int argc, char* argv[]);
bool areOperatorsOkay(char** wordArray, int numWord);
int countWords(char* input);
void tokenize(char* input, int numWords, char** wordArray);
counters_t* iterateInput(char** wordArray, int numWord, char* pageDirectory, index_t* index);
void Union(counters_t* and, counters_t* or);
void unionHelper(void* arg, const int key, const int count);
void intersection(counters_t* and, counters_t* current);
void intersectionHelper(void* arg, const int key, const int count);
void sortMatches(counters_t* counter, char* pageDirectory);
void addToStruct(void* arg, const int key, const int count);
int compare(const void* thing1, const void* thing2);
void printArray(docAndCount_t* array, char* pageDirectory, int sizeOfArray);


int main(const int argc, char* argv[]) 
{
  //parse arguments and check for validity
  parseArgs(argc, argv);

  //set variables
  char* pageDirectory = argv[1];
  char* indexFilename = argv[2];
  counters_t* validated;

  //open indexer-made file and determine the number of words in it
  FILE* file = fopen(indexFilename, "r");
  if (file == NULL) {
    fprintf(stderr, "file from indexFilename is invalid\n");
    exit(1);
  }
  const int linesInFile = file_numLines(file);

  //make and load new index
  index_t* index = index_new(linesInFile);
  index_load(index, file);
  fclose(file);

  //parse user input
  char* input;
  
  //until input is null:
  while (1) {
    printf("query? ");

    //read input from user
    input = file_readLine(stdin);

    //break if input is null
    if (input == NULL) {
      printf("\n");
      break;
    }

    //count words in input
    int numWord = countWords(input);
    char* wordArray[numWord];

    //if countWords returns 0
    if (numWord == 0) {
      printf("no words found (or invalid character)\n");
      free(input);
      continue;
    }
  
    //split up input into individual words
    tokenize(input, numWord, wordArray);
    
    //if there are no operators in places there shouldn't be:
    if (!areOperatorsOkay(wordArray, numWord)) {
      fprintf(stderr, "query cannot start with an operator, contain two adjacent operators, or end with an operator\n");
      free(input);
      continue;
    }
    
    //print cleaned query
    printf("query: ");
    for (int i = 0; i < numWord; i ++) {
      printf("%s ", wordArray[i]);
    }
    printf("\n");

    //adding up points
    validated = iterateInput(wordArray, numWord, pageDirectory, index);

    //sorting matches
    sortMatches(validated, pageDirectory);

    //delete counter with points
    counters_delete(validated);

    //free(copiedInput);
    free(input);
  }

  //delete and clean up
  index_delete(index);

  // #ifdef MEMTEST
  //   mem_report(stdout, "index deleted\n");
  
  // #endif

  exit(0);

}


static void parseArgs(const int argc, char* argv[])
{
    //check for correct number of arguments
    if (argc != 3) {
        fprintf(stderr, "querier takes 2 arguments\n");
        exit(1);
    }

    //make sure argv[1] is a crawler directory
    if (!pagedir_validate(argv[1])) {
        fprintf(stderr, "pageDirectory not produced by crawler\n");
        exit(1);
    }

    //make sure argv[2] can be read
    FILE* file;
    if ((file = fopen(argv[2], "r")) == NULL) {
        fprintf(stderr, "indexFilename does not exist/is not readable\n");
        exit(1);
    }
    fclose(file);
}


bool areOperatorsOkay(char** wordArray, int numWord)
{
  //check to make sure first word is not and / or
  if (strcmp(wordArray[0], "and") == 0 || strcmp(wordArray[0], "or") == 0) {
    return false;
  }

  //check to make sure no two operators are adjacent
  for (int i = 0; i < numWord - 1; i++) {
    if ((strcmp(wordArray[i], "and") == 0) || (strcmp(wordArray[i], "or") == 0)) {
      if ((strcmp(wordArray[i+1], "and") == 0) || (strcmp(wordArray[i+1], "or") == 0)) {
        return false;
      }
    }
  }

  //check to make sure last word is not and / or
  if ((strcmp(wordArray[numWord - 1], "and") == 0) || (strcmp(wordArray[numWord - 1], "or") == 0)) {
    return false;
  }

  return true;
}

int countWords(char* input)
{
  bool midWord = false;
  int count = 0;
  char *pointer;

  //for each character:
  for (pointer = input; *pointer != '\0'; pointer++){

    //if it's a letter and not in the middle of a word:
    if (isalpha(*pointer) && !midWord) {
      count++;
      midWord = true;
    }

    //if it's a space:
    else if (isspace(*pointer)) {
      midWord = false;
    }

    //if it's not a space or a letter:
    else if (!isspace(*pointer) && !isalpha(*pointer)) {
      return 0;
    }
  }
  return count;
}

void tokenize(char* input, int numWords, char** wordArray)
{
  char*start = input;
  char*rest = input;

  //iterate through to split words
  for (int i =0; i < numWords; i++) {
    while (!isalpha(*start)) {
      start++;
    }
    rest = start;

    //while there are spaces:
    while (isalpha(*rest) != 0) {
      rest++;
    }
    *rest = '\0';
    wordArray[i] = start;

    //increment
    start = rest;
  }
}

counters_t* iterateInput(char** wordArray, int numWord, char* pageDirectory, index_t* index)
{
  char* word = wordArray[0];
  counters_t* and = counters_new();
  counters_t* or = counters_new();
  counters_t* current = counters_new();
  
  //add first word counter to "and"
  Union(index_get(index, word), and);

  //for next words:
  for (int i = 1; i < numWord; i ++) {
    word = wordArray[i];
    
    //if the word is or
    if (strcmp(word, "or") == 0 ) {

      //combine its score with whatever is in "and"
      Union(and, or); 

      //clear out "and"
      counters_delete(and);
      and = counters_new();
    }

    //if the word is not or / and
    else if (strcmp(word, "and") != 0) {
      
      //if the word does not exist in the index:
      if (index_get(index, word) == NULL) {
        counters_set(current, i, 0);
      }
    
      else {
        //combine the score from index into current
        Union(index_get(index, word), current);
      }

      //intersect the scores of current and "and"
      intersection(current, and);
    }
  }

  /* print statements from testing */

  // FILE* fp = fopen("testfile.txt", "w");
  // counters_print(current,fp);
  // counters_print(and, fp);

  //combine whatever is left in "and" and "or"
  Union(and, or);

  //clean up
  counters_delete(and);
  counters_delete(current);
  
  // counters_print(or, fp);
  // fclose(fp);

  return or;
}

void Union(counters_t* and, counters_t* or)
{
  counters_iterate(and, or, unionHelper);
}

/* helper function for Union */
void unionHelper(void* arg, const int key, const int count)
{
  counters_t* or = arg;

  if (arg == NULL) {
    fprintf(stderr, "null argument in unionHelper\n");
    exit(1);
  }

  //score for "and"
  int andCount = count;

  //score for "or"
  int orCount = counters_get(or, key);

  //merged score
  counters_set(or, key, andCount + orCount);
}

void intersection(counters_t* current, counters_t* and)
{
  //struct to track two counters
  moreCounters_t twoCounters;
  twoCounters.counter1 = current;
  twoCounters.counter2 = and;

  //call intersectionHelper on each item in counter "and"
  counters_iterate(and, &twoCounters, intersectionHelper);
}

/* helper function for intersection */
void intersectionHelper(void* arg, const int key, const int count)
{
  //struct to track two counters
  moreCounters_t* twoCounters = arg;
  counters_t* current = twoCounters->counter1;
  counters_t* and = twoCounters->counter2;

  if (arg == NULL) {
    fprintf(stderr, "null argument in intersectionHelper\n");
    exit(1);
  }
  
  //score for current
  int countCurr = counters_get(current, key);

  //score for "and"
  int countAnd = counters_get(and, key);
  
  //intersection of "and" and current
  if (countAnd > countCurr) {
    counters_set(and, key, countCurr);
  }
  else {
    counters_set(and, key, countAnd);
  }
}

void sortMatches_counter(void* arg, const int key, const int count)
{
  //counting how many matches there are
  if (count > 0) {
    int * docCounter = arg;
    (*docCounter)++;
  }
}

void sortMatches(counters_t* counter, char* pageDirectory) 
{
  int docCounter = 0;

  //counting how many matches there are
  counters_iterate(counter, &docCounter, sortMatches_counter);
  if (docCounter == 0) {
    printf("no matches found\n");
  }

  //get the size of docs
  docAndCount_t* docAndCount = malloc(sizeof(docAndCount_t) * docCounter);

  //struct holding array and index
  container_t container;
  container.array = docAndCount;
  container.index = 0;
  
  //adds objects to array
  counters_iterate(counter, &container, addToStruct);

  int sizeOfArray = container.index; //technically last index in array, not size

  //quicksort to sort array
  qsort(docAndCount, sizeOfArray, sizeof(docAndCount_t), compare);

  //prints out sorted array
  printArray(docAndCount, pageDirectory, sizeOfArray);

  //clean up
  free(docAndCount);

}

void addToStruct(void* arg, const int key, const int count)
{
  container_t* ctn = arg;
  docAndCount_t keys;
  docAndCount_t* array = ctn->array;
  keys.docID = key;
  keys.count = count;

  //if there has been a match, add it to the array structure
  if (count > 0) {
    array[ctn->index] = keys;
    ctn->index += 1;
  }

}

int compare(const void* thing1, const void* thing2)
{
  //returns <0 if thing1 has a bigger score than thing2
  //returns 0 if equal
  
  const docAndCount_t* key1 = thing1;
  const docAndCount_t* key2 = thing2;
  return key2->count - key1->count;
}

void printArray(docAndCount_t* array, char* pageDirectory, int sizeOfArray)
{

  //for word in array:
  for (int i = 0; i < sizeOfArray; i ++) {

    //get path to each file and open file
    char* filepath = malloc(100);
    sprintf(filepath, "%s/%d", pageDirectory, i+1);

    FILE* file = fopen(filepath, "r");

    //if the file is null, clean up
    if (file == NULL) {
      fprintf(stderr, "null file pointer\n");
      fclose(file);
      free(filepath);
      exit(1);
    }

    char* URL = file_readLine(file);

    //print out matches info
    printf("score: %d ",array[i].count);
    printf("docID: %d ",array[i].docID);
    printf("URL: %s\n",URL);

    //clean up
    fclose(file);
    free(filepath);
    free(URL);

  }
}
