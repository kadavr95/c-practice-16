//������������ ������ 16. ������� 4. ������� ������� (T02-01c). Dimini Inc. (c)2013
#include <stdio.h>//����������� ���������

#define n 5 //����������� ��������� ��������� � ������� (�) � ������ (�)
#define m n //� �������� 11

int filling(int matrix[][m]);//��������� �������
int output(int matrix[][m]);
int rowsearch(int matrix[][m]);
int fillfile(int matrix[][m]);
int readfile(int matrix[][m]);
 int search(int matrix[][m],char *string, int *ii);

int main(void)
{
	int matrix[n][m];
	filling(matrix);//���������� �������
	fillfile(matrix);
	readfile(matrix);
	output(matrix);//����� �������
	rowsearch(matrix);//����� ����� � ������������ ������ ��������� � ���
	fflush(stdin);//�������� �������� ������������
	getchar();
	return 0;
}

int filling(int matrix[][m])//����������
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
				matrix[i][j]=-rand()+2*rand();
			}
			else//���� �������� ������ ������
			{
				matrix[i][m-j-1]=-rand()+2*rand();
			}
		}
	}
}

int output(int matrix[][m])//�����
{
	int i,j;
	printf("Matrix:\n",matrix[i][j]);//���������
	for (i = 0; i < n; i++)//����� �������
	{
		printf("|");//����� �����������
		for (j = 0; j < m; j++)
		{
			printf("%6d|",matrix[i][j]);//����� ��������
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
	for (i = 1; i <=n ; i++)//���� �� ���� ���������
	{
		for (j = 1; j <= n; j++)
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
	for (ii = 1; ii <= n; ii++)//���� �� �������
	{
		fgets(fullstring,30*30,filepointer);//���������� ����������
		search(matrix,fullstring,&ii);//����� ��������� ����� � ������
	}
	fclose(filepointer);//�������� �����
}

 int search(int matrix[][m],char *string, int *ii)//����� ��������� ����� � ������
{
	int i,j=0,k=1;//����������� ����������
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
