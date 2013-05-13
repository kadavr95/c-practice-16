#include <stdio.h>

#define n 3
#define m 5 //max allowed 11

int filling(int matrix[][m]);
int output(int matrix[][m]);

int main(void)
{
	int matrix[n][m];
	filling(matrix);
	output(matrix);
	fflush(stdin);//ожидание действий пользователя
	getchar();
	return 0;
}

int filling(int matrix[][m])
{
	int i,j;//определение переменных
	int stime;
	long int ltime;
	ltime=time(NULL);//создание случайной последовательности
	stime=(unsigned) ltime/2;
	srand(stime);
	for (i = 0; i < n; i++)//заполнение массива
	for (j = 0; j < m; j++)
	{
	 if (i%2==0)
	 {
		matrix[i][j]=-rand()+2*rand();
	 }
	 else
	 {
		matrix[i][m-j-1]=-rand()+2*rand();
     }
	}
}

int output(int matrix[][m])
{
	int i,j;
	printf("Matrix:\n",matrix[i][j]);
	for (i = 0; i < n; i++)
	{
		printf("|");
	 for (j = 0; j < m; j++)
	 {
		printf("%6d|",matrix[i][j]);
	 }
	 printf("\n");
	}
}
