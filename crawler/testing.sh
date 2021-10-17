# testing for lab 4
# ellie boyd
# cs50
# 10-15-21

#test 1--missing parameter
./crawler http://cs50tse.cs.dartmouth.edu/tse/letters/index.html ../data/letters
echo $?

#test2--non-internal URL
./crawler https://facebook.com ../data/letters 1
echo $?

#test3--invalid pageDirectory
./crawler http://cs50tse.cs.dartmouth.edu/tse/letters/index.html hello 1
echo $?

#test4--maxDepth is out of range
./crawler http://cs50tse.cs.dartmouth.edu/tse/letters/intex.html ../data/letters 15
echo $?

#test5--valgrind toscrape at depth 1
valgrind ./crawler http://cs50tse.cs.dartmouth.edu/tse/toscrape ../data/letters 1
echo $?

#test6--toscrape at depth 2
./crawler http://cs50tse.cs.dartmouth.edu/tse/toscrape ../data/letters 2

#test7--valgrind letters depth 1
valgrind ./crawler http://cs50tse.cs.dartmouth.edu/tse/letters/index.html ../data/letters 1
echo $?

#test8--letters depth 2
./crawler http://cs50tse.cs.dartmouth.edu/tse/letters/index.html ../data/letters 2
echo $?

#test9--letters depth 3
./crawler http://cs50tse.cs.dartmouth.edu/tse/letters/index.html ../data/letters 3

#test10--wiki depth 1
./crawler http://cs50tse.cs.dartmouth.edu/tse/wikipedia ../data/letters 1

