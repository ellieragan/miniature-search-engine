# CS50 crawler
# Ellie Boyd
# Oct 20 2021

### Usage

To build `indexer`, run `make`.

To clean up, eun `make clean`.

To test, run `make test`.

To check valgrind on a single sample test case, run `make valgrind`.

It includes:
```c
int main(const int argc, char* argv[]);
static index_t* indexBuild(char* pageDirectory);
static void indexPage(webpage_t* page, const int docID);
```

### Assumptions

none not specified in requirements & design

### Files

* `Makefile` - the compilation and testing procedures
* `indexer.c` - the indexer module
* `testing.sh` - list of test commands called by Makefile
* `testing.out` - output from testing.sh
* `indextest.c` - test for indexer.c
* `IMPLEMENTATION.md` - implementation of indexer
* `.gitignore` - to hide unwanted files

### known bugs:

A couple of bugs I noticed are as follows:
First, my code does not recognize when a file to be written into is not supposed to be written into and exits 0 anyway. Same thing for every other test, even though I put checking statements into my code to make sure these things were valid and returning non-0 if they weren't, they are clearly not doing what they're supposed to. 
Second, my while loop that reads crawler-made files always goes one step too far and tries to read a number file one too big and then says that it can't read the file but it still exits 0. I don't know what the deal is. Please tell me how to fix these things so they don't ruin my entire search engine later on


