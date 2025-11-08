#include "ipc.h"

static struct sembuf SEM_LOCK = {0,-1,0};
static struct sembuf SEM_UNLOCK={0, 1,0};

int create_or_get_sem(key_t key){
    int id = semget(key, 1, IPC_CREAT | 0666);
    if(id==-1) die("semget");
    return id;
}
void sem_set(int semid, int val){ if(semctl(semid,0,SETVAL,val)==-1) die("semctl SETVAL"); }
void P(int semid){ if(semop(semid, &SEM_LOCK, 1)==-1) die("semop P"); }
void V(int semid){ if(semop(semid, &SEM_UNLOCK,1)==-1) die("semop V"); }

int* shm_attach(key_t key, size_t size, int* out_id){
    int id = shmget(key, size, IPC_CREAT | 0666);
    if(id==-1) die("shmget");
    void* p = shmat(id, NULL, 0);
    if(p==(void*)-1) die("shmat");
    if(out_id) *out_id = id;
    return (int*)p;
}
void shm_detach(void* addr){ if(shmdt(addr)==-1) die("shmdt"); }
void shm_remove(int shmid){ if(shmctl(shmid, IPC_RMID, NULL)==-1) die("shmctl RMID"); }
void sem_remove(int semid){ if(semctl(semid, 0, IPC_RMID)==-1) die("semctl RMID"); }
