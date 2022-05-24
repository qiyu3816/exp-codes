#include <stdio.h>
void QuickSort(int A[], int s, int m)
{
	int i, j, t;
	if(s < m)
	{
		i = s;
		j = m + 1;
		while(1)
		{
			while(i + 1 < s + m && A[++i] > A[s]);
			while(j - 1 > -1 && A[--j] < A[s]);
			if(i >= j) break;
			t = A[i], A[i] = A[j], A[j] = t;
		}
		t = A[s], A[s] = A[j], A[j] = t;
		QuickSort(A, s, j - 1);
		QuickSort(A, j + 1, m);
	}
} 
int main()
{
	int A[10];
	FILE *fr = fopen("/home/qiyu/code_1/sort.txt", "r");
	FILE *fw = fopen("/home/qiyu/code_1/result.txt", "w");
	for (int i = 0; i < 10; i++)
	{
		fscanf(fr, "%d", &A[i]);
	}
	fclose(fr);
    QuickSort(A, 0, 9);
	for(int i = 0; i < 10; i++)
	{
		fprintf(fw, "%d ", A[i]);
	}
	fclose(fw);
	return 0;
}
