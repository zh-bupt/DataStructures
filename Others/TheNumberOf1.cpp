/*
*by zh at 2016.11.17
*求二进制数中一的个数 
*/ 
#include<iostream>
using namespace std;

/*计算一个整型数据的二进制表示中1的个数 */
int Count(int num){
	int count=0;
	while(num){
		num&=num-1;
		count++;
	}
	return count;
} 

/*相关问题:给定两个正整数,把A的二进制
形式改变为B的二进制形式需要改变多少位*/ 
int Diff(int a,int b){
	return Count(a^b);
} 

int main(){
	int num;
	cout<<"请输入整数:";
	cin>>num;
	cout<<"整数"<<num<<"的二进制表示中1的个数为:"<<Count(num)<<endl;
	system("pause");
	return 0; 
}
