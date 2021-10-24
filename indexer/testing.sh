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
./indexer ~/cs50-dev/shared/tse/output/crawler/pages-letters-depth-1 ../data/myindexer hello there
echo $?

#test3--index compare of letters1
./indexer ../../shared/tse/output/crawler/pages-letters-depth-1 ../data/letters1
../../shared/tse/indexcmp ../../shared/tse/output/indexer/index-letters-1 ../data/letters1

#test4--letters2
./indexer ../../shared/tse/output/crawler/pages-letters-depth-2 ../data/letters2
../../shared/tse/indexcmp ../../shared/tse/output/indexer/index-letters-2 ../data/letters2

#test5--index compare of letters3
./indexer ../../shared/tse/output/crawler/pages-letters-depth-3 ../data/letters3
../../shared/tse/indexcmp ../../shared/tse/output/indexer/index-letters-3 ../data/letters3

#test6--index compare of letters10
./indexer ../../shared/tse/output/crawler/pages-letters-depth-10 ../data/letters10
../../shared/tse/indexcmp ../../shared/tse/output/indexer/index-letters-10 ../data/letters10

#test7--index compare of toscrape1
./indexer ../../shared/tse/output/crawler/pages-toscrape-depth-1 ../data/toscrape1
../../shared/tse/indexcmp ../../shared/tse/output/indexer/index-toscrape-1 ../data/toscrape1

#test8--index compare of toscrape2
./indexer ../../shared/tse/output/crawler/pages-toscrape-depth-2 ../data/toscrape2
../../shared/tse/indexcmp ../../shared/tse/output/indexer/index-toscrape-2 ../data/toscrape2

#test 9 should be toscrape3 according to the rubric but there is no toscrape 3 provided in cs50-dev/shared/tse/output/crawler

#test10--index compare of wiki1
./indexer ../../shared/tse/output/crawler/pages-wikipedia-depth-1 ../data/wiki1
../../shared/tse/indexcmp ../../shared/tse/output/indexer/index-wikipedia-1 ../data/wiki1

#test11--index compare of wiki2
./indexer ../../shared/tse/output/crawler/pages-wikipedia-depth-2 ../data/wiki2
../../shared/tse/indexcmp ../../shared/tse/output/indexer/index-wikipedia-2 ../data/wiki2

#test12--index compare of wiki3
./indexer ../../shared/tse/output/crawler/pages-wikipedia-depth-3 ../data/wiki3
../../shared/tse/indexcmp ../../shared/tse/output/indexer/index-wikipedia-3 ../data/wiki3

#test13--invalid pageDirectory
./indexer ./hello ../data/myindexer
echo $?

#test14--invalid indexFile
./indexer ~/cs50-dev/shared/tse/output/crawler/pages-letters-depth-1 *&&^%%
echo $?

#test15--invalid indexFile (read only directory)
cd ../data
touch readonlydirectory
./indexer ~/cs50-dev/shared/tse/output/crawler/pages-letters-depth-1 ../data/readonlydirectory
echo $?

#test16--valgrind test
valgrind ./indexer ~/cs50-dev/shared/tse/output/crawler/pages-letters-depth-1 ../data/myindexer
echo $?











