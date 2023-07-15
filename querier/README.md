# CS50 querier
# Ellie Boyd
# Oct 20 2021

### Usage

To build `querier`, run `make`.

To clean up, run `make clean`.

To test, run `make test`.

To check valgrind on a single sample test case, run `make valgrind`.

It includes:
```c
static void parseArgs(const int argc, char* argv[]);
bool areOperatorsOkay(char** wordArray, int numWord);
int countWords(char* input);
void tokenize(char* input, int numWords, char** wordArray);
counters_t* iterateInput(char** wordArray, int numWord, char* pageDirectory, index_t* index);
void Union(counters_t* and, counters_t* or);
void unionHelper(void* arg, const int key, const int count);
void intersection(counters_t* and, counters_t* current);
void intersectionHelper(void* arg, const int key, const int count);
void sortMatches(counters_t* counter, char* pageDirectory);
void addToStruct(void* arg, const int key, const int count);
int compare(const void* thing1, const void* thing2);
void printArray(docAndCount_t* array, char* pageDirectory, int sizeOfArray);
```

### Assumptions

none not specified in requirements & design

### Files

* `Makefile` - the compilation and testing procedures
* `querier.c` - the querier module
* `testing.sh` - list of test commands called by Makefile
* `testing.out` - an output location for the test commands called by Makefile
* `IMPLEMENTATION.md` - implementation of querier
* `DESIGN.md` - design of querier
* `.gitignore` - to hide unwanted files




