#include<iostream>
#include<stdlib.h>

using namespace std;

typedef struct node{
	int data;
	struct node* next;
}lnode,* linkedlist;

/*正向建立一个不带头节点的单向链表*/
linkedlist Create(int n){
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
linkedlist Create_r(int n){
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

//将两个不带头节点的有序单链表合并
linkedlist MergeList(linkedlist &a,linkedlist &b){
	linkedlist current=new lnode,head=current,temp;
	while(a&&b){
		if(a->data<b->data) {
			current->next=a;
			current=a;
			a=a->next;
		}else{
			current->next=b;
			current=b;
			b=b->next;
		}
	}
	current->next=a?a:b;
	temp=head->next;
	delete head;
	return temp;
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

/*输出单链表*/
void Print(linkedlist list){
	while(list!=NULL){
		int data=list->data;
		cout<<data<<' ';
		list=list->next;
	}
	cout<<endl;
}

int main(){
	linkedlist list1,list2;
	int n;
	cout<<"请输入你要输入的链表1数据个数:";
	cin>>n;
	list1=Create(n);
	cout<<"请输入你要输入的链表1数据个数:";
	cin>>n;
	list2=Create(n);
	list1=MergeList(list1,list2);
	Print(list1);
	return 0;
}
