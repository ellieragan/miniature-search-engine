//word.c
//ellie boyd
//oct 19

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include "word.h"

/* takes a word and makes it all lowercase*/

char* normalizeWord(char* word) 
{
  if (word != NULL) {
    for (char* letter=word; *letter != '\0'; letter++) {
      *letter=tolower(*letter);
    }
  }
  return word;
}


