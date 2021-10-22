/* indexer.c
 * takes parameters pageDirectory and indexFilename
 * cs50 
 * Ellie Boyd
 * Oct 17 2021
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "webpage.h"
#include "pagedir.h"
#include "index.h"
#include "word.h"


/* global variables */

static index_t* indexBuild(char* pageDirectory);
static void indexPage(webpage_t* page, const int docID, index_t* index);
const int slots = 200; 


int main(const int argc, char* argv[]) 
{

  //check for correct number of arguments
  if (argc < 3) {
    fprintf(stderr, "not enough arguments\n");
    exit(1);
  }

  //assign arguments
  char* pageDirectory = argv[1];
  char* indexFilename = argv[2];

  //call indexBuild
  index_t* index = indexBuild(pageDirectory);

  //write index into a file
  index_save(index, indexFilename);

  //delete index
  index_delete(index);

  exit(0);
}

/* builds an in-memory index from webpage files it finds in the pageDirectory
 */
index_t* indexBuild(char* pageDirectory) 
{
  index_t* index = index_new(slots);
  
  webpage_t* page = NULL;
  int i=0;
  while ((page = pagedir_load(pageDirectory, i)) != NULL) {
    indexPage(page, i, index);
    webpage_delete(page);
    i++;
  }
  return index;
}


/* builds an in-memory index from webpage files it finds in the pageDirectory
 */
void indexPage(webpage_t* page, const int docID, index_t* index) 
{
  int pos = 0;
  char* word;
  if (webpage_fetch(page) == false) {
    fprintf(stderr, "error fetching html");
    exit(6);
  }
  while ((word = webpage_getNextWord(page, &pos)) != NULL) {
    if (strlen(word) >= 3) {
      word = normalizeWord(word);
      index_insert(index, word, docID);
    }
    free(word);
  } //free(word);
}

