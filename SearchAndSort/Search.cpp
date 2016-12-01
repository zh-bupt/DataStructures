/*
*writen by zh 2016.12.01 
*查找序列以带头结点的单链表表示，各结点中设一个访问频度，
*初始值为 0，每次查找成功后该结点频度值增加 1。试给出算法，
*在每次查找后查找序列均按访问频度从大到小排列。
*/ 
#include<iostream>
#include<stdlib.h>

using namespace std;

typedef struct node{
	char c;
	int times;
	struct node* next;
}lnode,* linkedlist;

/*正向建立一个带头节点的单向链表*/
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

/*正向建立一个带头节点的单向链表*/
linkedlist Create(int n){
	linkedlist head = new lnode,p,current;
	head->times = n;
	p = head;
	for (int i = 0; i < n; i++){
		current = new lnode;
		if (!current)  exit(1);
		current->times = 0;
		cout << "请输入第" << i+1 << "个元素:";
		cin >> current->c;
		p->next = current;
		p = current;
	}
	p->next = NULL;
	return head;
}

/*输出一个带头节点的单链表*/
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
	cout << "请输入查找表:";
	head = Create();
	cout << "请输入操作:" << endl;
	cout << "1.查询;" << endl;
	cout << "2.输出查询表;" << endl;
	cout << "3.退出." <<endl;
	cin >> flag;
	while (flag == 1 || flag == 2){
		switch (flag) {
			case 1:
				cout << "请输入要查询的元素:";
				cin >> c;
				index = Search(head,c);
				if (index)
					cout << "元素下标为:" << index << endl;
				else
					cout << "未查询到元素" << c << "!!!" << endl;
				break;
			case 2:
				Print(head);
				break;
		}
		cout << "请输入操作:" << endl;
		cout << "1.查询;" << endl;
		cout << "2.输出查询表;" << endl;
		cout << "3.退出." << endl;
		cin >> flag;
	}
	return 0;
}
