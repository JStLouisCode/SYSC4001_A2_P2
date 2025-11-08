#pragma once
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <signal.h>

#define SEM_KEY 12345
#define SHM_KEY 99999

// two ints: [0] multiple, [1] counter
#define SHM_SIZE (2 * sizeof(int))

// tiny helpers
static inline void die(const char* msg){ perror(msg); exit(1); }
