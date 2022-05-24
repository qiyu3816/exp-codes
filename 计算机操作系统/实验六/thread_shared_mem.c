// 父进程创建共享内存，新开两个线程，一个写入argv[1]，一个从共享内存读取
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>

int shmid;

void write_unit(char**);
void read_unit(void);

int main(int argc, char *argv[])
{
    int ret;
    shmid = shmget(IPC_PRIVATE, 1024, IPC_CREAT | 0600);
    printf("shmid: %d\n", shmid);
    if(shmid < 0)
    {
        perror("shmget error!\n");
        exit(1);
    }
    printf("shmget OK. Create shared memory successfully.\n");

    pthread_t thread_1, thread_2;

    ret = pthread_create(&thread_1, NULL, (void *)write_unit, &argv[1]);
    ret = pthread_create(&thread_2, NULL, (void *)read_unit, NULL);

    pthread_join(thread_1, NULL);
    pthread_join(thread_2, NULL);

    return 0;
}

void write_unit(char** arg)
{
    char* shmaddr = (char*)shmat(shmid, NULL, 0);
    if((int)shmaddr == -1)
    {
        perror("shmaddr error.\n");
        exit(1);
    }
    strcpy(shmaddr, *arg);
    shmdt(shmaddr);
    printf("write shared memory: %s\n", *arg);
}

void read_unit(void)
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

