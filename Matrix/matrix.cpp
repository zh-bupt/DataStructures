#include<iostream>
using namespace std;

const int MAXSIZE=10000;

typedef struct{
	int data[100][100];
	int col,row;
}Matrix,*Matrix_ptr;

typedef struct{
  int i,j;//元素在原矩阵中的坐标,i为行,j为列
  int e;
}triple;

typedef struct{
  int r,c,n;//r为行数,c为列数,n为非零元个数
  triple data[MAXSIZE+1];
}TSMatrix;

/*
*by zh 2016.11.20 
*从键盘输入一个矩阵 
*/
void Input(Matrix& m){
	cout << "请输入行数和列数:";
  	cin >> m.row >> m.col;
  	cout << "请输入矩阵:" << endl;
  	for (int i = 0; i < m.row; i++)
    	for (int j = 0; j< m.col; j++)
      		cin >> m.data[i][j];
}

/*
*by zh 2016.11.20
*将一个稀疏矩阵压缩
*/
TSMatrix Transfer(Matrix m){
  	TSMatrix t;
  	t.r = m.row; t.c = m.col; t.n = 0;
  	for (int p = 0; p < m.row; p++)
      for (int q = 0; q < m.col; q++)
        if (m.data[p][q]){
       		t.data[++t.n].e = m.data[p][q];
       		t.data[t.n].i = p;
       		t.data[t.n].j = q;
	   	}
  return t;
}

/*
*by zh 2016.11.20
*经典压缩矩阵转置
*/
TSMatrix TransposeSMatrix(TSMatrix m){
  	TSMatrix t;
  	t.n = m.n;t.r = m.c;t.c = m.r;
  	if (m.n) {
   		int q = 1;
    	for (int col = 1; col <= m.c; col++)
      	  for (int p = 1; p <= m.n; p++)
        	if (col == m.data[p].j) {
          		t.data[q].i = m.data[p].j;
          		t.data[q].j = m.data[p].i;
          		t.data[q].e = m.data[p].e;
          		q++;
        	}
  	}
  	return t;
}

/*
*by zh 2016.11.20
*快速压缩矩阵转置，利用两个向量，num表示每一列中非零
*元的个数cpot表示每一列第一个元素在新矩阵中的位置
*/
TSMatrix FastTransposeSMatrix(TSMatrix m){
  	TSMatrix t;
  	t.n = m.n; t.r = m.c; t.c = m.r;
  	if (m.n) {
    	int num[m.n], cpot[m.c];										//两个向量数组,num表示每一列中非零元的个数,cpot存储每一列的第一个元素在转置之后的矩阵中的位置 
    	for (int p = 1; p <= m.n; p++)  num[p] = 0;						//初始化num数组
    	cpot[1] = 1;
    	for (int p = 1; p <= m.n; p++)  num[m.data[p].j]++;				//求每一列中非零元的个数
    	for (int p = 2; p <= m.r; p++)  cpot[p] = cpot[p-1] + num[p-1];	//求每一列第一个元素在新矩阵中的位置
    	for (int p = 1; p <= m.n; p++) {								//转置 
      		int col = m.data[p].j;
      		int q = cpot[col];
      		t.data[q].j = m.data[p].i;
      		t.data[q].i = m.data[p].j;
    		t.data[q].e = m.data[p].e;
      		cpot[col]++; 
    	}
  	}
  return t;
}

/*
*by zh 2016.11.10
*从压缩矩阵转回一般矩阵 
*/ 
Matrix TransBack(TSMatrix tm){
  	Matrix m;
  	m.col=tm.c;
  	m.row=tm.r;
  	for (int i = 0 ; i < m.col; i++)
    	for (int j = 0 ;j < m.col; j++)
      		m.data[i][j]=0;
  	for (int p = 1; p <= tm.n; p++)
    	m.data[tm.data[p].i][tm.data[p].j] = tm.data[p].e;
  	return m;
}

/*
*by zh 2016.11.20
*将一个普通矩阵输出 
*/ 
void PrintMatrix(Matrix m){
	for (int p = 0; p < m.row; p++){
  	 	for (int q =0; q < m.col; q++)
      		cout << m.data[p][q] << ' ';
      	cout << endl;
  	}
  	cout << endl;
}

int main(int argc, char const *argv[]) {
  	Matrix m; 
  	TSMatrix tm;
  	Input(m);
  	PrintMatrix(m);
  	tm=Transfer(m);
  	tm=FastTransposeSMatrix(tm);
  	m=TransBack(tm);
  	PrintMatrix(m);
  	return 0;
}
