#include<iostream>
#include<stdlib.h>

using namespace std;

typedef struct node{
	int data;
	struct node* next;
}lnode,* linkedlist;

/*正向建立一个带头节点的单向链表*/
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

/*逆向建立一个带头节点的单向链表*/
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

/*带头节点的单链表逆置*/
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

/*输出一个带头节点的单链表*/ 
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
	cout<<"请输入你要输入的数据个数:";
	cin>>n;
	list=Create_r(n);
	Reverse(list);
	Print(list);
	return 0;
}
