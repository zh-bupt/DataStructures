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
*����һ���ַ�������һ�����������ַ���������
*�ַ�����������
*           ---------------------------------> "#" ------------------------------->
*          /                                                                       \
*BitTree ----> ��д��ĸ ----> "(" -----> BitTree ----> "," ----> BitTree ----> ")" ---->
*                        \                                                         /
*                         -------------------------------------------------------->
*/

void OperateString(const char* s,char* s1,char* s2){
	int i = 2,flag = 0;
	if(s[0] != '\0'&&s[1] == '\0')  s1[0] = s2[0] = '#';//��sΪһ����������ĸ,��������������Ϊ��
	else{
		for (; s[i] != ',' || flag != 0; i++){			//����������
			s1[i-2] = s[i];
			if(s[i] == '(')  flag++;
			if(s[i] == ')')  flag--;
		}//for
		int j = ++i;									//�ӵ�����
		for(; s[j] != '\0'; j++)  s2[j-i] = s[j];		//����������
		s2[j-i-1] = '\0';								//�ӵ����һ��������
	}//else
}

BitTree CreateBitTree(const char* s){			//����һ���ַ�������һ��������
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


/*����ǰ�����������������л�ԭһ�����������ַ���������*/
void OperateString(char* pre,char* in,char* preOrder_1,char* inOrder_1,char* preOrder_2,char* inOrder_2){
	char root=pre[0];
	int i=0;
	for(;in[i]!=root;i++)  inOrder_1[i]=in[i];				//�����������������������
	int j=++i;
	for(;in[j]!='\0';j++)  inOrder_2[j-i]=in[j];			//�����������������������
	int k=1,l=0;
	for(;k<i&&pre[k]!='\0';k++,l++)  preOrder_1[l]=pre[k];	//������������ǰ���������
	l=0;
	for(;pre[k]!='\0';k++,l++)  preOrder_2[l]=pre[k];		//������������ǰ���������
}

BitTree CreateBitTree(char* pre,char* in){		//���ݶ�������ǰ�������������ַ������л�ԭ������
	if(pre[0] == '\0' || in[0] == '\0')  return NULL;	//��һ������Ϊ���򷵻ؿ���
	BitTree root = new TreeNode;					//ǰ������ĵ�һ���ַ�һ��Ϊ���ڵ�,�������ڵ�
	root->data = (ElemType)pre[0];
	char pre1[100] = {'\0'},in1[100]={'\0'},pre2[100]={'\0'},in2[100]={'\0'};
	OperateString(pre,in,pre1,in1,pre2,in2);	//��ǰ��������������ǰ�����������
	root->lchild = CreateBitTree(pre1,in1);		//��ԭ������
	root->rchild = CreateBitTree(pre2,in2);		//��ԭ������
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
*�԰�������ʽ��ӡһ�ö�����,
*��������ʽ��ʵ�Ǵ���ε����������,
*��ʼֵlevelΪ1
*/
void DisplayBitTree(BitTree T,int level=1){
	if(!T)  return;
	DisplayBitTree(T->rchild,level+1);
	for(int i=1;i<level;i++)  std::cout<<"  ";
	std::cout<<T->data<<std::endl;
	DisplayBitTree(T->lchild,level+1);
}

#endif
