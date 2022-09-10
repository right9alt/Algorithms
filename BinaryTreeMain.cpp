#include <iostream>
#include<algorithm>
#include <string>
#include <sstream>
#include<vector>
#include<math.h>
#include <iomanip>
#include <map>
#include<set>
#include <fstream>
#include <numeric>
#include <queue>
#include"Tree.h"
using namespace std;
int main()
{
	//заполнение бинарного дерева
	int n, x;
	int count = 0;
	cout << "n "; cin >> n;
	tree* tr = NULL;
	cout << endl << "Zapolnite derevo" << endl;
	for (int i = 0; i < n; i++)
	{
		cin >> x;
		insert(tr, x);
	}
	cout << "Kakoy element naiti v dereve? -  x: ";
	cin >> x;
	if (find(tr,x)!=NULL)
	{
		cout << "X naiden!\n";
	}
	else
	{
		cout << "X ne naiden!\n";
	}
	int mm;
	cout << "skolko dobavit? -  amount: ";
	cin >> mm;
	for (int i = 0; i < mm; i++)
	{
		cout << "Kakoy element dobavit v derevo? -  x: ";
		cin >> x;
		insert(tr, x);
	}
	
	cout << "Kakoy element udalit v dereve? -  x: ";
	cin >> x;
	if (find(tr, x) != NULL)
	{
		remove(tr, find(tr, x)->inf);
		cout << "X Udalen!\n";
	}
	else
	{
		cout << "X ne naiden!\n";
	}
	cout << "Vashe derevo vivedeno inorder obhodom" << endl;
	inorder(tr); cout << endl;
	cout << "Vashe derevo vivedeno preorder obhodom" << endl;
	preorder(tr); cout << endl;
	cout << "Vashe derevo vivedeno postorder obhodom" << endl;
	postorder(tr); cout << endl;

}