/* querier.c
 * takes parameters pageDirectory and indexFilename where pageDirectory is the pathname of a directory produced by the crawler and indexFilename is the pathname of a file produced by the indexer
 * cs50
 * Ellie Boyd
 * Oct 24 2021
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "webpage.h"
#include "pagedir.h"
#include "index.h"
#include "file.h"
#include "word.h"
#include "counters.h"
#include "mem.h"
#include "hashtable.h"

static void parseArgs(const int argc, char* argv[]);
char* parseInput(char* input);

int main(const int argc, char* argv[]) 
{
  //parse arguments and check for validity
  parseArgs(argc, argv);

  //set variables
  char* pageDirectory = argv[1];
  char* indexFilename = argv[2];

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

  //begin taking stdin
  char* input = mem_malloc(sizeof(file_readLine(stdin)));
  input = file_readLine(stdin);
  if ((strcmp("", input) == 0) || input == NULL) { //if line is empty or EOF is reached without a line being read:
    free(input);
    exit(1);
  }

  input = parseInput(input);

  //delete index and clean up
  index_delete(index);

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
}

char* parseInput(char* input)
{
  input = normalizeWord(input);
  fprintf(stdout, "%s\n", input);
  free(input);
  return NULL;
}


