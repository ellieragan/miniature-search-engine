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
//#include "../libcs50hash.h"
//#include "set.h"
#include "../libcs50/mem.h"

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

void helpsCounter(void* arg, const int key, const int count) 
{
  FILE* fp = arg;
  fprintf(fp, "%d %d ", key, count);
}

void iterateAgain(void* arg, const char* key, void* item)
{
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
  index_t* index = malloc(sizeof(index_t));
  index -> num_slots = num_slots;
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
  hashtable_delete(index->hashtable, delete);
}

/******** index_save ********/
/* see index.h for description */
bool
index_save(index_t* index, const char* filename) 
{
  if (index == NULL || filename == NULL) {
    return false;
  }

  FILE* file = fopen(filename, "w");
  if (file == NULL) {
    return false;
  }

  hashtable_iterate(index->hashtable, file, iterateAgain);
  fclose(file);
  return true;

}









