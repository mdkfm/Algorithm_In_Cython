VPATH = ./Container:./List:./Graph:./test
CC = gcc
CFLAGS = -fgnu89-inline

vpath %.c ./List ./Graph ./test ./Container
vpath %.h ./include
vpath %.so ./lib

test_source = $(wildcard ./test/graphAdj_test.c)
test := $(patsubst ./test/%.c, %, $(test_source))
all : $(test)

container = $(wildcard ./Container/*.c)
lib = $(patsubst ./Container/%.c, ./lib/lib%.so, $(container))

$(test): %_test : %_test.c %.c $(lib)
	$(CC) $^ -o ./test/$@ $(CFLAGS)

$(lib): ./lib/lib%.so : %.c %.h
	$(CC) $< -fPIC -shared -o $@ $(CFLAGS)
