#include <stdio.h>

void BubbleSort(int A[], int s, int m)
{
	int i, j, t;
	for(j = 0; j <= m - s; j++)
		for(i = s; i < m - j; i++)
			if(A[i] < A[i + 1])
				t = A[i], A[i] = A[i + 1], A[i + 1] = t;
}
int main()
{
	int A[10];
	FILE *fr = fopen("/home/qiyu/code_1/sort.txt", "r");
	FILE *fw = fopen("/home/qiyu/code_1/result.txt", "w");
	for(int i = 0; i < 10; i++)
		fscanf(fr, "%d", &A[i]);
	fclose(fr);
	BubbleSort(A, 0, 9);
    for(int i = 0; i < 10; i++)
		fprintf(fw, "%d ",A[i]);
	fclose(fw);
	return 0;
}
