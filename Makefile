CFLAGS=-Wall -Wextra -Werror -pedantic -std=c99
CC=clang $(CFLAGS)

all	:	hatterspeak

hatterspeak:	hatterspeak.o bv.o speck.o bf.o parser.o hs.o ll.o str.o hash.o
	$(CC) -o hatterspeak hatterspeak.o bv.o speck.o bf.o parser.o hs.o ll.o str.o hash.o
hatterspeak.o:	hatterspeak.c
	$(CC) -c hatterspeak.c
bv.o	:	bv.c
	$(CC) -c bv.c
speck.o	:	speck.c
	$(CC) -c speck.c
bf.o	:	bf.c
	$(CC) -c bf.c
parser.o:	parser.c
	$(CC) -c parser.c
hs.o	:	hs.c
	$(CC) -c hs.c
ll.o	:	ll.c
	$(CC) -c ll.c
str.o	:	str.c
	$(CC) -c str.c
hash.o	:	hash.c
	$(CC) -c hash.c
clean	:
	rm -rf hatterspeak hatterspeak.o bv.o bf.o speck.o parser.o hs.o ll.o str.o hash.o infer-out
infer	:
	make clean; infer-capture -- make; infer-analyze -- make

