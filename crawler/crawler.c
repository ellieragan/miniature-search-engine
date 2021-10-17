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


int main(const int argc, char* argv[]) {

  //initialize arguments
  char* seedURL = NULL;
  char* pageDirectory = NULL;
  int maxDepth = 0;
  
  parseArgs(argc, argv, &seedURL, &pageDirectory, &maxDepth);
  crawl(seedURL, pageDirectory, maxDepth);
  exit(0);
} 

/* parses arguments, checking to ensure that the program exits gracefully from invalid and missing arguments
 */
static void parseArgs(const int argc, char* argv[], char** seedURL, char** pageDirectory, int* maxDepth)
{
  //check for correct number of arguments
  if (argc < 4) {
    fprintf(stderr, "not enough arguments\n");
    exit(1);
  }

  //assign arguments
  *seedURL = argv[1];
  *pageDirectory = argv[2];
  *maxDepth = atoi(argv[3]); //i really thought this was supposed to have no pointer but it doesn't compile without one

  //normalizes URL (normalizeURL called inside of isInternalURL) and checks to see if it's internal
  if (isInternalURL(*seedURL) != true) {
    fprintf(stderr, "URL is not internal\n");
    exit(2);
    }
  
  //checks to see if directory is valid/readable
  if (pagedir_init(*pageDirectory) == false) {
    fprintf(stderr, "error with page directory\n");
    exit(3);
  }

  //checks to see if maxDepth is in range
  if (*maxDepth < min || *maxDepth > max) {
    fprintf(stderr, "maxDepth must be in the range [0, 10]");
    exit(5);
  }
}

/* pulls webpages from a bag, searches webpages for new URLS, adds them to a hashtable once they've been searched, and adds the new URLS to the bag to be searched in the future
 */
static void crawl(char* seedURL, char* pageDirectory, const int maxDepth) 
{
  
  //adds first website to hashtable and bag
  hashtable_t* hashtable = hashtable_new(slots);
  hashtable_insert(hashtable, seedURL, "");
  bag_t* bag = bag_new();

  char* newURL = malloc(strlen(seedURL) + 1);
  strcpy(newURL, seedURL);
  printf("%s is the newURL", newURL);
  webpage_t* webpage = webpage_new(newURL, min, NULL);
  bag_insert(bag, webpage);
  
  //begins pulling webpages from bag
  int ID = 0;
  webpage_t* extracted;
  while ((extracted = bag_extract(bag)) != NULL) {
    
    if (webpage_fetch(extracted)) {
      printf("%d fetched %s\n", webpage_getDepth(extracted), webpage_getURL(extracted));
      pagedir_save(extracted, pageDirectory, ++ID); 
      if (webpage_getDepth(extracted) < maxDepth) {
        pageScan(extracted, bag, hashtable);
      }
    }

    printf("ID is %d\n", ID);
    printf("url is %s\n", webpage_getURL(extracted));
    
    webpage_delete(extracted);

  }

  //removes hashtable and bag
  hashtable_delete(hashtable, NULL);
  bag_delete(bag, webpage_delete);
}

/*
 * assists crawl in adding unseen webpages to bag and seen webpages to hashtable
 */
static void pageScan(webpage_t* page, bag_t* pagesToCrawl, hashtable_t* pagesSeen)
{
  int pos = 0;
  char* nextURL;
  printf("%d reading %s\n", webpage_getDepth(page), webpage_getURL(page));

  //while there is a next URL to read:
  while ((nextURL = webpage_getNextURL(page, &pos)) != NULL) {
    printf("%d found %s\n", webpage_getDepth(page), nextURL);
    
    //normalize & check to see if internal:
    if (isInternalURL(nextURL)) {
      //if not already in hashtable:
      if ((hashtable_insert(pagesSeen, nextURL, ""))) {
          int currDepth = webpage_getDepth(page);
          webpage_t* webpage = webpage_new(nextURL, currDepth + 1, NULL);
          bag_insert(pagesToCrawl, webpage);
          printf("%d added %s\n", webpage_getDepth(page), nextURL);
      }
      else {
        free(nextURL);
      }
    }
    else {
      free(nextURL);
    }
  }
}


