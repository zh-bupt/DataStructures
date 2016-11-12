#include<iostream>
using namespace std;

const int MAXSIZE=12500;

typedef struct{
  int i,j;//Ԫ����ԭ�����е�����,iΪ��,jΪ��
  int e;
}triple;

typedef struct{
  int r,c,n;//rΪ����,cΪ����,nΪ����Ԫ����
  triple data[MAXSIZE+1];
}TSMatrix;

/*��һ��ϡ�����ѹ��*/
TSMatrix Transfer(int m[][100],int row,int col){
  TSMatrix t;
  t.r = row; t.c = col; t.n = 0;
  for (int p = 0; p < row; p++)
     for (int q = 0; q < col; q++)
       if (m[p][q]){
       	t.data[++t.n].e = m[p][q];
       	t.data[t.n].i = p;
       	t.data[t.n].j = q;
	   }
  return t;
}

/*����ѹ������ת��*/
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
        }//if
  }//if
  return t;
}//TransposeSMatrix

/*����ѹ������ת�ã���������������num��ʾÿһ���з���
Ԫ�ĸ���cpot��ʾÿһ�е�һ��Ԫ�����¾����е�λ��*/
TSMatrix FastTransposeSMatrix(TSMatrix m){
  TSMatrix t;
  t.n = m.n; t.r = m.c; t.c = m.r;
  if (m.n) {
    int num[m.n], cpot[m.c];
    for (int p = 1; p <= m.n; p++)  num[p] = 0;//��ʼ��num����
    cpot[1] = 1;
    for (int p = 1; p <= m.n; p++)  num[m.data[p].j]++;//��ÿһ���з���Ԫ�ĸ���
    for (int p = 2; p <= m.r; p++)  cpot[p] = cpot[p-1] + num[p-1];//��ÿһ�е�һ��Ԫ�����¾����е�λ��
    for (int p = 1; p < m.n; p++) {
      int col = m.data[p].j;
      int q = cpot[col];
      t.data[q].j = m.data[p].i;
      t.data[q].i = m.data[p].j;
      t.data[q].e = m.data[p].e;
      cpot[col]++;
    }//for
  }//if
  return t;
}//FastTransposeSMatrix

//int[][100] TransBack(TSMatrix m){
//  int a[100][100] = {0};
//  for (int p = 1; p <= m.n; p++)
//    a[m.data[p].i][m.data[p].j] = m.data[p].e;
//  return a;
//}//TransBack

void PrintMatrix(int m[][100],int r,int c){
  for (int p = 1; p <= r; p++)
    for (int q =1; q <= c; q++)
      cout << m[p][q] << ' ';
  cout << endl;
}//PrintTSMatrix

int main(int argc, char const *argv[]) {
  int matrix[100][100], row, col;
  TSMatrix ts_matrix; 
  cout << "����������������:";
  cin >> row >> col;
  for (int i = 0; i < row; i++)
    for (int j = 0; j< col; j++)
      cin >> matrix[i][j];
  ts_matrix = Transfer(matrix,row,col);
  return 0;
}//main
