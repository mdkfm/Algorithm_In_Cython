VPATH = ./List:./Graph:./test

vpath %.c ./List ./Graph ./test
vpath %.h ./include
vpath %.so ./lib

test = $(wildcard ./test/*.c)
test := $(patsubst ./test/%.c, %, $(test))
all : $(test)

link_list_test: link_list_test.c liblink_list.so
	gcc $() -o ./test/link_list_test

tree_test: tree_test.c libtree.so libqueue.so
	gcc ./test/tree_test.c ./lib/libtree.so ./lib/libqueue.so -o ./test/tree_test

lib%.so : %.c
	gcc $< -fPIC -shared -o ./lib/$@;
