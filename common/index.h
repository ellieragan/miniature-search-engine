/*
 * index.h - header file for index module
 *
 * an index maps words to (docID, count) pairs, where each count represents the number of occurrences of the given word in the given document. It ignores words with fewer than three characters, and "normalizes" the word before indexing. (Here, "normalize" means to convert all letters to lower-case.)
 *
 * Ellie Boyd
 * Oct 17 2021
 */

#ifndef __INDEX_H
#define __INDEX_H

#include <stdio.h>
#include <stdbool.h>

/******** global types ********/
typedef struct index index_t;

/******** index_new ********/
/* creates a new, empty index
 *
 * Caller provides:
 *  number of slots to be used in the index
 *
 * We return:
 *  pointer to the new index or NULL if error
 *
 */
index_t* index_new(const int num_slots);

/******** index_insert ********/
/* adds new words to index if they don't already exist and increments the counter if the word does exist
 *
 * Caller provides:
 *  pointer to an index, char* word to insert, and the int docID of the file in which the word was found
 *
 * We return:
 *  void
 *
 */
bool index_insert(index_t* index, const char* word, const int docID);

/******** index_delete ********/
/* deletes an index object 
 *
 * Caller provides:
 *  index object to delete, helper delete function
 *
 * We return:
 *  void
 *
 */
void index_delete(index_t* index);


/******** index_save ********/
bool index_save(index_t* index, const char* filename);



#endif
