/* indextest.c
 * Ellie Boyd
 * Oct 21 2021
 * tests index
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../libcs50/webpage.h"
#include "../libcs50/hashtable.h"
#include "../libcs50/counters.h"
#include "../common/index.h"

int main(const int argc, const char *argv[]) {

  if (argc < 3) {
    fprintf(stderr, "not enough arguments\n");
    exit(1);
  }

  if (argv[1] == NULL || argv[2] == NULL) {
    fprintf(stderr, "null argument");
  }

  //assign arguments
  const char* oldIndexFilename = argv[1]; //file produced by indexer
  const char* newIndexFilename = argv[2]; //file into which index should be written

  index_t* index = index_new(500); //new index

  FILE* oldfile;
  oldfile = fopen(oldIndexFilename, "r"); //open file to read from
  index_load(index, oldfile); //put into index
  fclose(oldfile);

  FILE* newfile;
  newfile = fopen(newIndexFilename, "w"); //open file to write into
  index_save(index, newfile); //write into new file
  fclose(newfile); 

  index_delete(index);

}









