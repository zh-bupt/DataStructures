/*
*by zh at 2016.11.17
*�����������һ�ĸ��� 
*/ 
#include<iostream>
using namespace std;

/*����һ���������ݵĶ����Ʊ�ʾ��1�ĸ��� */
int Count(int num){
	int count=0;
	while(num){
		num&=num-1;
		count++;
	}
	return count;
} 

/*�������:��������������,��A�Ķ�����
��ʽ�ı�ΪB�Ķ�������ʽ��Ҫ�ı����λ*/ 
int Diff(int a,int b){
	return Count(a^b);
} 

int main(){
	int num;
	cout<<"����������:";
	cin>>num;
	cout<<"����"<<num<<"�Ķ����Ʊ�ʾ��1�ĸ���Ϊ:"<<Count(num)<<endl;
	system("pause");
	return 0; 
}
