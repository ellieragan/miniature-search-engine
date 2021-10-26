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

1. *main,* which initializes functions
2. *parseArgs,* which parses arguments
3. *

## Pseudo code for logic/algorithmic flow
The querier will run as follows:

`parse the command line, validate parameters, initialize other modules
create new index and load index from indexFilename into that index
call readQueries`

where `readQueries`:

`calls parseQueries to clean and parse the query (and make sure it's valid)
`

