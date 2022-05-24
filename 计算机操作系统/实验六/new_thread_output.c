// 主线程创建新线程，新线程输出运行信息，分别试用pthread_exit()和exit()退出新线程
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <time.h>
#include <string.h>

void output(void)
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

    printf("\nchild thread current time: %s\n", cur_time);
	memcpy(s, cur_time, strlen(cur_time)+1);
    free(cur_time);

    cur_time = NULL;

    //pthread_exit(NULL);
    exit(0);
}

int main()
{
    int ret;
    pthread_t thread_1;
    
    ret = pthread_create(&thread_1, NULL, (void*)output, NULL);

    pthread_join(thread_1, NULL);

    printf("main thread end\n");
}
