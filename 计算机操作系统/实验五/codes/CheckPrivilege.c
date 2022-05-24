#include <stdio.h>   
#include <stdlib.h>   
#include <unistd.h>   
#include <fcntl.h>   

int main(int argc, char* argv[])   
{   
    if((access("test.txt",F_OK))!=-1)   
    {   
        printf("file test.txt exists.\n");   
    }   
    else  
    {   
        printf("test.txt doesn't exist!\n");   
    }   

    if(access("test.txt",R_OK)!=-1)   
    {   
        printf("test.txt can read: \n");   
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
        printf("test.txt cannot read.\n");   
    }   

    if(access("test.txt",W_OK)!=-1)   
    {   
        printf("test.txt can write\n");   
    }   
    else  
    {   
        printf("test.txt cannot write.\n");   
    }   
    if(access("test.txt",X_OK)!=-1)   
    {   
        printf("test.txt can execute\n");   
    }   
    else  
    {   
        printf("test.txt cannot execute.\n");   
    }   

    return 0;   
}  
