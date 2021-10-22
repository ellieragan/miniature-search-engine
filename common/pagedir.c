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

webpage_t* pagedir_load(char* pageDirectory, int docID)
{
  char* combinedFilepath = mem_malloc(strlen(pageDirectory) + 12);
  sprintf(combinedFilepath, "%s/.crawler", pageDirectory);
  FILE* file = fopen(combinedFilepath, "r");
  free(combinedFilepath);
  if (file == NULL) {
    return NULL;
  }
  fclose(file);
  char* pageLabeledWithNumber = mem_malloc(strlen(pageDirectory) + 9);
  sprintf(pageLabeledWithNumber, "%s/%d", pageDirectory, docID);
  FILE* file2 = fopen(pageLabeledWithNumber, "r");
  free(pageLabeledWithNumber);
  if (file2 == NULL) {
    return NULL;
  }
  
  char* URL = file_readLine(file2);
  char* depthChar = file_readLine(file2);
  char* HTML = file_readLine(file2);
  int depth = atoi(depthChar);
  webpage_t* page = webpage_new(URL, depth, HTML);
  fclose(file2);
  

  return page;
}
  
