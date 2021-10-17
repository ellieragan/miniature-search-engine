/* pagedir.c 
 * to handle pagesaver
 * Ellie Boyd
 * Oct 13 2021
 */

#include <stdio.h>
#include <stdlib.h>
#include "../libcs50/webpage.h"
#include "pagedir.h"


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
