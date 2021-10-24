### Implementation for Indexer
# Ellie Boyd

## Data structures

Hashtable is used to create an index, and counters structures are used to map frequency of word occurences in files

## Control flow

The indexer is implemented in indexer.c with three functions.

#main
parses arguments, opens the file to be written into, makes an index using indexBuild, and writes that index into a file before closing the file and deleting the index

#indexBuild
creates a new index and a null webpage, and then calls `pagedir_load` to load information into the webpage before calling indexPage on it. It then deletes the page and returns and index

#indexPage
gets words from a webpage, checks to see if the word is 3 or more characters, makes the word all lowercase, and inserts it into the index (`index_insert` contains all of the checks to see if the word already exists anywhere, and if it exists in a counter with that specific file, incrementing the counter if so and otherwise creating a new entry for the new file or new word)

## Other modules

#pagedir
handles a couple of functions from crawler in addition to a new one responsible for checking to see if a file path contains a .crawler file, reading crawler output, and creating a webpage out of it.

Pseudocode for `pagedir.load`:

`create the pathname for the .crawler file to see if it is present
create the pathname for the crawler produced numerically named files
read each line of a file with the given docID and assign it to variables for URL, depth, and HTML
create a webpage with those variables`

## libraries:

libraries used are common.a and libcs50.a


##function prototypes:

#indexer
`int main(const int argc, char* argv[]);
index_t* indexBuild(char* pageDirectory);
void indexPage(webpage_t* page, const int docID, index_t* index);
`

#pagedir
`bool pagedir_init(const char* pageDirectory);
void pagedir_save(const webpage_t* page, const char* pageDirectory, const int docID);
webpage_t* pagedir_load(char* pageDirectory, int docID);
`

## Error handling

Command line parameters are checked, as are parameters called by functions and things such as opened files and allocated memory

## Testing plan

testing.sh tests things like command line errors, incorrect input values for functions, etc. Indextest is intended to test the functionality of index itself by building an index object from an index file and then rewriting the file from the index object.
