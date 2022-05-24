### C语言创建新线程及共享内存使用

#### 多线程

```c
#include <pthread.h>

// 线程创建时传入的参数是指针型的，函数定义的参数类型故而要用二级指针
void func(char**);

// 首先声明线程标识符
pthread_t thread_1;
pthread_t thread_1;

// 创建新线程
// 函数标识符，线程属性，线程函数指针，函数的参数
int ret = pthread_create(&thread_1, NULL, (void*)func, &argv[1]);
int ret = pthread_create(&thread_2, NULL, (void*)func, &argv[2]);

// 将子线程合入主线程，阻塞主线程等待子线程结束
// 子线程资源不会自动回收，需要运行pthread_exit()
pthread_join(thread_1);

// 将子线程与主线程分离，子线程结束资源自动回收
// pthread_join()函数的替代函数，可回收创建时detachstate属性设置为PTHREAD_CREATE_JOINABLE的线程的存储空间。该函数不会阻塞父线程。pthread_join()函数用于只是应用程序在线程tid终止时回收其存储空间。
pthread_detach(thread_2);
```



#### 共享内存

```c
#include <sys/ipc.h>
#include <sys/shm.h>

// 开辟或使用一块共享内存，返回shmid
int shmget(key_t key, int size, int shmflg);

// 将参数shmid所指向的共享内存与当前进程连接。当使用某共享内存时，需要先使用shmat，达成连接
void *shmat(int shmid, const void *shmaddr, int shmflg); 

// 将先前用shmat连接的共享内存与当前进程解除连接。参数shmaddr为shmat返回的共享内存的地址
int shmdt(const void *shmaddr);

// 控制内存的操作。当cmd为IPC_RMID时，删除shmid所指的共享内存
int shmctl(int shmid, int cmd, struct shmid_ds *buf);

// 创建共享内存示例
shmid = shmget(IPC_PRIVATE, 1024, IPC_CREATE | 0600);
// shmid小于0则出错
if(shmid < 0)
{
    perror("shmget error!\n");
    exit(1);
}
printf("shmget OK. Create shared memory successfully.\n");

// 读写共享内存示例
char* shmaddr = (char*)shmat(shmid, NULL, 0);
if((int)shmaddr == -1)
{
    perror("shmaddr error.\n");
    exit(1);
}
strcpy(shmaddr, argv[1], strlen(argv[1]) + 1);
shmdt(shmaddr);
```

key_t，0/IPC_PRIVATE，函数shmget()将创建一块新的共享内存。

shmflg，IPC_CREAT，如果共享内存不存在，则创建一个共享内存，否则打开操作；IPC_EXCL，只有在共享内存不存在的时候，新的共享内存才建立，否则就产生错误。