/*
*writen by zh 2016.12.01 
*���������Դ�ͷ���ĵ������ʾ�����������һ������Ƶ�ȣ�
*��ʼֵΪ 0��ÿ�β��ҳɹ���ý��Ƶ��ֵ���� 1���Ը����㷨��
*��ÿ�β��Һ�������о�������Ƶ�ȴӴ�С���С�
*/ 
#include<iostream>
#include<stdlib.h>

using namespace std;

typedef struct node{
	char c;
	int times;
	struct node* next;
}lnode,* linkedlist;

/*������һ����ͷ�ڵ�ĵ�������*/
linkedlist Create(){
	linkedlist head = new lnode,p,current;
	char c;
	head->times = 0;
	p = head;
	cin >> c;
	while (c != '#'){
		current = new lnode;
		if (!current)  exit(1);
		current->times = 0;
		current->c = c;
		head->times ++;
		p->next = current;
		p = current;
		cin >> c;
	}
	p->next = NULL;
	return head;
}

/*������һ����ͷ�ڵ�ĵ�������*/
linkedlist Create(int n){
	linkedlist head = new lnode,p,current;
	head->times = n;
	p = head;
	for (int i = 0; i < n; i++){
		current = new lnode;
		if (!current)  exit(1);
		current->times = 0;
		cout << "�������" << i+1 << "��Ԫ��:";
		cin >> current->c;
		p->next = current;
		p = current;
	}
	p->next = NULL;
	return head;
}

/*���һ����ͷ�ڵ�ĵ�����*/
void Print(linkedlist list){
	list = list->next;
	while(list){
		cout << "(" << list->c << "," << list->times << ")" << " ";
		list = list->next;
	}
	cout << endl;
}

int Search(linkedlist& head,char c){
	linkedlist current = head->next,pre = head,p = head;
	int i = 1;
	while (current){
		if (current->c == c) {
			current->times ++;
			pre->next = current->next;
			current->next = p->next;
			p->next = current;
			return i;
		}
		i++;
		pre = current;
		current = current->next;
		if (current && current->times < pre->times)  p = pre;
	}
	return 0;
}

int main(int argc, char const *argv[]) {
	linkedlist head;
	int n,flag,index;
	char c;
	cout << "��������ұ�:";
	head = Create();
	cout << "���������:" << endl;
	cout << "1.��ѯ;" << endl;
	cout << "2.�����ѯ��;" << endl;
	cout << "3.�˳�." <<endl;
	cin >> flag;
	while (flag == 1 || flag == 2){
		switch (flag) {
			case 1:
				cout << "������Ҫ��ѯ��Ԫ��:";
				cin >> c;
				index = Search(head,c);
				if (index)
					cout << "Ԫ���±�Ϊ:" << index << endl;
				else
					cout << "δ��ѯ��Ԫ��" << c << "!!!" << endl;
				break;
			case 2:
				Print(head);
				break;
		}
		cout << "���������:" << endl;
		cout << "1.��ѯ;" << endl;
		cout << "2.�����ѯ��;" << endl;
		cout << "3.�˳�." << endl;
		cin >> flag;
	}
	return 0;
}
