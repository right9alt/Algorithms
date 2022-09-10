#pragma once
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
using namespace std;
class RBT
{
private:
class  RBTNode
{
public:
	
	//Поля кчд
	enum RBTColor { Black, Red, DoubleBlack = -1 };
	int* inf = new int;
	int color = Black;
	RBTNode* left = NULL;
	RBTNode* right = NULL;
	RBTNode* parent = NULL;
	//конструкторы кчд
	RBTNode(int i, int c, RBTNode* p, RBTNode* l, RBTNode* r)
	{
		*inf = i;
		color = c;
		parent = p;
		left = l;
		right = r;
	};
	RBTNode()
	{
		this->inf = nullptr;
		this->color = Black;
		this->parent = nullptr;
		this->left = new RBTNode(this->left);
		this->right = new RBTNode(this->right);
	};
	// NULL конструктор
	RBTNode(RBTNode* parent) {
		this->inf = nullptr;
		this->color = Black;
		this->parent = parent;
		this->left = nullptr;
		this->right = nullptr;
	}
	static RBTNode* sibling(RBTNode* node) {
		if (!node->parent)
			return nullptr;
		else
		{
			if (node == node->parent->left)
				return node->parent->right;
			else
				return node->parent->left;
		}
	};
	static RBTNode* uncle(RBTNode* node) {
		RBTNode* node_grandparent = grandparent(node);

		if (node_grandparent == nullptr) {
			return nullptr;
		}
		if (node->parent == node_grandparent->left) {
			return node_grandparent->right;
		}
		else {
			return node_grandparent->left;
		}
	}
	static RBTNode* grandparent(RBTNode* node) {
		if ((node != nullptr) && (node->parent != nullptr)) {
			return node->parent->parent;
		}
		return nullptr;
	}
	static bool isNIL(RBTNode*& node) {
		if (node != nullptr) {
			return (node->inf == nullptr
				&& node->right == nullptr
				&& node->left == nullptr);
		}
		return true;
	}


};

//25 50 75 60 68 10 18 15 6 3 7
//Правая рука
void rightRotate(RBTNode* x) {
	RBTNode* y = x->left;

	x->left = y->right;
	if (!RBTNode::isNIL(y->right)) y->right->parent = x;

	if (!RBTNode::isNIL(y)) y->parent = x->parent;
	if (x->parent) {
		if (x == x->parent->right)
			x->parent->right = y;
		else
			x->parent->left = y;
	}
	else {
		root = y;
	}

	y->right = x;
	if (!RBTNode::isNIL(x)) x->parent = y;
};
//левая рука
void leftRotate(RBTNode* x) {
	RBTNode* y = x->right;

	x->right = y->left;
	if (!RBTNode::isNIL(y->left)) y->left->parent = x;

	if (!RBTNode::isNIL(y)) y->parent = x->parent;
	if (x->parent) {
		if (x == x->parent->left)
			x->parent->left = y;
		else
			x->parent->right = y;
	}
	else {
		root = y;
	}

	y->left = x;
	if (!RBTNode::isNIL(x)) x->parent = y;
};


RBTNode* inorderPredecessor(RBTNode* start_node) {
	RBTNode* result_node = start_node;
	while (!RBTNode::isNIL(result_node->right)) {
		result_node = result_node->right;
	}
	return result_node;
}
// вставка
void InsertFixUp(RBTNode* node)
{
	while (node->parent && node->parent->color == RBTNode::Red) {
		RBTNode* node_grandparent = RBTNode::grandparent(node);
		RBTNode* node_uncle = RBTNode::uncle(node);
		bool node_uncle_exists = !RBTNode::isNIL(node_uncle);
		if (node_grandparent == nullptr) {
			return;
		}
		if (node->parent == node_grandparent->left) {
			if (node_uncle_exists && node_uncle->color == RBTNode::Red) {
				node->parent->color = RBTNode::Black;
				node_uncle->color = RBTNode::Black;
				node_grandparent->color = RBTNode::Red;
				node = node_grandparent;
			}
			else {
				if (node == node->parent->right) {
					node = node->parent;
					leftRotate(node);
				}
				node->parent->color = RBTNode::Black;
				node_grandparent->color = RBTNode::Red;
				rightRotate(node_grandparent);
			}
		}
		else {
			if (node_uncle_exists && node_uncle->color == RBTNode::Red) {
				node->parent->color = RBTNode::Black;
				node_uncle->color = RBTNode::Black;
				node_grandparent->color = RBTNode::Red;
				node = node_grandparent;
			}
			else {
				if (node == node->parent->left) {
					node = node->parent;
					rightRotate(node);
				}
				node->parent->color = RBTNode::Black;
				node_grandparent->color = RBTNode::Red;
				leftRotate(node_grandparent);
			}
		}
	}
	root->color = RBTNode::Black;
}
//удалить перестроить
void removeFixUp(RBTNode* node)
{
	if (node->color == RBTNode::Red
		&& RBTNode::isNIL(node->left)
		&& RBTNode::isNIL(node->right)) {
		if (node == node->parent->left) {
			node->parent->left = new RBTNode(node->parent);
			node = node->parent->left;
		}
		else {
			node->parent->right = new RBTNode(node->parent);
			node = node->parent->right;
		}
		return;
	}
	// Если удаляем чёрный.
	if (node->color == RBTNode::Black
		&& !RBTNode::isNIL(node->left)
		&& RBTNode::isNIL(node->right)) {
		*node->inf = *node->left->inf;
		removeFixUp(node->left);
		return;
	}
	if (node->color == RBTNode::Black
		&& RBTNode::isNIL(node->left)
		&& !RBTNode::isNIL(node->right)) {
		*node->inf = *node->right->inf;
		removeFixUp(node->right);
		return;
	}
	if (node->color != RBTNode::DoubleBlack
		&& !RBTNode::isNIL(node->left)
		&& !RBTNode::isNIL(node->right)) {
		RBTNode* in_succ = inorderPredecessor(node->left);
		*node->inf = *in_succ->inf;
		removeFixUp(in_succ);
		return;
	}
	if (node->color == RBTNode::Black
		&& RBTNode::isNIL(node->left)
		&& RBTNode::isNIL(node->right)) {
		node->inf = nullptr;
		node->left = nullptr;
		node->right = nullptr;
		node->color = RBTNode::DoubleBlack;
		removeFixUp(node);
		return;
	}
	// Doubleblack (чёрный лист)
	if (node->color == RBTNode::DoubleBlack) {
		if (node == root) {
			node->color = RBTNode::Black;
			return;
		}
		RBTNode* node_sibling = RBTNode::sibling(node);
		if (node_sibling->color == RBTNode::Black
			&& node_sibling->left->color == RBTNode::Black
			&& node_sibling->right->color == RBTNode::Black) {
			node->color = RBTNode::Black;
			node->parent->color--;
			node_sibling->color = RBTNode::Red;
			if (node->parent->color == RBTNode::DoubleBlack) {
				removeFixUp(node->parent);
			}
			return;
		}
		if (node_sibling->color == RBTNode::Red) {
			changeColors(node_sibling, node->parent);
			if (node == node->parent->left) {
				leftRotate(node->parent);
			}
			else {
				rightRotate(node->parent);
			}
				removeFixUp(node);
			return;
		}
		RBTNode*& near_child = (node == node->parent->left) ? node_sibling->left : node_sibling->right;
		RBTNode*& far_child = (node == node->parent->left) ? node_sibling->right : node_sibling->left;
		if (node_sibling->color == RBTNode::Black
			&& near_child->color == RBTNode::Red
			&& far_child->color == RBTNode::Black) {
			changeColors(node_sibling, near_child);
			if (node == node->parent->left) {
				rightRotate(node_sibling);
			}
			else {
				leftRotate(node_sibling);
			}
				removeFixUp(node);
			return;
		}
		if (node_sibling->color == RBTNode::Black
			&& far_child->color == RBTNode::Red) {
			changeColors(node->parent, node_sibling);
			if (node == node->parent->left) {
				leftRotate(node->parent);
			}
			else {
				rightRotate(node->parent);
			}
			node->color = RBTNode::Black;
			far_child->color = RBTNode::Black;
			return;
		}
	}

}
//смена цвета
void changeColors(RBTNode* node_x, RBTNode* node_y) {
	short x_color = node_x->color;
	node_x->color = node_y->color;
	node_y->color = x_color;
}

public:
	RBTNode* root;

	RBT() 
	{
		this->root = nullptr;
	}
	RBTNode* findNode(int inf)
	{
		RBTNode* node_to_find = this->root;
		while (*node_to_find->inf != inf) {
			if (*node_to_find->inf < inf) {
				node_to_find = node_to_find->right;
			}
			else {
				node_to_find = node_to_find->left;
			}
		}
		if (node_to_find == this->root &&
			*node_to_find->inf != inf) {
			return nullptr;
		}
		return node_to_find;
	}
	//вставляем узел и балансируем
	void insertNode(int elem) 
	{
		RBTNode* node_elem = nullptr;
		node_elem = new RBTNode(elem,
			RBTNode::Red,
			nullptr,
			new RBTNode(node_elem),
			new RBTNode(node_elem)
		);

		if (this->root == nullptr) {
			this->root = node_elem;
			node_elem->parent = nullptr;
		}
		else {
			RBTNode* node_x = this->root;
			RBTNode* node_y = new RBTNode;
			while (!RBTNode::isNIL(node_x)) {
				node_y = node_x;
				if (*node_elem->inf > *node_x->inf) {
					if (RBTNode::isNIL(node_x->right)) {
						break;
					}
					node_x = node_x->right;
				}
				else {
					if (RBTNode::isNIL(node_x->left)) {
						break;
					}
					node_x = node_x->left;
				}
			}
			node_elem->parent = node_y;
			if (*node_y->inf < *node_elem->inf) {
				node_y->right = node_elem;
			}
			else {
				node_y->left = node_elem;
			}
		}
		InsertFixUp(node_elem);
	}
	//удаляем узел и балансируем
	void delNode(int elem) 
	{
		RBTNode* node_to_delete = findNode(elem);
		if (node_to_delete == nullptr) {
			return;
		}
		removeFixUp(node_to_delete);
	}
	
	void inorder(RBTNode* node) {
		if (node && node->inf) {
			inorder(node->left);
			if (node->color == 0) {
				std::cout << *node->inf << " - Black" << std::endl;
			}
			else {
				std::cout << *node->inf << " - Red" << std::endl;
			}
			inorder(node->right);
		}
	}

	void postorder(RBTNode* node) {
		if (node && node->inf) {
			postorder(node->left);
			postorder(node->right);
			if (node->color == 0) {
				std::cout << *node->inf << " - Black" << std::endl;
			}
			else {
				std::cout << *node->inf << " - Red" << std::endl;
			}
		}
	}

	void preorder(RBTNode* node) {
		if (node && node->inf) {
			if (node->color == 0) {
				std::cout << *node->inf << " - Black" << std::endl;
			}
			else {
				std::cout << *node->inf << " - Red" << std::endl;
			}
			preorder(node->left);
			preorder(node->right);
		}
	}
};