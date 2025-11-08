#pragma once
#include "common.h"

int  create_or_get_sem(key_t key);
void sem_set(int semid, int val);
void P(int semid);  // lock
void V(int semid);  // unlock

int* shm_attach(key_t key, size_t size, int* out_id);
void shm_detach(void* addr);
void shm_remove(int shmid);
void sem_remove(int semid);
