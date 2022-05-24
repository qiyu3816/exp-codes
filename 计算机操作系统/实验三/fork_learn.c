// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// #include <unistd.h>
// #include <stdio.h> 
// int main () 
// { 
// 	pid_t fpid; //fpid表示fork函数返回的值
// 	int count=0;
// 	fpid=fork(); 
// 	if (fpid < 0) 
// 		printf("error in fork!"); 
// 	else if (fpid == 0) {
// 		printf("i am the child process, my process id is %d/n",getpid()); 
// 		printf("我是爹的儿子/n");//对某些人来说中文看着更直白。
// 		count++;
// 	}
// 	else {
// 		printf("i am the parent process, my process id is %d/n",getpid()); 
// 		printf("我是孩子他爹/n");
// 		count++;
// 	}
// 	printf("统计结果是: %d/n",count);
// 	return 0;
// }

// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// #include <unistd.h>
// #include <stdio.h>
// int main(void)
// {
//    int i=0;
//    printf("i son/pa ppid pid  fpid/n");
//    //ppid指当前进程的父进程pid
//    //pid指当前进程的pid,
//    //fpid指fork返回给当前进程的值
//    for(i=0;i<2;i++){
//        pid_t fpid=fork();
//        if(fpid==0)
//     	   printf("%d child  %4d %4d %4d/n",i,getppid(),getpid(),fpid);
//        else
//     	   printf("%d parent %4d %4d %4d/n",i,getppid(),getpid(),fpid);
//    }
//    return 0;
// }

// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// #include <unistd.h>
// #include <stdio.h>
// int main(void)
// {
//    int i=0;
//    for(i=0;i<3;i++){
//        pid_t fpid=fork();
//        if(fpid==0)
//     	   printf("son/n");
//        else
//     	   printf("father/n");
//    }
//    return 0;

// }

// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// #include <unistd.h>
// #include <stdio.h>
// int main() {
// 	pid_t fpid;//fpid表示fork函数返回的值
// 	//printf("fork!");
// 	printf("fork!/n");
// 	fpid = fork();
// 	if (fpid < 0)
// 		printf("error in fork!");
// 	else if (fpid == 0)
// 		printf("I am the child process, my process id is %d/n", getpid());
// 	else
// 		printf("I am the parent process, my process id is %d/n", getpid());
// 	return 0;
// }

// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// #include <stdio.h>
// #include <unistd.h>
// int main(int argc, char* argv[])
// {
//    fork();
//    fork() && fork() || fork();
//    fork();
//    return 0;
// }

// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
int main(int argc, char* argv[])
{
    pid_t fpid_1;
    pid_t fpid_2;
    (fpid_1 = fork()) && (fpid_2 = fork());
    if(fpid_1 == 0)
    {
        int ret = nice(0);
        printf("child b priority=%d\n", ret);
        if(ret == -1)
        {
            if(errno == EACCES) printf("cannot set priority\n");
        }
    }
    else if(fpid_2 == 0)
    {
        int ret = nice(10);
        printf("child c priority=%d\n", ret);
        if(ret == -1)
        {
            if(errno == EACCES) printf("cannot set priority\n");
        }
    }
    else
    {
        int ret = nice(19);
        printf("father a priority=%d\n", ret);
        if(ret == -1)
        {
            if(errno == EACCES) printf("cannot set priority\n");
        }
    }

    if(fpid_1 == 0)
    {
        printf("I'm child b ppid=%d pid=%d\n", getppid(), getpid());
    }
    else if(fpid_2 == 0)
    {
        printf("I'm child c ppid=%d pid=%d\n", getppid(), getpid());
    }
    else
    {
        printf("I'm father a ppid=%d pid=%d\n", getppid(), getpid());
    }
    return 0;
}
