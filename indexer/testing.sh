# testing for lab 5
# ellie boyd
# cs50
# 10-17-21

#my test numbers are off from the sample I'm sorry

#test1--one missing argument
./indexer ../data/letters
echo $?

#test2--no arguments
./indexer
echo $?

#test3--more than two arguments
./indexer ~/cs50-dev/shared/tse/output/crawler/pages-letters-depth-1 ./myindexer hello there
echo $?

#test4--invalid pageDirectory
./indexer ./hello ./myindexer
echo $?

#test5--invalid indexFile
./indexer ~/cs50-dev/shared/tse/output/crawler/pages-letters-depth-1 NULL
echo $?

#test6--invalid indexFile (read only directory)
touch readonlydirectory
./indexer ~/cs50-dev/shared/tse/output/crawler/pages-letters-depth-1 readonlydirectory
echo $?

#test7--valgrind test
valgrind ./indexer ~/cs50-dev/shared/tse/output/crawler/pages-letters-depth-1 ./myindexer
echo $?











