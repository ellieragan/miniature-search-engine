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
  char* oldIndexFilename = argv[1]; //file produced by indexer
  char* newIndexFilename = argv[2]; //file into which index should be written

  index_t* index = index_new(500); //new index
  index_load(index, oldIndexFilename); //put into index
  FILE* fp;
  fp = fopen(newIndexFilename, "w"); //file pointer to write into
  index_save(index, fp); //write into new file
  index_delete(index);
}









