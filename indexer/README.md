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


