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
#include "counters.h"
#include "mem.h"
#include "hashtable.h"


/* global variables */

static index_t* indexBuild(char* pageDirectory);
static void indexPage(webpage_t* page, const int docID, index_t* index);
const int slots = 200; 


int main(const int argc, char* argv[]) 
{

  //check for correct number of arguments
  if (argc != 3) {
    fprintf(stderr, "indexer takes 2 arguments\n");
    exit(1);
  }

  //assign arguments
  char* pageDirectory = argv[1];
  char* indexFilename = argv[2];

  //call indexBuild
  index_t* index;
  
  index = indexBuild(pageDirectory);

  //open file
  if (indexFilename == NULL) {
    fprintf(stderr, "indexFilename does not exist\n");
    exit(1);
  }
  FILE* file = fopen(indexFilename, "w");

  //write index into a file
  if (file == NULL) {
    fprintf(stderr, "invalid indexFilename\n");
    fclose(file);
    exit(1);
  }
  
  index_save(index, file);
  fclose(file);

  //delete index
  index_delete(index);

  exit(0);
}

/* builds an in-memory index from webpage files it finds in the pageDirectory
 */
index_t* indexBuild(char* pageDirectory) 
{
  index_t* index = index_new(slots); //new index
  webpage_t* page = NULL;
  int i=1;

  // //check to see if directory was made by crawler
  // if (pagedir_validate(pageDirectory) == false) {
  //   fprintf(stderr, "invalid pageDirectory\n");
  //   free(page);
  //   exit(1);
  //}

  // char* pageLabeledWithNumber = mem_malloc(strlen(pageDirectory) + 9);
  // sprintf(pageLabeledWithNumber, "%s/%d", pageDirectory, i);
  // FILE* file;
  // while ((file = fopen(pageLabeledWithNumber, "r")) != NULL) {
  //   page = pagedir_load(file, i);
  //   indexPage(page, i, index);
  //   i++;
  //   sprintf(pageLabeledWithNumber, "%s/%d", pageDirectory, i);
  //   fclose(file);
  // }

  // free(pageLabeledWithNumber);

  while ((page = pagedir_load(pageDirectory, i)) != NULL) { //new webpage
    indexPage(page, i, index); 
    webpage_delete(page); 
    i++;
  }
  free(page);

  return index;
}


/* builds an in-memory index from webpage files it finds in the pageDirectory
 */
void indexPage(webpage_t* page, const int docID, index_t* index) 
{
  int pos = 0;
  char* word;

  while ((word = webpage_getNextWord(page, &pos)) != NULL) {
    if (strlen(word) >= 3) {
      word = normalizeWord(word); //make lowercase
      index_insert(index, word, docID); //add to index
    }
    free(word);
  }
}

