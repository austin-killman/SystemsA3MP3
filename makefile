CC = gcc

CFLAGS += -std=gnu11
CFLAGS += -Wall -Werror


defrag: defrag.c 
	${CC} ${CFLAGS} -pthread -o defrag defrag.c -g
