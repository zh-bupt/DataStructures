#include<iostream>
#include<stdlib.h>
#include<cstring>

#define ElemType int
#ifndef BINARY_TREE
#define BINARY_TREE

typedef struct TreeNode{
	ElemType data;
	struct TreeNode * lchild,* rchild;
}TreeNode,* BitTree;

void visit(char c){
	std::cout << c << ' ';
}

/*
*根据一个字符串创建一个二叉树的字符串处理函数
*字符串构造如下
*           ---------------------------------> "#" ------------------------------->
*          /                                                                       \
*BitTree ----> 大写字母 ----> "(" -----> BitTree ----> "," ----> BitTree ----> ")" ---->
*                        \                                                         /
*                         -------------------------------------------------------->
*/

void OperateString(const char* s,char* s1,char* s2){
	int i = 2,flag = 0;
	if(s[0] != '\0'&&s[1] == '\0')  s1[0] = s2[0] = '#';//若s为一个单独的字母,则其左右子树均为空
	else{
		for (; s[i] != ',' || flag != 0; i++){			//复制左子树
			s1[i-2] = s[i];
			if(s[i] == '(')  flag++;
			if(s[i] == ')')  flag--;
		}//for
		int j = ++i;									//扔掉逗号
		for(; s[j] != '\0'; j++)  s2[j-i] = s[j];		//复制右子树
		s2[j-i-1] = '\0';								//扔掉最后一个反括号
	}//else
}

BitTree CreateBitTree(const char* s){			//根据一个字符串创建一个二叉树
	if (s[0] == '#' || s[0] == '\0')  return NULL;
	else{
		BitTree t = new TreeNode;
		t->data = (ElemType)s[0];
		char s1[100] = {'\0'},s2[100]={'\0'};
		OperateString(s,s1,s2);
		t->lchild = CreateBitTree(s1);
		t->rchild = CreateBitTree(s2);
		return t;
	}
}


/*根据前序遍历和中序遍历序列还原一个二叉树的字符串处理函数*/
void OperateString(char* pre,char* in,char* preOrder_1,char* inOrder_1,char* preOrder_2,char* inOrder_2){
	char root=pre[0];
	int i=0;
	for(;in[i]!=root;i++)  inOrder_1[i]=in[i];				//复制左子树的中序遍历序列
	int j=++i;
	for(;in[j]!='\0';j++)  inOrder_2[j-i]=in[j];			//复制右子树的中序遍历序列
	int k=1,l=0;
	for(;k<i&&pre[k]!='\0';k++,l++)  preOrder_1[l]=pre[k];	//复制左子树的前序遍历序列
	l=0;
	for(;pre[k]!='\0';k++,l++)  preOrder_2[l]=pre[k];		//复制右子树的前序遍历序列
}

BitTree CreateBitTree(char* pre,char* in){		//根据二叉树的前序和中序遍历的字符串序列还原二叉树
	if(pre[0] == '\0' || in[0] == '\0')  return NULL;	//若一种序列为空则返回空树
	BitTree root = new TreeNode;					//前序遍历的第一个字符一定为根节点,创建根节点
	root->data = (ElemType)pre[0];
	char pre1[100] = {'\0'},in1[100]={'\0'},pre2[100]={'\0'},in2[100]={'\0'};
	OperateString(pre,in,pre1,in1,pre2,in2);	//将前序拆成左右子树的前序和中序序列
	root->lchild = CreateBitTree(pre1,in1);		//还原左子树
	root->rchild = CreateBitTree(pre2,in2);		//还原右子树
	return root;
}

int CreateBitTree(BitTree &T){
	ElemType e;
	std::cin >> e;
	if (e == -1)  T = NULL;
	else{
		if (!(T = new TreeNode))  return 0;
		T->data = e;
		CreateBitTree(T->lchild);
		CreateBitTree(T->rchild);
		return 1;
	}
}

/*
*以凹入表的形式打印一棵二叉树,
*凹入表的形式其实是带层次的逆中序遍历,
*初始值level为1
*/
void DisplayBitTree(BitTree T,int level=1){
	if(!T)  return;
	DisplayBitTree(T->rchild,level+1);
	for(int i=1;i<level;i++)  std::cout<<"  ";
	std::cout<<T->data<<std::endl;
	DisplayBitTree(T->lchild,level+1);
}

#endif
