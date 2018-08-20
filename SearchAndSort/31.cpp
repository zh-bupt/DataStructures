#include<iostream>
using namespace std;

const int MAX_LENGTH = 100;

void GetC(int C[],int A[],int length){
	for(int i = 1; i <= length; i++)
	  for(int j = 1; j <= length; j++)
	    if(A[i] > A[j])  C[i]++;
} 

void Sort(int A[],int length){
	int C[MAX_LENGTH]={0},B[MAX_LENGTH];
	GetC(C,A,length);
	for ( int i = 1; i <= length; i++){
		B[i] = A[i];
		A[i] = -1;
	}
	for (int i = 1; i <= length; i++){
		int j = C[i]+1;
		for (; A[j] != -1; j++);
	    A[j] = B[i];
	}
}

int main(){
	int A[MAX_LENGTH],length;
	cin >> length;
	for (int i = 1; i <= length; i++)  cin >> A[i];
	Sort(A,length);
	for (int i = 1; i <= length; i++)  cout << A[i] << ' ';
}
