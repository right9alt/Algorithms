#include <iostream>
using namespace std;



int* LSD(int* , int );
void countSort(int*, int, int);
int getMax(int*, int);
int* counting(int* ,int*,int );
ostream& operator<< (std::ostream& out, int* A)
{
	// Перегружаем оператор для удобного вывода массивов
	out << "Sort(";
	for (int i = 0; i < _msize(A)/sizeof(A[0]); i++)
	{
		out << A[i] << " ";
	}
	out << ")" << endl;
	return out;
}

int main()
{
	//counting
	int N;
	printf("N:= ");
	cin >> N;
	//создаем динамические массивы для демонстрации работы сортировки
	int* A = new int[N];
	int* B = new int[N] ;
	printf("COUNTING TIME!\n");
	for (int i = 0; i < N; i++)
	{//заполняем
		int tmp =  rand() % N;
		A[i] = tmp;
		B[i] = 0;
	}
	//выводим результат заполнения
	printf("Unsort( ");
	for (int i = 0; i < N; i++)
	{
		printf("%d ", A[i]);
	}
	printf(")\n");
	cout << counting(A, B, N);//выводим результат

	//lsd
	printf("LSD TIME!\n");

	for (int i = 0; i < N; i++)
	{
		int tmp = rand() % N;
		A[i] = tmp;
	}
	//выводим результат заполнения
	printf("Unsort( ");
	for (int i = 0; i < N; i++)
	{
		printf("%d ", A[i]);
	}
	printf(")\n");
	cout << LSD(A,N);//выводим результат
}
int* counting(int* A, int* B, int N)
{
	for (int i = 0; i < N; i++)
	{
		B[A[i]]++;//подсчитываем кол-во вхождений разных цифр
	}
	int k = 0;
	for (int i = 0; i < N; i++)
	{
		while (B[i] != 0)
		{
			A[k] = i;//заменяем значения нашего массива на кол-во вхождений числа i
			k++;
			B[i]--;
		}
	}
	return A;
}
int getMax(int* A, int N)//поиск max
{
	int mx = A[0];
	for (int i = 1; i < N; i++)
		if (A[i] > mx)
			mx = A[i];
	return mx;
}
void countSort(int* A, int N, int exp)
{
	int* output = new int[N]; // output array
	int* count = new int[10];
	for (int i = 0; i < 10; i++)
	{
		count[i] = 0;
	}
	int i;

	for (i = 0; i < N; i++)
		count[(A[i] / exp) % 10]++;

	for (i = 1; i < 10; i++)
		count[i] += count[i - 1];

	for (i = N - 1; i >= 0; i--) {
		output[count[(A[i] / exp) % 10] - 1] = A[i]; //собираем ответ
		count[(A[i] / exp) % 10]--;
	}

	for (i = 0; i < N; i++)
		A[i] = output[i];
}
int* LSD(int* A, int N)
{
	int m = getMax(A, N);
	for (int exp = 1; m / exp > 0; exp *= 10)
		countSort(A, N, exp);
	return A;
}
