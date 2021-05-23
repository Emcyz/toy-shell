#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <signal.h>

int main(void)
{
    int shmid;
    void *shmaddr;
    if((shmid=shmget((key_t)4885, sizeof(int) * 3, IPC_CREAT|0666)) == -1)
    {
       perror("shmid failed");
       exit(1);
    }
    if((shmaddr=shmat(shmid, (void *)0, 0)) == (void *)-1)
    {
       perror("shmat failed");
       exit(1);
    }

    int s;
    int a;
    int b;
    int *shm;
    shm = (int *)shmaddr;
    pid_t pid, cpid;
    int status;
    int i = 0;

    while (true)
    {
        printf("MyShell $ ");
        s = fscanf(stdin, "%d %d", &a, &b);
        if (s == -1)
        {
            fprintf(stderr, "fscanf_s failed\n");
            exit(1);
        }
        
        shm[0] = a;
        shm[1] = b; 

        pid = fork();
        if (pid < 0) {
            fprintf(stderr, "fork failed\n");
            exit(1);
        } 
        else if (pid != 0)
        {  /* parent */
            sleep(1);
            while (shm[2] != 0)
            {
                shm[2] = shm[0] % shm[1];
                if (shm[2] != 0)
                {
                    shm[0] = shm[1];
                    shm[1] = shm[2];
                    printf("parent : %d %d\n", shm[0], shm[1]);
                }
                else
                {
                    printf("parent solved GCD : %d\n", shm[1]);
                    kill(pid, SIGINT);
                    printf("parent killed child process\n");
                    break;
                }
                sleep(2);
            }
        }
        else
        {  /* child */
            while (1)
            {
                shm[2] = shm[0] % shm[1];
                if (shm[2] != 0)
                {
                    shm[0] = shm[1];
                    shm[1] = shm[2];
                    printf("child : %d %d\n", shm[0], shm[1]);
                }
                else
                {
                    printf("child solved GCD : %d\n", shm[1]);
                    return 1;
                }
                sleep(2);
            }
        }
    }
    return 0;
}
