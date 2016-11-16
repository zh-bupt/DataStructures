#include<iostream>
#include<stdlib.h>

using namespace std;

typedef struct node{
	int data;
	struct node* next;
}lnode,* linkedlist;

/*������һ����ͷ�ڵ�ĵ�������*/
linkedlist Create(int n){
	linkedlist head=new lnode,p,current;
	head->data=n;
	p=head;
	for(int i=0;i<n;i++){
		current=new lnode;
		if(!current)  exit(1);
		cin>>current->data;
		p->next=current;
		p=current;
	}
	p->next=NULL;
	return head;
}

/*������һ����ͷ�ڵ�ĵ�������*/
linkedlist Create_r(int n){
	linkedlist head=new lnode,p=NULL,current;
	if(!head)  exit(1);
	head->data=n;
	for(int i=0;i<n;i++){
		current=new lnode;
		if(!current)  exit(1);
		cin>>current->data;
		current->next=p;
		p=current;
		head->next=current;
	}
	return head;
}

/*��ͷ�ڵ�ĵ���������*/
void Reverse(linkedlist &list){
	linkedlist current=list->next,last=NULL,next;
	while(current){
		next=current->next;
		current->next=last;
		last=current;
		current=next;
	}
	list->next=last;
}

/*���һ����ͷ�ڵ�ĵ�����*/ 
void Print(linkedlist list){
	list=list->next;
	while(list){
		cout<<list->data<<" ";
		list=list->next;
	}
	cout<<endl;
}

int main(){
	linkedlist list;
	int n;
	cout<<"��������Ҫ��������ݸ���:";
	cin>>n;
	list=Create_r(n);
	Reverse(list);
	Print(list);
	return 0;
}
