#include<iostream>
#include "BinaryTree.h"
#include<stdlib.h>
#include<cstring>
using namespace std;

/*
*�Ը����б�һ�ø����Ķ������Ƿ�������
*���������㷨����������Զ��������ʾ��
*/ 
bool isBST(BitTree T){
	if(!T)  return true;
	if(!T->rchild&&!T->rchild)  return true;
	if(!T->rchild)  return T->lchild->data > T->data ? false:true;
	if(!T->lchild)  return T->rchild->data < T->data ? false:true;
	return T->lchild->data < T->data && T->rchild->data > T->data ? isBST(T->lchild)&&isBST(T->rchild) : false;
} 

int main(){
	BitTree t;
	CreateBitTree(t);
	DisplayBitTree(t);
	if(isBST(t))
		cout << "�����������" << endl;
	else
		cout << "�������������" << endl; 
}
