//��������������� ������ 16. ������� 1. ������� ������� (T02-01c). Govnokod Inc. (c)2013
#include <stdio.h>//����������� ���������
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define n 5 //����������� ��������� ��������� � ������� (�) � ������ (�)
#define m n

int filling(int low, int up,int matrix[][m]);//��������� �������
int output(int matrix[][m]);
int rowsearch(int matrix[][m]);
int fillfile(int matrix[][m]);
int readfile(int matrix[][m]);
 int search(int matrix[][m],char *string, int *ii);
 int transpose(int matrix[][m]);
 int sum(int matrix[][m], int matrix2[][m], int matrixres[][m]);
 int multiply(int matrix[][m], int matrix2[][m], int matrixres[][m]);
 int power(int matrix[][m], int matrix2[][m], int matrixres[][m], int pwr);

int main(void)
{
	int matrix[n][m],matrix2[n][m],matrixres[n][m],low,up,i,j;
	printf("Enter limits: ");//���� ��������
	scanf("%d %d", &low,&up);
	if (low>up)//����� ��������
	{
		up=low-up;
		low=low-up;
		up=low+up;
	}
	filling(low,up,matrix);//���������� �������
	fillfile(matrix);//���� ����� (����)
	readfile(matrix);
	output(matrix);//����� �������
	for (i=0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			matrix2[i][j]=matrix[i][j];
		}
	}
	transpose(matrix2);//����������������
	multiply(matrix,matrix2,matrixres);//���������
	for (i=0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			matrix[i][j]=matrixres[i][j];
		}
	}
	power(matrix,matrix,matrixres,2);//�� ������ �������
	output(matrixres);//�����
	fflush(stdin);//�������� �������� ������������
	getchar();
	return 0;
}

int filling(int low,int up,int matrix[][m])//����������
{
	int i,j;
	int stime;
	long int ltime;
	ltime=time(NULL);//�������� ��������� ������������������
	stime=(unsigned) ltime/2;
	srand(stime);
	for (i = 0; i < n; i++)//���������� �������
	{
		for (j = 0; j < m; j++)
		{
			if (i%2==1)//���������� ������ ���� ������ ����� �������
			{
				matrix[i][j]=low+(up-low)*rand()/RAND_MAX;
			}
			else//���� �������� ������ ������
			{
				matrix[i][m-j-1]=low+(up-low)*rand()/RAND_MAX;
			}
		}
	}
}

int output(int matrix[][m])//�����
{
	int i,j;
	printf("Matrix:\n");//���������
	for (i = 0; i < n; i++)//����� �������
	{
		printf("|");//����� �����������
		for (j = 0; j < m; j++)
		{
			printf("%10d|",matrix[i][j]);//����� ��������
		}
		printf("\n");//������� �� �������� �������
	}
}



int fillfile(int matrix[][m])//���������� ����� ���������� �� �������
{
	int i,j;//����������� ����������
	FILE *filepointer;
	char string[30];
	if ((filepointer = fopen("TEST","w"))==NULL)//�������� �����
	{
		printf("Error while opening the file.\n");
		exit(1);
	}
	for (i = 0; i <n ; i++)//���� �� ���� ���������
	{
		for (j = 0; j < n; j++)
		{
			ltoa(matrix[i][j],string,10);//������� �� ����� � ������
			fputs(string,filepointer);//������ ����� � ��������� ������� � ����
			fputs(" ",filepointer);
		}
		fputs("\n",filepointer);//������� �� ��������� ������
	}
	fclose(filepointer);//�������� �����
 }
int readfile(int matrix[][m])//���������� �� ����� � ������
{
	int ii,j,pos,length;//����������� ����������
	char fullstring[30*30];
	char string[30];
	FILE *filepointer;
	if ((filepointer = fopen("TEST","r"))==NULL)//�������� �����
	{
		printf("Error while opening the file.\n");
		exit(1);
	}
	for (ii = 0; ii < n; ii++)//���� �� �������
	{
		fgets(fullstring,30*30,filepointer);//���������� ����������
		search(matrix,fullstring,&ii);//����� ��������� ����� � ������
	}
	fclose(filepointer);//�������� �����
}

 int search(int matrix[][m],char *string, int *ii)//����� ��������� ����� � ������
{
	int i,j=0,k=0;//����������� ����������
	char string1[100000],charword1[100000],symbol;
	memset(charword1,0,sizeof(charword1));//������� ���������� ��� �������� �����
	strcpy(string1,string);//����� ������ � ��������� ����������
	for (i = 0; i < strlen(string1); i++)//���� ������� ������
	{
		symbol=string1[i];//���������� �������
		if ((strchr(" ",symbol))|| (i==(strlen(string1)-1)))//������� ����� ����� ��� ����� ������
		{
			if (i==(strlen(string1)-1))//�������� � ������ ����� ������
			{
				charword1[i-j]=symbol;//���������� ���������� �����
			}
			j=i+1;//��������� ���������� ���������� �� ����� ���������� ������� � �����
			matrix[*ii][k]=atol(charword1);//������� �� ������ � ����� � ������ � ������
			k=k+1;//������� � ���������� �������� �������
			memset(charword1,0,sizeof(charword1));//����� ���������� � ������
		}
		else//��������, ���� ����� ��� �� �����������
		{
			charword1[i-j]=symbol;//������ ������� � ���������� ��� �����
		}
	}
}


int rowsearch(int matrix[][m])//����� ����� � ������������ ������ ��������� � ���
{
	int sum,maxsum,i,j;
	maxsum=-m*100000;//��������� �������� ������������ ����� ���������
	for (i = 0; i < n; i++)//����������� ������������� ��������
	{
		sum=0;//��������� �����
		for (j = 0; j < m; j++)
		{
			sum=sum+matrix[i][j];//������� ����� �����
		}
		if (sum>maxsum)//��������� � ������������ ������
		{
			maxsum=sum;//��������� ������������ ����� ���� ��� ������ �����
		}
	}
	printf("Rows with maximum sum of elements: ");//����� ���������
	for (i = 0; i < n; i++)//����� ������� ����� � ������������� �������
	{
		sum=0;//��������� �����
		for (j = 0; j < m; j++)
		{
			sum=sum+matrix[i][j];//������� ����� �����
		}
		if (sum==maxsum)//�������� ��������� ������������ ����� � �������
		{
			printf("%d ",i+1);//����� ������ ������
		}
	}
}

int transpose(int matrix[][m])
{
	int i,j,t;
	for (i = 0; i < n; i++)//���������������� ���������
	{
		for (j = 0; j < i; j++)
		{
			t=matrix[i][j];
			matrix[i][j]=matrix[j][i];
			matrix[j][i]=t;
		}
	}
}

int sum(int matrix[][m], int matrix2[][m], int matrixres[][m])
{
	int i,j;
	for (i=0; i < n; i++)//�������� ������
	{
		for (j = 0; j < n; j++)
		{
			matrixres[i][j]=matrix2[i][j]+matrix[i][j];
		}
	}
}
int multiply(int matrix[][m], int matrix2[][m], int matrixres[][m])
{
	int i,j,k;
	for (i=0; i < n; i++)//������� ��������������
	{
		for (j = 0; j < n; j++)
		{
			matrixres[i][j]=0;
		}
	}
	for (i=0; i < n; i++)//������������ ������
	{
		for (j = 0; j < n; j++)
		{
			for (k = 0; k < n; k++)
			{
			 matrixres[i][j]=matrixres[i][j]+matrix2[i][k]*matrix[k][j];
			}
		}
	}
}
int power(int matrix[][m], int matrix2[][m], int matrixres[][m], int pwr)
{
int i,j,k;
	for (i = pwr; i >1; i--)//���������� � �������
	{
		multiply(matrix,matrix2,matrixres);//������������ ������
		for (k=0; k < n; k++)
		{
			for (j = 0; j < n; j++)
			{
				matrix2[i][j]=matrixres[i][j];
			}
		}
	}
}
