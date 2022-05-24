#include <stdio.h>
#include <stdlib.h>
#include "inculde/add.h"

int main(int argc, char *argv[])
{
    if(argc != 3)
        printf("please input two numbers!!!\n");
    int a = atoi(argv[1]), b = atoi(argv[2]);
    printf("result: %d\n", add(a, b));
    return 0;
}
