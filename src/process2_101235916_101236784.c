// Child: waits until counter > 100, then decrements; prints multiples of shared multiple.
#include "ipc.h"

int main(void){
    int sem = create_or_get_sem(SEM_KEY);
    int shmid; 
    int* data = shm_attach(SHM_KEY, SHM_SIZE, &shmid);

    // start when counter > 100
    for(;;){
        P(sem); int counter = data[1]; V(sem);
        if(counter > 100) { printf("[Process 2] start @ counter=%d\n", counter); break; }
        sleep(1);
    }

    int cycle=0;
    for(;;){
        P(sem);
        int multiple = data[0];
        data[1]--;                      // decrement shared counter
        int counter = data[1];
        V(sem);

        if(counter % multiple == 0)
            printf("[Process 2] Cycle:%d - %d is a multiple of %d\n", cycle, counter, multiple);
        else
            printf("[Process 2] Cycle:%d\n", cycle);

        cycle++;
        if(counter > 500){              // same stop rule as your code
            printf("[Process 2] Counter exceeded 500. Exit.\n");
            break;
        }
        sleep(1);
    }

    shm_detach(data);
    return 0;
}
