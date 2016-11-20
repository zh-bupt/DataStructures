#include<iostream>
#include<stdlib.h>
#include<cstring>
using namespace std;

#define ElemType char
#ifndef BINARY_TREE
#define BINARY_TREE

typedef struct TreeNode{
	ElemType data;
	struct TreeNode * lchild,* rchild;
}TreeNode,* BitTree;

void visit(char c){
	cout<<c<<' ';
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
	int i=2,flag=0;
	if(s[0]!='\0'&&s[1]=='\0')  s1[0]=s2[0]='#';//��sΪһ����������ĸ,��������������Ϊ�� 
	else{
		for(;s[i]!=','||flag!=0;i++){			//���������� 
			s1[i-2]=s[i];
			if(s[i]=='(')  flag++;
			if(s[i]==')')  flag--;
		}//for 
		int j=++i;								//�ӵ����� 
		for(;s[j]!='\0';j++)  s2[j-i]=s[j];		//���������� 
		s2[j-i-1]='\0';							//�ӵ����һ�������� 
	}//else
}

BitTree CreateBitTree(const char* s){			//����һ���ַ�������һ�������� 
	if(s[0]=='#'||s[0]=='\0')  return NULL;
	else{
		BitTree t=new TreeNode;
		t->data=s[0];
		char s1[100]={'\0'},s2[100]={'\0'};
		OperateString(s,s1,s2);
		t->lchild=CreateBitTree(s1);
		t->rchild=CreateBitTree(s2);
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
	root->data = pre[0];		
	char pre1[100] = {'\0'},in1[100]={'\0'},pre2[100]={'\0'},in2[100]={'\0'};
	OperateString(pre,in,pre1,in1,pre2,in2);	//��ǰ��������������ǰ����������� 
	root->lchild = CreateBitTree(pre1,in1);		//��ԭ������ 
	root->rchild = CreateBitTree(pre2,in2);		//��ԭ������ 
	return root;
} 

int CreateBitTree(BitTree &T){
	char ch;
	cin >> ch;
	if (ch == '#')  T = NULL;
	else{
		if (!(T = new TreeNode))  return 0;
		T->data = ch;
		CreateBitTree(T->lchild);
		CreateBitTree(T->rchild);
		return 1;
	}
}

/*����α���һ�ö�����*/
void LevelTraverse(BitTree T){
	
}

/*ǰ������ݹ��㷨*/
void PreOrderTraverse1(BitTree T){
	if(T){
		visit(T->data);
		PreOrderTraverse1(T->lchild);
		PreOrderTraverse1(T->rchild);
	}
}

/*ǰ������ǵݹ��㷨*/
void PreOrderTraverse2(BitTree T){
	if(!T) exit(1);
	BitTree s[1000] = {NULL};
	int index = 0;
	s[index++] = T;
	while(index){
		T=s[--index];
		visit(T->data);
		if(T->rchild)  s[index++] = T->rchild;
		if(T->lchild)  s[index++] = T->lchild;
	}
}

/*��������ݹ��㷨*/
void InOrderTraverse1(BitTree T){
	if (T){
		InOrderTraverse1(T->lchild);
		visit(T->data);
		InOrderTraverse1(T->rchild);
	}
}

/*��������ǵݹ��㷨*/
void InOrderTraverse2(BitTree T){
	if(!T)  exit(1);
	BitTree s[1000]={NULL};
	int index=0;
	s[index++]=T;
	while(index){
		T=s[index-1];
		while(T){
			s[index++]=T->lchild;
			T=s[index-1];
		}
		index--;
		if(index){
			T=s[--index];
			visit(T->data);
			s[index++]=T->rchild;
		}
	} 
}

/*��������ǵݹ��㷨*/
void InOrderTraverse3(BitTree T){
	if(!T)  exit(1);
	BitTree s[1000]={NULL};
	int index=0;
	while(T||index){
		if(T){
			s[index++]=T;
			T=T->lchild;
		}else{
			T=s[--index];
			visit(T->data);
			T=T->rchild;
		}
	} 
}

/*��������ݹ��㷨*/
void PostOrderTraverse1(BitTree T){
	if (T){
		PostOrderTraverse1(T->lchild);
		PostOrderTraverse1(T->rchild);
		visit(T->data);
	}
}

/*��������ǵݹ��㷨*/
void PostOrderTraverse2(BitTree T){
	if(!T)  exit(1);
	typedef struct{
		BitTree T;
		char tag;
	}group;
	group a[1000]={NULL,'\0'};
	int index=0;
	char tag;
	while(T||index){
		while(T){
			group temp={T,'L'};
			a[index++]=temp;
			T=T->lchild;
		}
		tag='R';
		while(index&&tag=='R'){
			group temp=a[--index];
			tag=temp.tag;
			T=temp.T;
			if(tag=='L'){
				temp.tag='R';
				a[index++]=temp;
				T=T->rchild;
			}else{
				visit(T->data);
				T=NULL;
			}
		}
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
	for(int i=1;i<level;i++)  cout<<"  ";
	cout<<T->data<<endl;
	DisplayBitTree(T->lchild,level+1);
} 

/*
*�õ�һ�ö�����������(ֱ��),�Լ�һ�����ȵ������ߵ�·��
*/ 
void  GetHigh(BitTree t,char p[],char* path,int& high,int n=1){//n�ĳ�ֵΪ1, high�ĳ�ֵΪ0
	if(t){
		p[n]=t->data;
		if(n>high){
			high=n;
			for(int i=1;i<=n;i++)  path[i]=p[i];
		}
		GetHigh(t->lchild,p,path,high,n+1);
		GetHigh(t->rchild,p,path,high,n+1);
	}
}

/*
*�õ�����һ������·��
*/ 
void GetPath(BitTree t,int n,int &high,char e,char p[],char* path){
	if(t){
		p[n]=t->data;
		if(t->data==e){
			high=n;
			for(int i=1;i<=n;i++)  path[i]=p[i];
		}
		GetPath(t->lchild,n+1,high,e,p,path);
		GetPath(t->rchild,n+1,high,e,p,path);
	}
} 

/*
*�õ��������Ĺ�ͬ����
*/ 
char GetCommonAncestor(BitTree t,char c1,char c2){
	int h1=0,h2=0;
	char path1[100],path2[100],p[100],pre;
	GetPath(t,1,h1,c1,p,path1);
	GetPath(t,1,h2,c2,p,path2);
	for(int i=1;i<=h1&&i<=h2;i++)
	  if(path1[i]==path2[i])
	    pre=path1[i];
	return pre;
}

/*
*�ж����ö������Ƿ����� 
*/ 
int Similar(BitTree t1,BitTree t2){
	if (!t1 && !t2)  return 1;
	if ((!t1 && t2)||(t1 && !t2))  return 0;
	return Similar(t1->lchild,t2->lchild) && Similar(t1->rchild,t2->rchild);
} 

/*
*�ж����ö������Ƿ���� 
*/
int Equal(BitTree t1,BitTree t2){
	if (!t1 && !t2)  return 1;
	if ((!t1 && t2)||(t1 && !t2))  return 0;
	return (t1->data == t2->data) && Equal(t1->lchild,t2->lchild) && Equal(t1->rchild,t2->rchild);
} 

/*
*���������������н������Һ��� 
*/
void ChangeChild(BitTree& t){
	if(!t)  return;
	BitTree temp = t->lchild;
	t->lchild = t->rchild;
	t->rchild = temp;
	ChangeChild(t->lchild);
	ChangeChild(t->rchild);
} 


#endif

#ifndef THREADED_BINARY_TREE
#define THREADED_BINARY_TREE

typedef enum Tag{
	Link,Thread
}Tag;

typedef struct ThreadedTreeNode{
	ElemType data;
	struct ThreadedTreeNode * lchild,* rchild;
	Tag LTag,RTag;
}ThreadedTreeNode,* ThreadedBitTree;

void InOrderTraverse1(ThreadedBitTree T);
ThreadedBitTree CopyToThreaded(BitTree t);
void InOrderThreading(ThreadedBitTree &t);
void InOrderTraverseThreaded(ThreadedBitTree t,void *visit(char c));
void InOrderThreading(ThreadedBitTree &t);
void InThreading(ThreadedBitTree t,ThreadedBitTree &pre);

/*��������ݹ��㷨*/
void InOrderTraverse1(ThreadedBitTree T){
	if (T){
		InOrderTraverse1(T->lchild);
		visit(T->data);
		InOrderTraverse1(T->rchild);
	}
}

/*��һ����ͨ������ת��Ϊһ������������*/
ThreadedBitTree CopyToThreaded(BitTree t){
	ThreadedBitTree root=NULL;
	if(t){
		root=new ThreadedTreeNode;
		root->data=t->data;
		root->LTag=root->RTag=Link;
		root->lchild=CopyToThreaded(t->lchild);
		root->rchild=CopyToThreaded(t->rchild);
	}
	return root;
} 

/*˳��̱�������������*/
void InOrderTraverseThreaded(ThreadedBitTree t,void (*visit)(char c)){
	ThreadedBitTree p=t->lchild;
	while(p!=t){
		while(p->LTag==Link)  p=p->lchild;
		visit(p->data);
		while(p->RTag==Thread&&p->rchild!=t){
			p=p->rchild;
			visit(p->data);
		}
		p=p->rchild;
	}
} 

/*�����������һ��������������*/
void InOrderThreading(ThreadedBitTree &t){
	ThreadedBitTree Thrt;
	if(!(Thrt=new ThreadedTreeNode)) exit(1);
	Thrt->LTag=Link;
	Thrt->RTag=Thread;
	Thrt->rchild=Thrt;
	if(!t)  Thrt->lchild=Thrt;
	else{
		ThreadedBitTree pre=Thrt; 
		Thrt->lchild=t;
		InThreading(t,pre);
		pre->RTag=Thread;
		pre->rchild=Thrt;
		Thrt->rchild=pre;
	} 
}

void InThreading(ThreadedBitTree t,ThreadedBitTree &pre){
	if(t){
		InThreading(t->lchild,pre);
		if(!t->lchild){
			t->LTag=Thread;
			t->lchild=pre;
		}
		if(!pre->rchild){
			pre->RTag=Thread;
			pre->rchild=t;
		}
		pre=t;
		InThreading(t->rchild,pre);
	}
}

#endif


int main(){
	BitTree t1,t2,t3;
	char* s1="A(B(C,D),E(#,F))";
	char* s2="A(B(C,D),E(#,H))";
	t1=CreateBitTree(s1);
	t2=CreateBitTree(s1);
	t3=CreateBitTree(s2);
	cout << "===============" << endl;
	DisplayBitTree(t1);
	cout << "===============" << endl;
	DisplayBitTree(t2);
	cout << "===============" << endl;
	DisplayBitTree(t3); 
	cout << "===============" << endl;
	ChangeChild(t3);
	cout << "===============" << endl;
	DisplayBitTree(t3); 
	cout << "===============" << endl;
	int flag1=Similar(t1,t3),flag2=Equal(t1,t3);
	cout<<flag1<<" "<<flag2;
	return 0;
}

