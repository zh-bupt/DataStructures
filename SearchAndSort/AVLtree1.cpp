#include<iostream>
using namespace std;

typedef enum {
	LH = -1, EH, RH
}BalanceFactor;

typedef struct ElemType {
	int key;
	char data;
}ElemType;

typedef struct BSTNode {
	ElemType data;
	BalanceFactor bf;//结点的平衡因子
	struct BSTNode * lchild, *rchild;
}BSTNode, *BSTree;

void R_Rotate(BSTree &t);
void L_Rotate(BSTree &t);
int InsertAVL(BSTree &T, ElemType e, bool &taller);
void RightBalance(BSTree &T);
void LeftBalance(BSTree &T);
BSTree Create(ElemType array[]);
void DisplayBSTree(BSTree T, int level);


void R_Rotate(BSTree &t) {
	BSTree lc = t->lchild;
	t->lchild = lc->rchild;
	lc->rchild = t;
	t = lc;
}

void L_Rotate(BSTree &t) {
	BSTree rc = t->rchild;
	t->rchild = rc->lchild;
	rc->lchild = t;
	t = rc;
}

int InsertAVL(BSTree &T, ElemType e, bool &taller) {
	if (!T) {
		T = new BSTNode;
		T->data = e;
		T->lchild = T->rchild = NULL;
		T->bf = EH;
		taller = true;
	}
	else {
		if (e.key == T->data.key) {
			taller = false;
			return 0;
		}
		if (e.key < T->data.key) {
			if (!InsertAVL(T->lchild, e, taller))  return 0;
			if (taller)
				switch (T->bf) {
				case LH:
					LeftBalance(T);
					taller = false;
					break;
				case EH:
					T->bf = LH;
					taller = true;
					break;
				case RH:
					T->bf = EH;
					taller = false;
					break;
				}//switch (T->bf)
		}
		else {
			if (!InsertAVL(T->rchild, e, taller))  return 0;
			if (taller)
				switch (T->bf) {
				case LH:
					T->bf = EH;
					taller = false;
					break;
				case EH:
					T->bf = RH;
					taller = true;
					break;
				case RH:
					RightBalance(T);
					taller = false;
					break;
				}//switch (T->bf)
		}
	}
	return 1;
}

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
	cout <<  '(' <<T->data.key << ',' << T->data.data <<  ')' << endl << endl;
	DisplayBSTree(T->lchild, level + 1);
}

int main() {
	//ElemType array[] = { { 13,'a' },{ 24,'b' },{ 37,'c' },{ 13,'a' },{ 24,'b' },{ 37,'c' },{ 90,'d' },{ 53,'e' } };
	ElemType array[] = { {1,'a'},{2,'b'},{3,'c'},{4,'d'},{5,'f'},{6,'g'},{7,'h'},{8,'i'},{9,'j'},{10,'l'},
						{11,'m'},{12,'n'},{13,'o'},{14,'p'},{15,'q'},{16,'r'},{17,'s'},{18,'t'},{19,'u'},
						{20,'v'},{21,'w'},{22,'x'},{23,'y'},{24,'z'},{25,'@'},{26,'#'},{27,'$'},{28,'%'},
						{29,'^'},{30,'&'},{31,'*'}}; 
	Create(array, 31);
	return 0;
}
