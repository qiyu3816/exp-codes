// 读取每行输入并输出该行字符长度
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <semaphore.h>
#include <string.h>

sem_t sem_1;
sem_t sem_2;
void count_strlen(char*);

int main(int argc, char *argv[])
{
    int ret;
    pthread_t thread_1;
    char* msg;

    // 初始化
    ret = sem_init(&sem_1, 0, 0);
    if(ret == -1)
    {
        perror("semaphore initialization failed\n");
        exit(EXIT_FAILURE);
    }
    ret = sem_init(&sem_2, 0, 1);
    if(ret == -1)
    {
        perror("semaphore initialization failed\n");
        exit(EXIT_FAILURE);
    }
    ret = pthread_create(&thread_1, NULL, (void*)count_strlen, msg);
    if(ret != 0)
    {
        perror("pthread_create failed\n");
        exit(EXIT_FAILURE);
    }

    // 开始输入
    printf("Input line by line and type 'quit' to finish\n");
    sem_wait(&sem_2);
    while(strcmp("quit\n", msg) != 0)
    {
        fgets(msg, 512, stdin);
        sem_post(&sem_1);
        sem_wait(&sem_2);
    }

    printf("\nending...\n");
    ret = pthread_join(thread_1, NULL);
    if(ret != 0)
    {
        perror("pthread_join failed\n");
        exit(EXIT_FAILURE);
    }
    sem_destroy(&sem_1);
    sem_destroy(&sem_2);
    printf("end successfully");
    return 0;
}

void count_strlen(char* msg)
{
    sem_wait(&sem_1);
    while(strcmp("quit\n", msg) != 0)
    {
        printf("last line has %ld characters\n\n", strlen(msg) - 1);
        sem_post(&sem_2);
        sem_wait(&sem_1);
    }
    sem_post(&sem_2);
    pthread_exit(NULL);
}
