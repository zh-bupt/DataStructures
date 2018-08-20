#include<iostream>
#include "BinaryTree.h"
#include<stdlib.h>
#include<cstring>
using namespace std;

/*
*试给出判别一棵给定的二叉树是否是排序
*二叉树的算法，设二叉树以二叉链表表示。
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
		cout << "是排序二叉树" << endl;
	else
		cout << "不是排序二叉树" << endl; 
}
