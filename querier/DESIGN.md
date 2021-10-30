# Design spec for querier
## Ellie Boyd

## User interface
The querier takes exactly two arguments from the command line:
`./querier pageDirectory indexFilename`
where pageDirectory is a crawler-made directory and indexFilename is a path to an index-made file.

After being run, the querier also provides a prompt to the user to get input

## Inputs and outputs
The querier reads an index file produced by an indexer and page files produced by a crawler and outputs responses to searches input by the user on the command line

## Functional decomposition into modules
We anticipate the following modules:

1. main, which initializes functions
2. parseArgs, which parses arguments
5. tokenize, which splits up the words from the input and handles them
6. iterateInput, which calculates scores for the words
7. Union, which handles the "or"s
8. intersection, which handles the "and"s
9. sortMatches, which sorts the results from iterateInput
10. printArray, which prints the sorted list of matches

## Pseudo code for logic/algorithmic flow
The querier will run as follows:

`parses the command line, validate parameters, and initialize other modules
creates new index and load index from indexFilename into that index
calls tokenize and areOperatorsOkay
calls indexIterate
sorts the resulting array
deletes index
exits
`

where `tokenize`:

`iterates through to split words
    continues incrementing while there are spaces
    inserts null characters at the end of words
    inserts split words into an array
`

where `iterateInput`:

`adds first word counter to null
for next words:
if the word is or:
    combine its score with whatever is in "and"
    clear out "and"
if the word is not or / and:
    intersect the scores of current and "and"
combine "and" and "or"
clean up
return "or"
`
where `Union`:

`iterates through the counters "and" and "or" and adds together the scores in them using a helper function
`

where `intersection`:

`iterates through the counters "and" and "current" and saves to "and" the minimum of the two scores with the help of a helper function
`

where `sortMatches`:

`counts how many matches there are using a helper function
uses quicksort to sort match array from highest to lowest score
prints out sorted array
clean up
`

where `printArray`:

`iterates through the results from sortMatches and prints them to stdout with the score, docID, and URL
`

