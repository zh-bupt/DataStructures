/*
��������:
*/
#include<iostream>
using namespace std;
int const MAX_NUM=1000;

int findPrimaryNum(int *a,int length){
	int pNum=a[0],flag=0,total=0;
	for(int i=0;i<length;i++){
		if(flag==0){
			pNum=a[i];
			flag++;
		}else{
			if(a[i]==pNum)  flag++;
			else  flag--;
		}
	}
	
	for(int i=0;i<length;i++)
	  if(a[i]==pNum)  total++;
	
	if(total>length/2)  return pNum;
	else  return -1;
}

int main(){
	int a[MAX_NUM],length,primary_num;
	cout<<"���������鳤��:";
	cin>>length;
	cout<<"����������:";
	for(int i=0;i<length;i++)
	  cin>>a[i];
	primary_num=findPrimaryNum(a,length);
	if(primary_num==-1)  cout<<"������û������!!"<<endl;
	else  cout<<"�����������Ϊ:"<<primary_num<<endl;
	system("pause");
	return 0;
} 
