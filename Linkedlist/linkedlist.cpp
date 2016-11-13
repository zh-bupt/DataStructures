#include<iostream>
#include<stdlib.h>

using namespace std;

typedef struct node{
	int data;
	struct node* next;
}lnode,* linkedlist;

void Initialize(linkedlist &list){
	list=NULL;
}

/*正向建立一个不带头节点的单向链表*/
linkedlist Create1(int n){
	linkedlist head=NULL,last,current;
	for(;n>0;n--){
		current=new lnode;
		if(!head)  head=current;
		else  last->next=current;
		last=current;
		cin>>(current->data);
	}
	last->next=NULL;
	return head;
} 

/*逆向建立一个不带头节点的单向链表*/
linkedlist Create2(int n){
	linkedlist head=NULL,p;
	for(;n>0;n--){
		p=new lnode;
		cin>>p->data;
		p->next=head;
		head=p;
	}
	return head;
} 

/*不带头节点的单链表逆置*/ 
void Reverse(linkedlist &list){
	linkedlist current=list,last=NULL,next;
	while(current){
		next=current->next;
		current->next=last;
		last=current;
		current=next;
	}
	list=last;
}

/*将数据域为整型的一个单链表拆分为只含奇数和只含偶数的两个链表*/ 
void Separate1(linkedlist list,linkedlist &odd,linkedlist &even){
	linkedlist temp;
	odd=even=NULL;
	while(list){
		temp=list->next;
		if((list->data)%2){
			list->next=odd;
			odd=list;
		}else{
			list->next=even;
			even=list;
		}
		list=temp;
	}
}

/*将数据域为整型的一个单链表拆分为只含奇数和只含偶数的两个链表*/ 
void Separate2(linkedlist list,linkedlist &odd,linkedlist &even){
	linkedlist temp,current1=new lnode,current2=new lnode;
	current1->next=current2->next=NULL;
	odd=current1;
	even=current2;
	while(list){
		temp=list->next;
		if(list->data%2){
			current1->next=list;
			list->next=NULL;
			current1=list;
		}else{
			current2->next=list;
			list->next=NULL;
			current2=list;
		}
		list=temp;
	}
	temp=odd;
	odd=odd->next;
	delete temp;
	temp=even;
	even=even->next;
	delete temp;
}

/*复制一个不带头节点的单链表*/
linkedlist Copy(linkedlist list){
	linkedlist head=NULL,p,last;
	while(list){
		p=new lnode;
		p->data=list->data;
		if(!head)  head=p;
		else last->next=p;
		last=p;
		list=list->next;
	}
	return head; 
}

void Print(linkedlist list){
	while(list!=NULL){
		int data=list->data;
		cout<<data<<' ';
		list=list->next;
	}
	cout<<endl;
}

int main(){
	linkedlist list,list2,odd=NULL,even=NULL;
	Initialize(list);
	list=Create2(10);
	list2=Copy(list);
//	Separate2(list,odd,even);
//	Reverse(list);
	Print(list);
	Print(list2);
//	Print(odd);
//	Print(even);
	return 0;
}
