#include<iostream>
using namespace std;

const int MAXSIZE=10000;

typedef struct{
	int data[100][100];
	int col,row;
}Matrix,*Matrix_ptr;

typedef struct{
  int i,j;//Ԫ����ԭ�����е�����,iΪ��,jΪ��
  int e;
}triple;

typedef struct{
  int r,c,n;//rΪ����,cΪ����,nΪ����Ԫ����
  triple data[MAXSIZE+1];
}TSMatrix;

/*
*by zh 2016.11.20 
*�Ӽ�������һ������ 
*/
void Input(Matrix& m){
	cout << "����������������:";
  	cin >> m.row >> m.col;
  	cout << "���������:" << endl;
  	for (int i = 0; i < m.row; i++)
    	for (int j = 0; j< m.col; j++)
      		cin >> m.data[i][j];
}

/*
*by zh 2016.11.20
*��һ��ϡ�����ѹ��
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
*����ѹ������ת��
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
*����ѹ������ת�ã���������������num��ʾÿһ���з���
*Ԫ�ĸ���cpot��ʾÿһ�е�һ��Ԫ�����¾����е�λ��
*/
TSMatrix FastTransposeSMatrix(TSMatrix m){
  	TSMatrix t;
  	t.n = m.n; t.r = m.c; t.c = m.r;
  	if (m.n) {
    	int num[m.n], cpot[m.c];										//������������,num��ʾÿһ���з���Ԫ�ĸ���,cpot�洢ÿһ�еĵ�һ��Ԫ����ת��֮��ľ����е�λ�� 
    	for (int p = 1; p <= m.n; p++)  num[p] = 0;						//��ʼ��num����
    	cpot[1] = 1;
    	for (int p = 1; p <= m.n; p++)  num[m.data[p].j]++;				//��ÿһ���з���Ԫ�ĸ���
    	for (int p = 2; p <= m.r; p++)  cpot[p] = cpot[p-1] + num[p-1];	//��ÿһ�е�һ��Ԫ�����¾����е�λ��
    	for (int p = 1; p <= m.n; p++) {								//ת�� 
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
*��ѹ������ת��һ����� 
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
*��һ����ͨ������� 
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
