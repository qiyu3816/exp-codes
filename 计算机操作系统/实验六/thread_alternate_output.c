// 父子线程交替输出
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <time.h>
#include <string.h>

char* getNowtime(void) 
{
	static char s[30]={0};
    char YMD[15] = {0};
    char HMS[10] = {0};
    time_t current_time;
    struct tm* now_time;

    char *cur_time = (char *)malloc(21*sizeof(char));
    time(&current_time);
    now_time = localtime(&current_time);

    strftime(YMD, sizeof(YMD), "%F ", now_time);
    strftime(HMS, sizeof(HMS), "%T", now_time);
    
    strncat(cur_time, YMD, 11);
    strncat(cur_time, HMS, 8);

    printf("\ncurrent time: %s\n", cur_time);
	memcpy(s, cur_time, strlen(cur_time)+1);
    free(cur_time);

    cur_time = NULL;

    return s;
}

int shared_sign = 0;
pthread_mutex_t father_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t child_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t father_cond = PTHREAD_COND_INITIALIZER;
pthread_cond_t child_cond = PTHREAD_COND_INITIALIZER;

void child(void)
{
    int count = 4;
    pthread_cond_signal(&child_cond);
    while(count--)
    {
        pthread_cond_wait(&father_cond, &father_mutex);
        pthread_mutex_trylock(&child_mutex);
        shared_sign--;
        printf("this is thread 2\n");
        printf("current num is: -------->%d\n", shared_sign);
        printf("--------------------------------------\n");
        pthread_mutex_unlock(&child_mutex);
        pthread_cond_signal(&child_cond);
    }
    pthread_exit(NULL);
}
void father(void)
{
    int count = 4;
    while(count--)
    {
        pthread_cond_wait(&child_cond, &child_mutex);
        pthread_mutex_lock(&father_mutex);
        shared_sign++;
        printf("this is thread 1\n");
        printf("current num is: -------->%d\n", shared_sign);
        printf("--------------------------------------\n");
        pthread_mutex_unlock(&father_mutex);
        pthread_cond_signal(&father_cond);
    }
    pthread_cond_signal(&father_cond);
    pthread_exit(NULL);
}

int main()
{
    int ret;
    pthread_t thread_1, thread_2;
    
    ret = pthread_create(&thread_1, NULL, (void*)father, NULL);
    ret = pthread_create(&thread_2, NULL, (void*)child, NULL);

    pthread_join(thread_1, NULL);
    pthread_join(thread_2, NULL);

    printf("final: %d\n", shared_sign);
    return 0;
}
