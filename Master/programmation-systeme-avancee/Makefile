CC = gcc 
CFLAGS = -Wall -g 
LDLIBS = -pthread -lrt
all : rl_test

rl_lock_library.o : rl_lock_library.c rl_lock_library.h

rl_test : rl_test.c rl_lock_library.o
clear : 
	rm *.o 