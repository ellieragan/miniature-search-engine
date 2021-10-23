/* 
 * word.h - header file for word module
 *
 * Ellie Boyd
 * Oct 19 2021
 */

#ifndef __WORD_H
#define __WORD_H

#include <stdio.h>

/******** normalizeWord ********/
/* makes all words in a word lowercase
 *
 * Caller provides:
 *  pointer to a word
 *
 * We return:
 *  the word, but lowercase
 */
char* normalizeWord(char* word);

#endif
