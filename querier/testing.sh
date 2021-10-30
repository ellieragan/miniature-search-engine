# testing for lab 6
# ellie boyd
# cs50
# 10-24-21


#test1--running with no parameters
./querier
echo $?

#test2--running with 3 parameters
./querier a b c
echo $?

#test3--running with a non-crawler-made directory
./querier ../../shared/tse/output/indexer ../../shared/tse/output/indexer/index-letters-1
echo $?

#test4--running with an indexFilename that cannot be read
./querier ../../shared/tse/output/crawler/pages-letters-depth-1 thisFileDoesNotExist

#test5--running with an invalid character as user input
.querier ../../shared/tse/output/crawler/pages-letters-depth-1 ../../shared/tse/output/indexer/index-letters-1
# expect: "query: "
# send: "&&***"
#once again I was not capable of figuring out expect/send

#test6--run with words that do exist in given file
.querier ../../shared/tse/output/crawler/pages-letters-depth-1 ../../shared/tse/output/indexer/index-letters-1
# expect: "query: "
# send: "page and home"
# i wanted to use expect and send but i couldn't get it to word :(
# try just inputting "page and home" because page appears once in two file and home appears once in all
echo $?

#test7--run with words that do not exist in given file?
#the word "dog" does not exist in these files if you need ideas for input
.querier ../../shared/tse/output/crawler/pages-letters-depth-1 ../../shared/tse/output/indexer/index-letters-1


