# CS50 crawler
# Ellie Boyd
# Oct 16 2021

### Usage

To build `crawler`, run `make`. 

To clean up, run `make clean`.

To test, run `make test`.

It includes:
```c
int main(const int argc, char* argv[]);
static void parseArgs(const int argc, char* argv[], char** seedURL, char** pageDirectory, int* maxDepth);
static void crawl(char* seedURL, char* pageDirectory, const int maxDepth);
static void pageScan(webpage_t* page, bag_t* pagesToCrawl, hashtable_t* pagesSeen);
```

### Assumptions

I assumed that the user input either nothing or an integer for the maxDepth, rather than a char or string of chars

### Files

* `Makefile` - the compilation and testing procedures
* `crawler.c` - the crawler module
* `testing.sh` - list of tests called by Makefile


 
