VPATH = ./include:./lib:./List:./Graph:./test

link_list_test: link_list_test.c liblink_list.so
	gcc ./test/link_list_test.c ./lib/liblink_list.so -o ./test/link_list_test
tree_test: tree_test.c libtree.so libqueue.so
	gcc ./test/tree_test.c ./lib/libtree.so ./lib/libqueue.so -o ./test/tree_test

liblink_list.so: link_list.c
	gcc ./List/link_list.c -fPIC -shared -o ./lib/liblink_list.so
libqueue.so: queue.c
	gcc ./List/queue.c -fPIC -shared -o ./lib/libqueue.so
libtree.so: tree.c queue.h
	gcc ./Graph/tree.c ./lib/libqueue.so -fPIC -shared -o ./lib/libtree.so



