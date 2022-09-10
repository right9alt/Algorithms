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

//25 50 75 60 68 10 18 15 6 3 7
//udalit 18 potom 3

int main()
{
	setlocale(LC_ALL, "Russian");
	RBT* tree = new RBT();
	cout << "Сколько элементов в дереве?";
	int tmp;
	cin >> tmp;
	int x;
	for (int i = 0; i < tmp; i++)
	{
		cin >> x;
		tree->insertNode(x);
	}
	cout << "\nPreorder\n";
	tree->preorder(tree->root);
	cout << "\nInorder\n";
	tree->inorder(tree->root);
	cout << "\nPostorder\n";
	tree->postorder(tree->root);

	cout << "\nСколько элементов udalit?";
	cin >> tmp;
	for (int i = 0; i < tmp; i++)
	{
		cin >> x;
		tree->delNode(x);
		cout << "\nPreorder\n";
		tree->preorder(tree->root);
	}
	return 0;
}

