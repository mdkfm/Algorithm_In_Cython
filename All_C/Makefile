VPATH = ./List:./Graph:./test

vpath %.c ./List ./Graph ./test
vpath %.h ./include
vpath %.so ./lib

test = $(wildcard ./test/*.c)
test := $(patsubst ./test/%.c, %, $(test))
all : $(test)


heap_test: heap_test.c libheap.so lib
	gcc ./test/heap_test.c ./lib/libheap.so -o ./test/heap_test

queue_test: queue_test.c libqueue.so
	gcc ./test/queue_test.c ./lib/libqueue.so -o ./test/queue_test

link_test: link_test.c liblink.so
	gcc ./test/link_test.c ./lib/liblink.so -o ./test/link_test

tree_test: tree_test.c libtree.so libqueue.so
	gcc ./test/tree_test.c ./lib/libtree.so ./lib/libqueue.so -o ./test/tree_test

lib%.so : %.c
	gcc $< -fPIC -shared -o ./lib/$@;
