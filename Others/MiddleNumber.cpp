/*
��λ��
��������:����һ���������е�����,�±�Ϊ[length/2]����Ϊ����λ��,
���������ȳ����������е�����,��������������ϲ�������������λ��,
��ʱ�临�ӶȺͿռ临�ӶȾ����ܵĵ� 
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
	cout<<"���������鳤��:";
	cin>>length;
	cout<<"����������1:";
	for(int i=0;i<length;i++)  cin>>a1[i];
	cout<<"����������2:";
	for(int i=0;i<length;i++)  cin>>a2[i];
	cout<<"�����������λ��Ϊ:"<<findMiddleNum(a1,a2,0,length,0,length)<<endl;
	system("pause");
	return 0;
}
