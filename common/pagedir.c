/* pagedir.c 
 * to handle pagesaver
 * Ellie Boyd
 * Oct 13 2021
 */

#include <stdio.h>
#include <stdlib.h>
#include "../libcs50/webpage.h"
#include "pagedir.h"
#include "../libcs50/file.h"
#include <string.h>
#include "../libcs50/mem.h"


/******** pagedir_init ********/
/* see pagedir.h for details */

bool pagedir_init(const char* pageDirectory) 
{ 
  
  //concatenating pathname
  char combinedName[100];
  sprintf(combinedName, "./%s/.crawler", pageDirectory);

  //inserting .crawler
  FILE* dotCrawler;
  dotCrawler = fopen(combinedName, "w");
  if (dotCrawler == NULL) {
    return false;
  }

  fclose(dotCrawler);
  return true;

}

/******** pagedir_save ********/
/* see pagedir.h for details */

void pagedir_save(const webpage_t* page, const char* pageDirectory, const int docID)
{
  //concatenating pathname
  char* combinedURL = malloc(100);
  sprintf(combinedURL, "./%s/%d", pageDirectory, docID);
  
  if (combinedURL != NULL){
  FILE *file;
  file = fopen(combinedURL, "w");
  free(combinedURL);

  if (file == NULL || page == NULL) {
    fprintf(stderr, "something went wrong with the output file pathname\n");
    exit(1);
  }

  //writing to file
  fprintf(file, "%s\n", webpage_getURL(page));
  fprintf(file, "%d\n", webpage_getDepth(page));
  fprintf(file, "%s\n",webpage_getHTML(page));

  fclose(file);

  }
}

/******** pagedir_load ********/
/* see pagedir.h for details */

webpage_t* pagedir_load(char* pageDirectory, int docID) //char* pageDirectory
{
  //creates path to a potential .crawler file
  char* combinedFilepath = mem_malloc(strlen(pageDirectory) + 12);
  sprintf(combinedFilepath, "%s/.crawler", pageDirectory);
  FILE* file1 = fopen(combinedFilepath, "r");
  free(combinedFilepath);

  //if file does not exist, then the directory must not have been made by a crawler
  if (file1 == NULL) {
    return NULL;
  }

  //otherwise, create path to each file made by crawler
  fclose(file1);
  

  char* pageLabeledWithNumber = mem_malloc(strlen(pageDirectory) + 9);
  sprintf(pageLabeledWithNumber, "%s/%d", pageDirectory, docID);
  FILE* file2 = fopen(pageLabeledWithNumber, "r");

  if (file2 == NULL) {
    fprintf(stderr, "cannot read file %s\n", pageLabeledWithNumber);
    free(pageLabeledWithNumber);
    return NULL;
  }

  free(pageLabeledWithNumber);
  
  //read through file to get URL, depth, and HTML
  char* URL = file_readLine(file2);
  char* depthChar = file_readLine(file2);
  char* HTML = file_readFile(file2);
  int depth = atoi(depthChar);

  //create webpage; clean up
  webpage_t* page = webpage_new(URL, depth, HTML);

  fclose(file2);
  free(depthChar);

  return page;
}

bool pagedir_validate(char* pageDirectory) 
{
  //creates path to a potential .crawler file
  char* combinedFilepath = mem_malloc(strlen(pageDirectory) + 12);
  sprintf(combinedFilepath, "%s/.crawler", pageDirectory);
  FILE* file = fopen(combinedFilepath, "r");
  free(combinedFilepath);
  

  //if file does not exist, then the directory must not have been made by a crawler
  if (file == NULL) {
    //fclose(file);
    return false;
  }

  fclose(file);
  return true;
}



  
