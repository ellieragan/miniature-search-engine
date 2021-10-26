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
echo $?

