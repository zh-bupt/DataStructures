/*
ʱ��:2016-10-28
��������:���һ���㷨,������A�е�Ԫ��ѭ������kλ,
		Ҫ��ֻ��һ��Ԫ�صĸ��ӿռ�,Ԫ���ƶ��򽻻�����ΪO(n)
*/
#include<iostream>
using namespace std;
/*
������array���±�Ϊstart���±�Ϊend֮��Ĳ��ֵߵ�
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
	Switch(0,len-1,array);//�Ƚ���������ߵ�
	Switch(0,step-1,array);//�ٽ������鿪ʼ��step��Ԫ�صߵ�
	Switch(step,len-1,array);//���step��Ԫ�ص������ߵ�
}

int main(){
	int array[1000]={0},len,step;
	cout<<"���������鳤��:";
	cin>>len;
	cout<<"����������:";
	for (int i = 0; i < len; i++){
		cin>>array[i];
	}
	cout<<"�������ƶ���λ��:";
	cin>>step;
	Move(array,step,len);
	cout<<"�ƶ�֮��Ľ��Ϊ:";
	for (int i = 0; i < len; ++i){
		cout<<array[i]<<' ';
	}
	cout<<endl;
	system("pause");
	return 0;
}
