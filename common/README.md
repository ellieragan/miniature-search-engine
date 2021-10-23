### Notes about index.c:

Despite the fact that I started this lab almost a week ago and regularly attended office hours/TA hours, the program has spent the last couple of days refusing to write into the output file, and I'm unsure of why this is. I tried going through gdb with a breakpoint in indexer.c where `index_save` is called, but there is no obvious error occurring in `index_save` aside from, perhaps, the fact that (several steps in) `set_iterate` does not appear to be calling the helper function it is supposed to. I also put a variety of print statements in different places during testing and everything seems to be working up to and past the `hashtable_iterate` function in my `index_save`, except that the program could not reach the print statements I put inside of my two helper functions `iterateAgain` and `helpsCounter` (called by `hashtable_iterate`). There are no errors thrown by `hashtable_iterate`, though, and the program continues to run after hitting that line without throwing any compiler errors. Also, because of the fact that I can't get any printed output, I had kind of a difficult time testing; I tried to write tests carefully but with no way of comparing my output to the sample output I'm unsure of whether or not the tests work as they should. 