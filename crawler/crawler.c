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
#include "bag.h"
#include "hashtable.h"
#include <string.h>


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
  int maxDepth = atoi(argv[3]); //possibly initialize to 0
  parseArgs(argc, argv, &seedURL, &pageDirectory, &maxDepth);
  crawl(seedURL, pageDirectory, maxDepth);
  exit(0);
} 

static void parseArgs(const int argc, char* argv[], char** seedURL, char** pageDirectory, int* maxDepth)
{
  
  if (argc < 4) {
    fprintf(stderr, "%d", argc);
    fprintf(stderr, "not enough arguments");
    exit(1);
  }
  for (int i=0; i<argc; i ++) {
    if (argv[i] == NULL) {
      fprintf(stderr, "%s is null\n", argv[i]);
      exit(2);
    }
  }
  
  char* fixedURL = normalizeURL(*seedURL);
  
  if (isInternalURL(fixedURL) != true) {
    fprintf(stderr, "%s is not an internal URL\n", fixedURL);
    exit(3);
  }
  //free(fixedURL); //get rid of????

  if (pagedir_init(*pageDirectory) == false) {
    fprintf(stderr, "error with page directory\n");
    exit(4);
  }

  //check to see if atoi argv[3] is 0 & if strcmp between argv[3] and 0 says they're the same

  if (*maxDepth < min || *maxDepth > max) {
    fprintf(stderr, "maxDepth must be in the range [0, 10]");
    exit(5);
}

}

static void crawl(char* seedURL, char* pageDirectory, const int maxDepth) 
{
  hashtable_t* hashtable = hashtable_new(slots);
  //mem_assert
  hashtable_insert(hashtable, seedURL, "");
  bag_t* bag = bag_new();
  //mem_assert
  webpage_t* webpage = webpage_new(seedURL, min, NULL);
  bag_insert(bag, webpage);
  int ID = 0;
  webpage_t* extracted;
  while ((extracted = bag_extract(bag)) != NULL) {
    if (webpage_fetch(extracted)) {
      printf("%d Fetched: %s\n", webpage_getDepth(extracted), webpage_getURL(extracted));
      pagedir_save(extracted, pageDirectory, ++ID);
      if (webpage_getDepth(extracted) < maxDepth) {
        pageScan(extracted, bag, hashtable);
      }
    }
    printf("ID is %d\n", ID);
    printf("url is %s\n", webpage_getURL(extracted));
    

    webpage_delete(extracted);

  }
  hashtable_delete(hashtable, NULL);
  bag_delete(bag, webpage_delete);

//don;t forget about mem_assert and mem_malloc_assert
}

static void pageScan(webpage_t* page, bag_t* pagesToCrawl, hashtable_t* pagesSeen)
{
  int pos = 0;
  char* nextURL;
  char* normalized;
  printf("%d Scanning: %s\n", webpage_getDepth(page), webpage_getURL(page));

  while ((nextURL = webpage_getNextURL(page, &pos)) != NULL) {
    printf("%d Found: %s\n", webpage_getDepth(page), nextURL);
    normalized = normalizeURL(nextURL);
    //free(nextURL);
    if (normalized != NULL) {
      if (isInternalURL(normalized)) {
        //if (hashtable_insert(pagesSeen, normalized) == NULL){
          //char* newURL = malloc(strlen(normalized) + 1);
          //strcpy(newURL, normalized);
          //printf("URL is %s\n", newURL);

          if ((hashtable_insert(pagesSeen, normalized, ""))) {
            int currDepth = webpage_getDepth(page);
            webpage_t* webpage = webpage_new(normalized, currDepth + 1, NULL); //curDepth + 1
              //if(webpage != NULL){
              bag_insert(pagesToCrawl, webpage);
              printf("%d Added: %s\n", webpage_getDepth(page), normalized);
              //}
        
          }
          else {
            free(normalized);
          }
      }
      else {
        free(normalized);
      }
    }
    else {
      free(normalized);
    }
    free(nextURL);
  }
}


