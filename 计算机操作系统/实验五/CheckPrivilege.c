#include <stdio.h>   
#include <stdlib.h>   
#include <unistd.h>   
#include <fcntl.h>   

int main(int argc, char* argv[])   
{   
    if((access("test.txt",F_OK))!=-1)   
    {   
        printf("文件 test.txt 存在.\n");   
    }   
    else  
    {   
        printf("test.txt 不存在!\n");   
    }   

    if(access("test.txt",R_OK)!=-1)   
    {   
        printf("test.txt 有可读权限，读得：\n");   
        FILE *fr = fopen("test.txt", "r");
        char c;
        while((c = getc(fr)) != EOF)
        {
            printf("%c", c);
        }
        printf("\n");
        fclose(fr);
    }   
    else  
    {   
        printf("test.txt 不可读.\n");   
    }   

    if(access("test.txt",W_OK)!=-1)   
    {   
        printf("test.txt 有可写权限\n");   
    }   
    else  
    {   
        printf("test.txt 不可写.\n");   
    }   
    if(access("test.txt",X_OK)!=-1)   
    {   
        printf("test.txt 有可执行权限\n");   
    }   
    else  
    {   
        printf("test.txt 不可执行.\n");   
    }   

    return 0;   
}  
