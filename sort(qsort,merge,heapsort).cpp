#include <vector>
#include <iostream>
#include <ctime>
#include <random>

using namespace std;


//dannie testng
vector<int> test { 50000,100000,500000,1000000 };
//vector<int> test{ 15,43,54,1,3,7,9,0,8,76,1 }; //testvector
//for random
std::random_device rd;
std::mt19937 mersenne(rd());
//qsort testng
void qsort(vector<int>& a, int l, int r)
{
	int i = l;
	int j = r;
	int el = a[(l + r) / 2];

	while (i <= j)
	{
		while (a[i] < el)
		{
			i++;
		}
		while (a[j] > el)
		{
			j--;
		}
		if (i <= j)
		{
			swap(a[i], a[j]);
			j--;
			i++;
		}
	}
	if (j > l)
	{
		qsort(a, l, j);
	}
	if (i < r)
	{
		qsort(a, i, r);
	}
}

//функции для пирамидальной сортировки

void downheap(vector<int>& a, long k, long n)
{
	
	int new_elem;
	long child;
	new_elem = a[k];
	while (k <= n / 2) 
	{
		child = 2 * k;
		if (child < n && a[child] < a[child + 1])  
			child++;
		if (new_elem >= a[child])
			break;
		a[k] = a[child];    
		k = child;
	}
	a[k] = new_elem;
}

void heapsort(vector<int> &a, long size)
{
	long i;
	int temp;
	for (i = size / 2 - 1; i >= 0; --i)
		downheap(a, i, size - 1);

	for (i = size - 1; i > 0; --i)
	{
		temp = a[i];
		a[i] = a[0];
		a[0] = temp;
		downheap(a, 0, i - 1);
	}
}

void merge(vector<int>& a, int left,int mid, int right)
{
	int it1 = 0;
	int it2 = 0;
	vector<int> result(right - left);
	while (left + it1 < mid && mid + it2 < right)
	{
		if (a[left + it1] < a[mid +it2])
		{
			result[it1 + it2] = a[left + it1];
			it1 += 1;
		}
		else
		{
			result[it1 + it2] = a[mid + it2];
			it2 += 1;
		}
	}
		while (left + it1 < mid)
		{
			result[it1 + it2] = a[left + it1];
			it1 += 1;
		}
		while (mid + it2 < right)
		{
			result[it1 + it2] = a[mid + it2];
			it2 += 1;
		}
		for (int i = 0; i < it1 + it2; i++)
		{
			a[left + i] = result[i];
		} 
				
	
	
};
//рекурсивная процедура сортировки
void mergeSortRecursive(vector<int>& a, int left, int right)
{
	if (left + 1 >= right)
		return;
	int mid = (left + right) / 2;
	mergeSortRecursive(a, left, mid);
	mergeSortRecursive(a, mid, right);
	merge(a, left, mid, right);
}

int main() 
{
	//qsort testing
	cout << "qsort time:\n";
	std::clock_t start;
	double duration;
	vector <vector<float>> t(5, vector<float>(4));//для подсчета среднего по сортировке
	for (int k = 0; k < 5; k++)
	{
		for (int i = 0; i < 4; i++)
		{
			vector<int> TMP(test[i]);
			for (int j = 0; j < test[i]; j++)
			{
				TMP[j] = mersenne();
			}
			start = clock();
			qsort(TMP, 0, TMP.size() - 1);
			duration = (clock() - start) / (double)CLOCKS_PER_SEC;
			t[k][i] = duration;
		}
	}
	for (int i = 0; i < 4; i++)
	{
		float answ = 0;
		cout << "sreednee ot " << test[i] << " :";
		for (int j = 0; j < 5; j++)
		{
			answ += t[j][i];
		}
		cout <<answ/5.f << "\n";
	}
	//heap testing
	 cout << "heapsort time:\n";
	for (int k = 0; k < 5; k++)
	{
		for (int i = 0; i < 4; i++)
		{
			vector<int> TMP(test[i]);
			for (int j = 0; j < test[i]; j++)
			{
				TMP[j] = mersenne();
			}
			start = clock();
			heapsort(TMP,TMP.size());
			duration = (clock() - start) / (double)CLOCKS_PER_SEC;
			t[k][i] = duration;
		}
	}
	for (int i = 0; i < 4; i++)
	{
		float answ = 0;
		cout << "sreednee ot " << test[i] << " :";
		for (int j = 0; j < 5; j++)
		{
			answ += t[j][i];
		}
		cout << answ / 5.f << "\n";
	}
	//Merge
	cout << "Mergesort time:\n";
	for (int k = 0; k < 5; k++)
	{
		for (int i = 0; i < 4; i++)
		{
			vector<int> TMP(test[i]);
			for (int j = 0; j < test[i]; j++)
			{
				TMP[j] = mersenne();
			}
			start = clock();
			mergeSortRecursive(TMP, 0,TMP.size()-1);
			duration = (clock() - start) / (double)CLOCKS_PER_SEC;
			t[k][i] = duration;
		}
	}
	for (int i = 0; i < 4; i++)
	{
		float answ = 0;
		cout << "sreednee ot " << test[i] << " :";
		for (int j = 0; j < 5; j++)
		{
			answ += t[j][i];
		}
		cout << answ / 5.f << "\n";
	}
	//test method
	/*heapsort(test, test.size());
	for (int i = 0; i < test.size(); i++)
	{
		cout << test[i] << " ";
	}*/
}
