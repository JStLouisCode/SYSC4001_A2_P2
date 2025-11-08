CC=gcc
CFLAGS=-Wall -Wextra -O2
SRC_DIR=src

all: process1 process2

process1: $(SRC_DIR)/process1_101235916_101236784.c $(SRC_DIR)/ipc.c
	$(CC) $(CFLAGS) $^ -o process1

process2: $(SRC_DIR)/process2_101235916_101236784.c $(SRC_DIR)/ipc.c
	$(CC) $(CFLAGS) $^ -o process2

clean:
	rm -f process1 process2

.PHONY: all clean
