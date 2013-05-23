//Самостоятельная работа 16. Вариант 1. Яскович Дмитрий (T02-01c). Govnokod Inc. (c)2013
#include <stdio.h>//подключение библиотек
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define n 5 //определение количеств элементов в столбце (н) и строке (м)
#define m n

int filling(int low, int up,int matrix[][m]);//прототипы функций
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
	printf("Enter limits: ");//ввод пределов
	scanf("%d %d", &low,&up);
	if (low>up)//обмен пределов
	{
		up=low-up;
		low=low-up;
		up=low+up;
	}
	filling(low,up,matrix);//заполнение матрицы
	fillfile(matrix);//ввод вывод (файл)
	readfile(matrix);
	output(matrix);//вывод матрицы
	for (i=0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			matrix2[i][j]=matrix[i][j];
		}
	}
	transpose(matrix2);//транспонирование
	multiply(matrix,matrix2,matrixres);//умножение
	for (i=0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			matrix[i][j]=matrixres[i][j];
		}
	}
	power(matrix,matrix,matrixres,2);//во вторую степень
	output(matrixres);//вывод
	fflush(stdin);//ожидание действий пользователя
	getchar();
	return 0;
}

int filling(int low,int up,int matrix[][m])//заполнение
{
	int i,j;
	int stime;
	long int ltime;
	ltime=time(NULL);//создание случайной последовательности
	stime=(unsigned) ltime/2;
	srand(stime);
	for (i = 0; i < n; i++)//заполнение матрицы
	{
		for (j = 0; j < m; j++)
		{
			if (i%2==1)//заполнение строки если чётная слева направо
			{
				matrix[i][j]=low+(up-low)*rand()/RAND_MAX;
			}
			else//если нечётная справа налево
			{
				matrix[i][m-j-1]=low+(up-low)*rand()/RAND_MAX;
			}
		}
	}
}

int output(int matrix[][m])//вывод
{
	int i,j;
	printf("Matrix:\n");//заголовок
	for (i = 0; i < n; i++)//вывод матрицы
	{
		printf("|");//вывод разделителя
		for (j = 0; j < m; j++)
		{
			printf("%10d|",matrix[i][j]);//вывод элемента
		}
		printf("\n");//переход на следущую строчку
	}
}



int fillfile(int matrix[][m])//заполнение файла элементами из массива
{
	int i,j;//определение переменных
	FILE *filepointer;
	char string[30];
	if ((filepointer = fopen("TEST","w"))==NULL)//создание файла
	{
		printf("Error while opening the file.\n");
		exit(1);
	}
	for (i = 0; i <n ; i++)//цикл по всем элементам
	{
		for (j = 0; j < n; j++)
		{
			ltoa(matrix[i][j],string,10);//перевод из числа в строку
			fputs(string,filepointer);//запись числа в строковом формате в файл
			fputs(" ",filepointer);
		}
		fputs("\n",filepointer);//переход на следующую строку
	}
	fclose(filepointer);//закрытие файла
 }
int readfile(int matrix[][m])//считывание из файла в массив
{
	int ii,j,pos,length;//определение переменных
	char fullstring[30*30];
	char string[30];
	FILE *filepointer;
	if ((filepointer = fopen("TEST","r"))==NULL)//открытие файла
	{
		printf("Error while opening the file.\n");
		exit(1);
	}
	for (ii = 0; ii < n; ii++)//цикл по строкам
	{
		fgets(fullstring,30*30,filepointer);//построчное считывание
		search(matrix,fullstring,&ii);//поиск отдельных чисел в строке
	}
	fclose(filepointer);//закрытие файла
}

 int search(int matrix[][m],char *string, int *ii)//поиск отдельных чисел в строке
{
	int i,j=0,k=0;//определение переменных
	char string1[100000],charword1[100000],symbol;
	memset(charword1,0,sizeof(charword1));//очистка переменной для текущего числа
	strcpy(string1,string);//сброс данных в локальную переменную
	for (i = 0; i < strlen(string1); i++)//цикл прохода строки
	{
		symbol=string1[i];//считывание символа
		if ((strchr(" ",symbol))|| (i==(strlen(string1)-1)))//условие конца числа или конца строки
		{
			if (i==(strlen(string1)-1))//действия в случае конца строки
			{
				charword1[i-j]=symbol;//завершение считывания числа
			}
			j=i+1;//изменение переменной отвечающей за место считанного символа в числе
			matrix[*ii][k]=atol(charword1);//перевод из строки в число и запись в массив
			k=k+1;//переход к следующему элементу массива
			memset(charword1,0,sizeof(charword1));//сброс переменной с числом
		}
		else//действия, если число ещё не закончилось
		{
			charword1[i-j]=symbol;//запись символа в переменную для числа
		}
	}
}


int rowsearch(int matrix[][m])//поиск строк с максимальной суммой элементов в них
{
	int sum,maxsum,i,j;
	maxsum=-m*100000;//начальное значение максимальной суммы элементов
	for (i = 0; i < n; i++)//определение максимального значения
	{
		sum=0;//обнуление суммы
		for (j = 0; j < m; j++)
		{
			sum=sum+matrix[i][j];//подсчёт новой суммы
		}
		if (sum>maxsum)//сравнение с максимальной суммой
		{
			maxsum=sum;//изменение максимальной суммы если она меньше новой
		}
	}
	printf("Rows with maximum sum of elements: ");//вывод заголовка
	for (i = 0; i < n; i++)//вывод номеров строк с максимальными суммами
	{
		sum=0;//обнуление суммы
		for (j = 0; j < m; j++)
		{
			sum=sum+matrix[i][j];//подсчёт новой суммы
		}
		if (sum==maxsum)//проверка равенства максимальной суммы и текущей
		{
			printf("%d ",i+1);//вывод номера строки
		}
	}
}

int transpose(int matrix[][m])
{
	int i,j,t;
	for (i = 0; i < n; i++)//транспонирование элементов
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
	for (i=0; i < n; i++)//сложение матриц
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
	for (i=0; i < n; i++)//очистка результирующей
	{
		for (j = 0; j < n; j++)
		{
			matrixres[i][j]=0;
		}
	}
	for (i=0; i < n; i++)//перемножение матриц
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
	for (i = pwr; i >1; i--)//возведение в степень
	{
		multiply(matrix,matrix2,matrixres);//перемножение матриц
		for (k=0; k < n; k++)
		{
			for (j = 0; j < n; j++)
			{
				matrix2[i][j]=matrixres[i][j];
			}
		}
	}
}
