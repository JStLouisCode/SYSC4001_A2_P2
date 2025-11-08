// Parent: increments and prints multiples; forks and execs process2; cleans up.
#include "ipc.h"

int main(void){
    srand(time(NULL));

    int sem = create_or_get_sem(SEM_KEY);
    sem_set(sem, 1);

    int shmid; 
    int* data = shm_attach(SHM_KEY, SHM_SIZE, &shmid);

    // init shared state
    P(sem); data[0]=3; data[1]=0; V(sem);

    pid_t pid = fork();
    if(pid < 0) die("fork");

    if(pid == 0){
        // CHILD: replace image with process2
        execl("./process2", "process2", (char*)NULL);
        die("exec process2");
    }

    // PARENT loop
    int cycle=0;
    for(;;){
        P(sem);
        data[1]++;                      // increment shared counter
        int counter = data[1];
        int multiple = data[0];
        V(sem);

        if(counter % multiple == 0)
            printf("[Process 1] Cycle:%d - %d is a multiple of %d\n", cycle, counter, multiple);
        else
            printf("[Process 1] Cycle:%d\n", cycle);

        cycle++;
        if(counter > 500){
            printf("[Process 1] Counter exceeded 500. Terminating.\n");
            break;
        }
        sleep(1);
    }

    // wait + cleanup
    wait(NULL);
    shm_detach(data);
    shm_remove(shmid);
    sem_remove(sem);
    printf("[Process 1] Cleanup complete. Exiting.\n");
    return 0;
}
