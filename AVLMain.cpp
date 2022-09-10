#include "AVLtree.h"

#include "iostream"
using namespace std;

//25 50 75 60 68 10 18 15 6 3 7
//удалить 50
int main()
{
	node* root = nullptr;

	cout << "Skolko elementov dobavit?";
	int x; cin >> x; int tmp;
	for (int i = 0; i < x; i++)
	{
		cout << "Current Element: ";
		cin >> tmp;
		root = insert(root, tmp);
	}
	cout << "\nPostorder\n";
	postorder(root);
	cout << "\nInorder\n";
	inorder(root);
	cout << "\nPreorder\n";
	preorder(root);
	cout << "Skolko elementov udalit?";
	cin >> x; 
	for (int i = 0; i < x; i++)
	{
		cout << "Current Element: ";
		cin >> tmp;
		root = delete_node(root, tmp);
		cout << "\nPreorder\n";
		preorder(root);
		cout << "\nPostorder\n";
		postorder(root);
		cout << "\nInorder\n";
		inorder(root);
	}
	cout << "\nPreorder\n";
	preorder(root);
	cout << "\nPostorder\n";
	postorder(root);
	cout << "\nInorder\n";
	inorder(root);

}