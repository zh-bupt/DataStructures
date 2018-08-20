/*
*问题描述： 
*输入一组关键字序列，并以此顺序建立一棵平衡二叉树，
*并在建树过程中用逆中序法输出每次插入新结点后的平衡二叉树形状。
*分工：
*编码 2015211203 张珩
*文档 2015211109 孙嘉文
*测试 2015522118 董笑言  
*/ 
#include<iostream>
using namespace std;

/*
*枚举类型，用来表示一个节点左右子树的关系  
*LH：表示左子树高
*RH：表示右子树高
*EH：表示左右子树等高 
*/ 
typedef enum {
	LH = -1, EH, RH
}BalanceFactor;

/*
*数据元素结构 
*/ 
typedef struct ElemType {
	int key;//数据元素的关键字 
	char data;//数据元素的其他数据项，以一个字符代替 
}ElemType;


/*
*平衡二叉树结构 
*/ 
typedef struct BSTNode {
	ElemType data;
	BalanceFactor bf;//结点的平衡因子
	struct BSTNode * lchild, *rchild;//左右孩子指针 
}BSTNode, *BSTree;

void R_Rotate(BSTree &t);//右旋函数原型 
void L_Rotate(BSTree &t);//左旋函数原型 
int InsertAVL(BSTree &T, ElemType e, bool &taller);//插入一个元素到平衡二叉树 
void RightBalance(BSTree &T);//右平衡函数原型 
void LeftBalance(BSTree &T);//左平衡函数原型 
BSTree Create(ElemType array[]);//构建平衡二叉树的函数原型 
void DisplayBSTree(BSTree T, int level);//以凹入表的形式输出平衡二叉树 

/*
*右旋函数
*对以t为根节点的二叉排序树作右旋处理，处理之后t指向新的
*数根结点，即处理之前的左子树的根节点 
*/ 
void R_Rotate(BSTree &t) {
	BSTree lc = t->lchild; 
	t->lchild = lc->rchild;
	lc->rchild = t;
	t = lc;
}


/*
*左旋函数
*对以t为根节点的二叉排序树作左旋处理，处理之后t指向新的
*数根结点，即处理之前的右子树的根节点 
*/ 
void L_Rotate(BSTree &t) {
	BSTree rc = t->rchild;
	t->rchild = rc->lchild;
	rc->lchild = t;
	t = rc;
}


/*
*插入一个元素到平衡二叉树 
*若在平衡的二叉排序树T中不存在和待插入元素e有相同关键字的结点，
*则插入一个数据元素为e的新节点，并返回1，否则返回0。若因插入而使
*二叉排序树失去平衡，则作平衡旋转处理，布尔量taller反映T长高与否 
*/ 
int InsertAVL(BSTree &T, ElemType e, bool &taller) {
	if (!T) {						//若原树为空，则插入新节点，树长高，置taller为true 
		T = new BSTNode;
		T->data = e;
		T->lchild = T->rchild = NULL;
		T->bf = EH;
		taller = true;
	}
	else {
		if (e.key == T->data.key) {	//树中已存在和e有相同关键字的结点 
			taller = false;			//则不再插入 
			return 0;				//并返回0 
		}
		if (e.key < T->data.key) {	//继续在T的左子树中进行搜索 
			if (!InsertAVL(T->lchild, e, taller))  return 0;//未插入 
			if (taller)				//已插入到T的左子树中且使树长高 
				switch (T->bf) {	//检查T的平衡因子 
				case LH:			//原本左子树就比右子树高，插入后需作左平衡处理 
					LeftBalance(T);
					taller = false;
					break;
				case EH:			//原本左右子树等高，现因左子树增高而使树长高 
					T->bf = LH;
					taller = true;
					break;
				case RH:			//原本右子树比左子树高，插入后左右子树等高 
					T->bf = EH;
					taller = false;
					break;
				}//switch (T->bf)
		}
		else {						//继续在T的左子树中进行搜索 
			if (!InsertAVL(T->rchild, e, taller))  return 0;//未插入 
			if (taller)				//已插入到T的左子树中且使树长高 
				switch (T->bf) {	
				case LH:			//原本左子树比右子树高，插入后左右子树等高
					T->bf = EH;
					taller = false;
					break;
				case EH:			//原本左右子树等高，现因右子树增高而使树长高 
					T->bf = RH;
					taller = true;
					break;
				case RH:			//原本右子树就比左子树高，插入后需作右平衡处理 
					RightBalance(T);
					taller = false;
					break;
				}//switch (T->bf)
		}
	}
	return 1;
}


/*
*对以指针T所指结点为根的二叉树作右平衡旋转处理，
*本函数执行后，指针T指向新的根节点 
*/ 
void RightBalance(BSTree &T) {
	BSTree rc = T->rchild;
	switch (rc->bf) {
	case RH:
		T->bf = rc->bf = EH;
		L_Rotate(T);
		break;
	case LH:
		BSTree ld = rc->lchild;//rd指向T的右孩子的左子树的根
		switch (ld->bf) {
		case LH:
			T->bf = EH;
			rc->bf = RH;
			break;
		case EH:
			T->bf = rc->bf = EH;
			break;
		case RH:
			T->bf = LH;
			rc->bf = EH;
			break;
		} //switch (rd->bf)
		ld->bf = EH;
		R_Rotate(T->rchild);
		L_Rotate(T);
	} //switch(lc->bf)
}


/*
*对以指针T所指结点为根的二叉树作左平衡旋转处理，
*本函数执行后，指针T指向新的根节点 
*/ 
void LeftBalance(BSTree &T) {
	BSTree lc = T->lchild;
	switch (lc->bf) {
	case LH:
		T->bf = lc->bf = EH;
		R_Rotate(T);
		break;
	case RH:
		BSTree rd = lc->rchild;//rd指向T的左孩子的右子树的根
		switch (rd->bf) {
		case LH:
			T->bf = RH;
			lc->bf = EH;
			break;
		case EH:
			T->bf = lc->bf = EH;
			break;
		case RH:
			T->bf = EH;
			lc->bf = LH;
			break;
		} //switch (rd->bf)
		rd->bf = EH;
		L_Rotate(T->lchild);
		R_Rotate(T);
	} //switch(lc->bf)
}

/*
*创建一个平衡二叉树
*传入参数为一个所存贮数据类型的数组以及存入数据的数目 
*/ 
BSTree Create(ElemType array[], int length) {
	BSTree t = NULL;
	bool taller;
	for (int i = 0; i<length; i++) {
		InsertAVL(t, array[i], taller);
		DisplayBSTree(t, 1);
		cout << "===========================================" << endl;
	}
	return t;
}

/*
*以凹入表的形式打印一棵二叉树,
*凹入表的形式其实是带层次的逆中序遍历,
*初始值level为1
*/
void DisplayBSTree(BSTree T, int level = 1) {
	if (!T)  return;
	DisplayBSTree(T->rchild, level + 1);
	for (int i = 1; i<level; i++)  cout << "\t";
//	cout <<  '(' <<T->data.key << ',' << T->data.data <<  ')' << endl << endl;
	cout << T->data.key << endl;
	DisplayBSTree(T->lchild, level + 1);
}

int main() {
	ElemType array[] = { { 13,'a' },{ 24,'b' },{ 37,'c' },{ 13,'a' },{ 24,'b' },{ 37,'c' },{ 90,'d' },{ 53,'e' } };
//	ElemType array[] = { {1,'a'},{2,'b'},{3,'c'},{4,'d'},{5,'f'},{6,'g'},{7,'h'},{8,'i'},{9,'j'},{10,'l'},
//						{11,'m'},{12,'n'},{13,'o'},{14,'p'},{15,'q'},{16,'r'},{17,'s'},{18,'t'},{19,'u'},
//						{20,'v'},{21,'w'},{22,'x'},{23,'y'},{24,'z'},{25,'@'},{26,'#'},{27,'$'},{28,'%'},
//						{29,'^'},{30,'&'},{31,'*'}}; 
	Create(array, 8);
	return 0;
}
