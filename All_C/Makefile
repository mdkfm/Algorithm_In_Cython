VPATH = ./List:./Graph:./test
CC = gcc
CFLAGS = -fgnu89-inline

vpath %.c ./List ./Graph ./test
vpath %.h ./include
vpath %.so ./lib

test = $(wildcard ./test/*.c)
test := $(patsubst ./test/%.c, %, $(test))
all : $(test)

huffman_test: huffman_test.c libhuffman.so libheap.so
	$(CC) $(CFLAGS) ./test/huffman_test.c ./lib/libhuffman.so ./lib/libheap.so -o ./test/huffman_test

heap_test: heap_test.c libheap.so lib
	$(CC) $(CFLAGS) ./test/heap_test.c ./lib/libheap.so -o ./test/heap_test

rlist_test: rlist_test.c librlist.so
	$(CC) $(CFLAGS) ./test/rlist_test.c ./lib/librlist.so -o ./test/rlist_test

link_test: link_test.c liblink.so
	$(CC) $(CFLAGS) ./test/link_test.c ./lib/liblink.so -o ./test/link_test

tree_test: tree_test.c libtree.so librlist.so
	$(CC) $(CFLAGS) ./test/tree_test.c ./lib/libtree.so ./lib/librlist.so -o ./test/tree_test

lib%.so : %.c
	$(CC) $(CFLAGS) $< -fPIC -shared -o ./lib/$@;
