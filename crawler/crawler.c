/* crawler.c
 * takes three arguments from the command line: seedURL, pageDirectory, and maxDepth
 * cs50
 * Ellie Boyd
 * Oct 11, 2021
 */

#include <stdio.h>
#include <stdlib.h>
#include "webpage.h"
#include "pagedir.h"

/* global variables */
static const int min = 0;
static const int max = 10;
static const int slots = 200;
static void parseArgs(const int argc, char* argv[], char** seedURL, char** pagedirectory, int* maxDepth);
static void crawl(char* seedURL, char* pageDirectory, const int maxDepth);
static void pageScan(webpage_t* page, bag_t* pagesToCrawl, hashtable_t* pagesSeen);


int main(int argc, char* argv[]) {
  char* seedURL = argv[1];
  char* pageDirectory = argv[2];
  int maxDepth = atoi(argv[3]);
  parseArgs(argc, argv, &seedURL, &pageDirectory, &maxDepth);
  crawl(&seedURL, &pageDirectory, &maxDepth);
  exit(0);
} 

static void parseArgs(const int argc, char* argv[], char** seedURL, char** pagedirectory, int* maxDepth)
{
  if (argc < 4) {
    fprintf(stderr, "not enough arguments");
    exit(1);
  }
  for (i=0; i<argc; i ++) {
    if (argv[i] == NULL) {
      fprintf(stderr, "%s is null", argv[i]);
      exit(2);
    }
  }
  char* fixedURL = normalizeURL(*seedURL);
  if (isInternalURL(&fixedURL) != true) {
    fprintf(stderr, "%s is not an internal URL", &fixedURL);
    exit(3);
  }

  if (pagedir_init(*pageDirectory) == false) {
    fprintf(stderr, "error with page directory");
    exit(4);

  if (*maxDepth < min || *maxDepth > max) {
    fprintf(stderr, "maxDepth must be in the range [0, 10]");
}

static void crawl(char* seedURL, char* pageDirectory, const int maxDepth) 
{
  hashtable_t* hashtable = hashtable_new(slots);
  hashtable_insert(hashtable, seedURL, "");
  bag_t* bag = bag_new(void);
  webpage_t* webpage = webpage_new(seedURL, min, NULL);
  bag_insert(bag, webpage);
  while ((webpage_t* extracted = bag_extract(bag)) != NULL) {
    if (webpage_fetch(extracted)) {
      pagedir_save(extracted);
      if (webpage_getDepth(extracted) < maxDepth) {
        pageScan(extracted, bag, hashtable);
      }
    }
    webpage_delete(extracted);
  }
  hashtable_delete(hashtable, void (*itemdelete)(void* item));
  bag_delete(bag, void (*itemdelete)(void* item));

//don;t forget about mem_assert and mem_malloc_assert
}

static void pageScan(webpage_t* page, bag_t* pagesToCrawl, hashtable_t* pagesSeen)
{
  int pos = 0;
  while ((char* nextURL = webpage_getNextURL(page, &pos)) != NULL) {
    if (isInternalURL(nextURL)) {
      if ((hashtable_insert(pagesSeen, nextURL, "") != false)) {
        int currDepth = webpage_getDepth(nextURL);
        webpage_t* webpage = webpage_new(nextURL, &currDepth, NULL);
        bag_insert(*pagesToCrawl, webpage);
      }
    }
    free(nextURL);
  }
}




