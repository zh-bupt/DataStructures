/*
中位数
问题描述:对于一个升序排列的数组,下标为[length/2]的数为其中位数,
现有两个等长的升序排列的数组,试求这两个数组合并后的新数组的中位数,
且时间复杂度和空间复杂度尽可能的低 
*/ 

#include<iostream>
using namespace std;

int const MAX_NUM=1000;

int findMiddleNum(int* a1,int* a2,int s1,int e1,int s2,int e2){
	int m1=(s1+e1)/2,m2=(s2+e2)/2;
	if(a1[m1]>a2[m2]){
		e1=m1;
		s2=m2;
	}else if(a1[m1]<a2[m2]){
		s1=m1;
		e2=m2;
	}else
	  return a1[m1];
	findMiddleNum(a1,a2,s1,e1,s2,e2);
}

int main(){
	int length,a1[MAX_NUM],a2[MAX_NUM];
	cout<<"请输入数组长度:";
	cin>>length;
	cout<<"请输入数组1:";
	for(int i=0;i<length;i++)  cin>>a1[i];
	cout<<"请输入数组2:";
	for(int i=0;i<length;i++)  cin>>a2[i];
	cout<<"两个数组的中位数为:"<<findMiddleNum(a1,a2,0,length,0,length)<<endl;
	system("pause");
	return 0;
}
