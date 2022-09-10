#include "iostream"
using namespace std;
struct node // структура для представления узлов дерева
{
	int inf;
	unsigned char height;
	node* left;
	node* right;
	node(int k) { inf = k; left = right = 0; height = 1; }
	
};

unsigned char height(node* p)
{
	return p ? p->height : 0;
}

int bfactor(node* p)
{
	return height(p->right) - height(p->left);
}

void fixheight(node* p)
{
	unsigned char hl = height(p->left);
	unsigned char hr = height(p->right);
	p->height = (hl > hr ? hl : hr) + 1;
}

node* rotateright(node* p) // правый поворот вокруг p
{
	node* q = p->left;
	p->left = q->right;
	q->right = p;
	fixheight(p);
	fixheight(q);
	return q;
}

node* rotateleft(node* q) // левый поворот вокруг q
{
	node* p = q->right;
	q->right = p->left;
	p->left = q;
	fixheight(q);
	fixheight(p);
	return p;
}

node* balance(node* p) // балансировка узла p
{
	fixheight(p);
	if (bfactor(p) == 2)
	{
		if (bfactor(p->right) < 0)
			p->right = rotateright(p->right);
		return rotateleft(p);
	}
	if (bfactor(p) == -2)
	{
		if (bfactor(p->left) > 0)
			p->left = rotateleft(p->left);
		return rotateright(p);
	}
	return p; // балансировка не нужна
}

node* insert(node* p, int k) // вставка ключа k в дерево с корнем p
{
	if (!p) return new node(k);
	if (k < p->inf)
		p->left = insert(p->left, k);
	else
		p->right = insert(p->right, k);
	return balance(p);
}

node* findmin(node* p) // поиск узла с минимальным ключом в дереве p 
{
	return p->right ? findmin(p->right) : p;
}

node* removemin(node* p) // удаление узла с минимальным ключом из дерева p
{
	if (p->left == 0)
		return p->right;
	p->left = removemin(p->left);
	return balance(p);
}
node* delete_node(node* current_node, int elem) {
	if (current_node == nullptr) {
		return nullptr;
	}
	else if (elem > current_node->inf) {
		current_node->right = delete_node(current_node->right, elem);
		current_node = balance(current_node);
	}
	else if (elem < current_node->inf) {
		current_node->left = delete_node(current_node->left, elem);
		current_node = balance(current_node);
	}
	else {
		if (current_node->right != nullptr) {
			node* in_pred = findmin(current_node->left);
			current_node->inf = in_pred->inf;
			current_node->left = delete_node(current_node->left, in_pred->inf);

			current_node->height = height(current_node);
			current_node = balance(current_node);
		}
		else {
			current_node->height = height(current_node);
			current_node = balance(current_node);
			return current_node->left;
		}
	}
	current_node->height = height(current_node);
	return current_node;
}

node* remove(node* p, int k) // удаление ключа k из дерева p
{
	if (!p) return 0;
	if (k < p->inf)
		p->left = remove(p->left, k);
	else if (k > p->inf)
		p->right = remove(p->right, k);
	else //  k == p->key 
	{
		node* q = p->left;
		node* r = p->right;
		delete p;
		if (!r) return q;
		node* min = findmin(r);
		min->right = removemin(r);
		min->left = q;
		return balance(min);
	}
	return balance(p);
}
void postorder(node* node) {
	if (node && node->inf) {
		postorder(node->left);
		postorder(node->right);
		cout << node->inf << endl;
	}
}

void inorder(node* node) {
	if (node && node->inf) {
		
		inorder(node->left);
		cout << node->inf << endl;
		inorder(node->right);
	}
}

void preorder(node* node) {
	if (node && node->inf) {
		cout << node->inf << endl;
		preorder(node->left);
		preorder(node->right);
	}
}