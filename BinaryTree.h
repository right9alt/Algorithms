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
//���
struct tree {
	int inf;
	tree* right;
	tree* left;
	tree* parent;

};

tree* node(int x) {//��������� ����
	tree* n = new tree;
	n->inf = x;
	n->left = n->right = NULL;
	n->parent = NULL;
	return n;

}

void insert(tree*& tr, int x) {//�������
	tree* n = node(x);
	if (!tr) tr = n; //���� ������ ������ - ������
	else {
		tree* y = tr;
		while (y) { //���� ���� ���������
			if (n->inf >= y->inf) //������ �����
				if (y->right)
					y = y->right;
				else {
					n->parent = y; //���� ���������� ������ ��������
					y->right = n;
					break;
				}

			else if (n->inf < y->inf)//����� �����

				if (y->left)
					y = y->left;
				else {
					n->parent = y;//���� ���������� ����� ��������
					y->left = n;
					break;

				}
		}
	}
}
void add(tree*& tr, int value, int amount) {
	for (int i = 0; i < amount; i++)
	{
		insert(tr, value);
	}
}

void inorder(tree* tr) {//������������ �����
	if (tr) {
		inorder(tr->left);
		cout << tr->inf << " ";
		inorder(tr->right);
	}

}
void preorder(tree* tr) {//������������ �����
	if (tr) {
		cout << tr->inf << " ";
		inorder(tr->left);
		inorder(tr->right);
	}

}
void postorder(tree* tr) {//������������ �����
	if (tr) {
		inorder(tr->left);
		inorder(tr->right);
		cout << tr->inf << " ";
	}

}

tree* find(tree* tr, int x) {//�����
	if (!tr || x == tr->inf)//����� ��� ����� �� ����� �����
		return tr;
	if (x < tr->inf)
		return find(tr->left, x);//���� �� ����� �����
	else
		return find(tr->right, x);//���� �� ������ �����

}

tree* Min(tree* tr) {//����� min
	if (!tr->left) return tr;//��� ������ �������
	else return Min(tr->left);//���� �� ����� ����� �� �����

}

tree* Max(tree* tr) {//����� max
	if (!tr->right) return tr;//��� ������� �������
	else return Max(tr->right);//���� �� ������ ����� �� �����

}

tree* Next(tree* tr, int x) {//����� ����������
	tree* n = find(tr, x);

	if (n->right)//���� ���� ������ �������
		return Min(n->right);//min �� ������ �����
	tree* y = n->parent; //��������
	while (y && n == y->right) {//���� �� ����� �� ����� ��� ���� - ������ �������
		n = y;//���� ����� �� ������
		y = y->parent;

	}
	return y;//���������� ��������

}

tree* Prev(tree* tr, int x) {//����� �����������
	tree* n = find(tr, x);
	if (n->left)//���� ���� ����� �������
		return Max(n->left);//max �� ����� �����
	tree* y = n->parent;//��������
	while (y && n == y->left) {//���� �� ����� �� ����� ��� ���� - ����� �������
		n = y;//���� ����� �� ������
		y = y->parent;

	}
	return y;//���������� ��������

}

//void Delete(tree*& tr, tree* v) {//�������� ����
//	tree* p = v->parent;
//	if (!p) tr = NULL; //������ �������� ���� ����
//	else if (!v->left && !v->right) {//���� ��� �����
//		if (p->left == v) //��������� � �������� ������ �� NULL
//			p->left = NULL;
//		if (p->right == v)
//			p->right = NULL;
//		delete v;
//
//	}
//	else if (!v->left || !v->right) {//���� ������ ���� �������
//		if (!p) { //���� ������� ������, � �������� 1 �������
//			if (!v->left) { //���� ���� ������ �������
//				tr = v->right; //�� ���������� ������
//				v->parent = NULL;
//
//			}
//			else { //���������� ��� ������
//
//				tr = v->left;
//				v->parent = NULL;
//
//			}
//
//		}
//		else {
//			if (!v->left) {//���� ���� ������ �������
//				if (p->left == v) //���� ��������� ���� ���. ����� ��������
//					p->left = v->right; //������� ���������� ���� ���������� ����� �������� ������ "����"
//				else
//					p->right = v->right; ////������� ���������� ���� ���������� ������ �������� ������ "����"
//				v->right->parent = p; //��������� ������� ���������� ��� "���"
//
//			}
//			else {//���������� ��� ������ �������
//				if (p->left == v)
//					p->left = v->left;
//				else
//					p->right = v->left;
//				v->left->parent = p;
//
//			}
//			delete v;
//
//		}
//
//	}
//	else {//���� ��� �������
//		tree* succ = Next(tr, v->inf);//��������� �� ��������� �����
//		v->inf = succ->inf; //����������� ��������
//		if (succ->parent->left == succ) {//���� succ ����� �������
//			succ->parent->left = succ->right; //��� ������ ������� ���������� ����� �������� ������ "����"
//			if (succ->right) //���� ���� ������� ����������
//				succ->right->parent = succ->parent; //��� ��������� ���������� "���"
//
//		}
//		else {//���������� ���� succ - ����sq �������
//			succ->parent->right = succ->right;
//			if (succ->right)
//				succ->right->parent = succ->parent;
//
//		}
//		delete succ;
//	}

//}
int min(tree*& tr)
{
	if (node == NULL)
	{
		return INT_MIN;
	}
	if (tr->left != NULL)
	{
		return min(tr->left);
	}
	return tr->inf;
}
void remove(tree*& tr, int item)
{
	if (tr == NULL)
	{
		return;
	}
	else if (item < tr->inf)
	{
		remove(tr->left, item);
	}
	else if (item > tr->inf)
	{
		remove(tr->right, item);
	}
	else    // item == node->data
	{
		if (tr->right == NULL)
		{
			tr = tr->left;
		}
		else if (tr->left == NULL)
		{
			tr = tr->right;
		}
		else
		{
			int min_val = min(tr->right);
			remove(tr->right, min_val);
			tr->inf = min_val;
			return;
		}
	}
}