#include <stdio.h>//подключение библиотек

#define n 3 //определение количеств элементов в столбце (н) и строке (м)
#define m 5 //м максимум 11

int filling(int matrix[][m]);//прототипы функций
int output(int matrix[][m]);
int rowsearch(int matrix[][m]);

int main(void)
{
	int matrix[n][m];
	filling(matrix);//заполнение матрицы
	output(matrix);//вывод матрицы
	rowsearch(matrix);//поиск строк с максимальной суммой элементов в них
	fflush(stdin);//ожидание действий пользователя
	getchar();
	return 0;
}

int filling(int matrix[][m])//заполнение
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
				matrix[i][j]=-rand()+2*rand();
			}
			else//если нечётная справа налево
			{
				matrix[i][m-j-1]=-rand()+2*rand();
			}
		}
	}
}

int output(int matrix[][m])//вывод
{
	int i,j;
	printf("Matrix:\n",matrix[i][j]);//заголовок
	for (i = 0; i < n; i++)//вывод матрицы
	{
		printf("|");//вывод разделителя
		for (j = 0; j < m; j++)
		{
			printf("%6d|",matrix[i][j]);//вывод элемента
		}
		printf("\n");//переход на следущую строчку
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
