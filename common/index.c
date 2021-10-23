/*
 * index.c - CS50 index module
 *
 * see index.h for more information
 *
 * Ellie Boyd
 * Oct 17 2021
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "index.h"
#include "../libcs50/hashtable.h"
#include "../libcs50/counters.h"
#include "../libcs50/mem.h"

//definition
typedef struct index {
    int num_slots;
    hashtable_t* hashtable;
} index_t;


/******** helper functions ********/
void delete(void* item) 
{
  counters_t* counters = item;
  if (counters != NULL) {
    counters_delete(counters);
  }
}

//recursive helper function called by iterateAgain
void helpsCounter(void* arg, const int key, const int count) 
{
  if (arg == NULL) {
    fprintf(stderr, "null argument in helpsCounter");
    exit(1);
  }

  printf("made it into helpsCounter\n");
  fflush(stdout);
  FILE* fp = arg;
  fprintf(fp, "%d %d ", key, count);

}

//helper function called by index_save
void iterateAgain(void* arg, const char* key, void* item)
{
  if (arg == NULL || key == NULL || item == NULL) {
    fprintf(stderr, "null argument passed to iterateAgain");
    exit(1);
  }

  printf("made it into iterateAgain\n");
  fflush(stdout);
  FILE* fp = arg;
  fprintf(fp, "%s ", key);

  counters_t* counter = item;
  counters_iterate(counter, fp, helpsCounter);
    
  fprintf(fp, "\n");
}

/******** index_new() ********/
/* see index.h for description */
index_t*
index_new(const int num_slots)
{
  //allocate memory
  index_t* index = malloc(sizeof(index_t));
  index -> num_slots = num_slots; 
  
  if (index == NULL) {
    return NULL;
  }

  index -> hashtable = hashtable_new(num_slots);
  return index;
}

/******** index_insert() ********/
/* see index.h for description */
bool
index_insert(index_t* index, const char* word, const int docID) 
{
  counters_t* counter;
  if ((counter = hashtable_find(index->hashtable, word)) != NULL) {
    counters_add(counter, docID);
  }
  else {
      counter = counters_new();
      counters_add(counter, docID);
      hashtable_insert(index->hashtable, word, counter);
  }
  return true;
}

/******** index_delete() ********/
/* see index.h for description */
void
index_delete(index_t* index)
{
  if (index != NULL) {
  hashtable_delete(index->hashtable, delete); //->hashtable
  
  }
}

/******** index_save ********/
/* see index.h for description */
bool
index_save(index_t* index, FILE *file) 
{
  
  if (index == NULL || file == NULL) {
    fprintf(stderr, "null parameter");
    return false;
  }
  
  //recursively enter hashtable
  hashtable_iterate(index->hashtable, file, iterateAgain); //please see README.md for notes about this line of code because it seems to be ruining the entire rest of my program
  return true;

}



