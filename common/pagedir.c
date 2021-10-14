/* pagedir.c 
 * to handle pagesaver
 * Ellie Boyd
 * Oct 13 2021
 */

/******** pagedir_init ********/
/* see pagedir.h for details */

bool pagedir_init(const char* pageDirectory) 
{
  sprintf(combinedName, "./%c/.crawler", pageDirectory);
  FILE* dotCrawler;
  dotCrawler = fopen(combinedName, "w");
  fclose(dotCrawler);

}

/******** pagedir_save ********/
/* see pagedir.h for details */

void pagedir_save(const webpage_t* page, const char* pageDirectory, const int docID)
{
  sprintf(combinedURL, "./%c/%d", pageDirectory, docID);
  FILE *file;
  file = fopen(combinedURL, "w");
  if (file == NULL) {
    fprintf(stderr, "something went wrong with the output file pathname");
    exit(1);
  }

  fprintf(file, "%s\n", webpage_getURL(page));
  fprintf(file, "%d\n", webpage_getDepth(page));
  fprintf(file, page->html);

  fclose(file);

}
