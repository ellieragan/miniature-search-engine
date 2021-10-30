### Implementation for Querier
# Ellie Boyd

## Data structures

Counters structures are used to map frequency of word occurences in files, and a few other structures are defined based on whatever was needed to hold multiple other structures (counters etc.) so that they could be passed into a helper function for counters_iterate

## Control flow

The querier is implemented in querier.c with three primary functions.

#main
parses arguments, verifies that all are valid

#tokenize
splits up user input into words, calls helper functions to check and make sure that those words have no invalid characters and that there are no operators next to each other, etc

#iterateInput
the primary logic of the program; takes the input words and works through them by calculating scores around "and" words first before moving on to handling the "or" sections of the input. uses an "and" counter and an "or" counter to achieve this out-of-order handling

## libraries:

libraries used are common.a and libcs50.a


## function prototypes:

#querier
`
int main(const int argc, char* argv[]);
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
`

## Error handling

Command line parameters are checked, as are parameters called by functions. I also used the ifdef memory test in a couple of places

## Testing plan

testing.sh tests things like command line errors, incorrect input values for functions, etc. It also calls the function a couple of times using valgrind. fuzzquery was provided for testing purposes but I did not include it in testing.sh. I did most of my testing by reading through the smaller crawler files provided and checking manually to make sure that using a variety of kinds of input gave the expected output based on what the files contained.
