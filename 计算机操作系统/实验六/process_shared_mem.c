// 创建共享内存，子进程写入argv[1]，父进程读取
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>
#include <unistd.h>

void write_unit(int shmid, char*);
void read_unit(int shmid);

int main(int argc, char *argv[])
{
    pid_t fpid;
    int shmid;
    shmid = shmget(IPC_PRIVATE, 1024, IPC_CREAT | 0600);
    printf("shmid: %d\n", shmid);
    if(shmid < 0)
    {
        perror("shmget error!\n");
        exit(1);
    }
    printf("shmget OK. Create shared memory successfully.\n");

    fpid = fork();

    if(fpid < 0)
    {
        printf("create child process error!\n");
        exit(1);
    }
    else if(fpid == 0)
    {
        write_unit(shmid, argv[1]);
    }
    else
    {
        sleep(2);
        read_unit(shmid);
    }

    return 0;
}

void write_unit(int shmid, char* arg)
{
    char* shmaddr = (char*)shmat(shmid, NULL, 0);
    if((int)shmaddr == -1)
    {
        perror("shmaddr error.\n");
        exit(1);
    }
    //strcpy(shmaddr, arg); // strcpy方式
    //memcpy(shmaddr, arg, strlen(arg) + 1); // memcpy方式
    memmove(shmaddr, arg, strlen(arg) + 1); // memmove方式
    printf("write shared memory: %s\n", shmaddr);
    shmdt(shmaddr);
}

void read_unit(int shmid)
{
    char* shmaddr = (char*)shmat(shmid, NULL, 0);
    if((int)shmaddr == -1)
    {
        perror("shmaddr error.\n");
        exit(1);
    }
    printf("read shared memory: %s\n", shmaddr);
    shmdt(shmaddr);
}
