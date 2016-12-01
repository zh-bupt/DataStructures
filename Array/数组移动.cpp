/*
时间:2016-10-28
问题描述:设计一个算法,将数组A中的元素循环右移k位,
		要求只用一个元素的附加空间,元素移动或交换次数为O(n)
*/
#include<iostream>
using namespace std;
/*
将数组array从下标为start到下标为end之间的部分颠倒
*/
void Switch(int start,int end,int *array){
	int temp;
	for(;start<end;start++,end--){
		temp=array[start];
		array[start]=array[end];
		array[end]=temp;
	}
}

void Move(int *array,int step,int len){
	step=step%len;
	Switch(0,len-1,array);//先将整个数组颠倒
	Switch(0,step-1,array);//再将从数组开始到step个元素颠倒
	Switch(step,len-1,array);//最后将step个元素到结束颠倒
}

int main(){
	int array[1000]={0},len,step;
	cout<<"请输入数组长度:";
	cin>>len;
	cout<<"请输入数组:";
	for (int i = 0; i < len; i++){
		cin>>array[i];
	}
	cout<<"请输入移动的位数:";
	cin>>step;
	Move(array,step,len);
	cout<<"移动之后的结果为:";
	for (int i = 0; i < len; ++i){
		cout<<array[i]<<' ';
	}
	cout<<endl;
	system("pause");
	return 0;
}
