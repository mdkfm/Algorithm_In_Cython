VPATH = ./List:./Graph:./test
CC = g++

vpath %.c ./List ./Graph ./test
vpath %.h ./include
vpath %.so ./lib

test = $(wildcard ./test/*.cpp)
test := $(patsubst ./test/%.cpp, %, $(test))
all : $(test)

test_graph : test_graph.cpp graph.cpp queue.cpp
	$(CC) ./test/test_graph.cpp ./List/queue.cpp ./Graph/graph.cpp -o ./test/$@

test_queue : test_queue.cpp queue.cpp
	$(CC) ./test/test_queue.cpp ./List/queue.cpp -o ./test/$@
