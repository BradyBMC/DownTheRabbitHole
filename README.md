# Assignment 6

## Down the Rabbit Hole and Through the Looking Glass: Bloom Filters, Hashing, and the Red Queen's Decrees

# by Brady Chan, brmchan 11/25/2020

## How to Run Code
To run the code type "make" in the same file directory where the code resides and hit enter to check for possible memory leaks. After compiling the program, type ./hatterspeak followed by -s, -h, -f, -m,- b. S will print out the stats and not the letter, h changes the size of the hashtable if a integer is supplied after, f changes the size of bloom filter if an integer is supplied after, m uses the move to fron and b doesn't use the move to front. The program is defaulted to not use the move to front rule and using b and m at the same time will cause an error. After putting in a valid argument, the program will take in a user input and check if it is in the hatterspeak or oldspeak textfiles. When the program is done searching it will print out a letter or stats. Lastly, type "make clean" to remove infer and all files created.

## Description
Store words inside bloom filter, linked list and hashtable. Then checks user input to see if they match.


### Deliverables

1. hatterspeak.c
1. speck.c
1. speck.h
1. hash.c
1. hash.h
1. parser.c
1. praser.h
1. ll.c
1. ll.h
1. str.c
1. str.h
1. hs.c
1. hs.h
1. bf.c
1. bf.h
1. bv.c
1. bv.h
1. Makefile
1. README.md
1. DESIGN.pdf
1. WRITEUP.pdf

## Notes
> No make infer errors, and no valgrind error. Clears all memory successfully.
> Takes in only positive integer for size and there is no edge case for negatives
> Cannot take both b and m since they contradict. It was assumed default move_to_front to be false since it wasn't said in the pdf. 

