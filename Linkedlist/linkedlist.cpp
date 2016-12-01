#include<iostream>
#include<stdlib.h>

using namespace std;

typedef struct node{
	int data;
	struct node* next;
}lnode,* linkedlist;

/*������һ������ͷ�ڵ�ĵ�������*/
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

/*������һ������ͷ�ڵ�ĵ�������*/
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

/*����ͷ�ڵ�ĵ���������*/
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

//����������ͷ�ڵ����������ϲ�
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

/*��������Ϊ���͵�һ����������Ϊֻ��������ֻ��ż������������*/
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

/*��������Ϊ���͵�һ����������Ϊֻ��������ֻ��ż������������*/
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

/*����һ������ͷ�ڵ�ĵ�����*/
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

/*���������*/
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
	cout<<"��������Ҫ���������1���ݸ���:";
	cin>>n;
	list1=Create(n);
	cout<<"��������Ҫ���������1���ݸ���:";
	cin>>n;
	list2=Create(n);
	list1=MergeList(list1,list2);
	Print(list1);
	return 0;
}
