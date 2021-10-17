/* pagedir.h - header file for CS50 'pagdir' 
 *
 * the 'pagdir' module writes a page to the pageDirectory in crawler and marks that directory as a crawler-produced pageDirectory.
 *
 * Ellie Boyd
 * Oct 14 2021
 */

#include <stdio.h>

/******** pagedir_init ********/
/* inserts a .crawler file into the directory given by the user
 *
 * Caller provides:
 * a const char* filepath, pageDirectory
 *
 * We return:
 *  true if successful, false if error
 */

bool pagedir_init(const char* pageDirectory);


/******** pagedir_save ********/
/* saves a webpage and its ID to the appropriate file 
 *
 * Caller provides:
 * a pointer to a webpage page, a const char* filepath pageDiretory, and an integer docID.
 *
 * We return:
 * nothing
 */

void pagedir_save(const webpage_t* page, const char* pageDirectory, const int docID);
