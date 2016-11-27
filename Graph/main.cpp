#include <iostream>
#include <memory.h>
#include "Graph.h"
using namespace std;

void Loop_dfs(ALGraph,int,int*,int*,int);
void Loop(ALGraph G);
int exist_path_dfs(ALGraph G,int i,int j,int k);


int count = 0;
void Loop(ALGraph G){
	int loop[100],flag[100] = {0};
	for (int i = 0; i < G.vexnum; i++)
	    Loop_dfs(G,i,loop,flag,0);
}


void Loop_dfs(ALGraph G,int current,int loop[],int flag[],int depth){
	ArcNode* p = G.vertices[current].firstarc;
	flag[current] = 1;
  	loop[depth] = current;
  	while (p) {
    	if (p->adjvex == loop[0]) {
    		int i = 0;
      		cout << "��" << ++count << "����·:";
      		for (; i <= depth; i++)
      			cout << G.vertices[loop[i]].data << "->";
      		cout << G.vertices[loop[0]].data << endl;
    	}else if (flag[p->adjvex] == 0) {
      		flag[p->adjvex] = 1;
      		Loop_dfs(G,p->adjvex,loop,flag,depth+1);
      		flag[p->adjvex] = 0;
    	}
    	p = p->nextarc;
  	}
}

int visited[100];
int exist_path_dfs(ALGraph G,int i,int j,int k) {
    if (i == j && k == 0)
        return 1;
    else if (k > 0) {
        visited[i] = 1;
        for (ArcNode* p = G.vertices[i].firstarc; p; p = p->nextarc) {
            int temp = p->adjvex;
            if( !visited[temp] && exist_path_dfs(G,temp,j,k-1))
              return 1;
        }
        visited[i] = 0;							//������Ҫ���Ѿ����ʵĵ�������Ϊ0
    }
    return 0;
}

int main(){
	ALGraph DG,UDG;
	int operate,k;
	char v1,v2;
	cout << endl << "���������:" << endl;
	cout << "1.�ҳ�����ͼ�е����л�·;" << endl;
	cout << "2.�ж�����ͼ�������������Ƿ���ڳ���Ϊk�ļ�·��;" << endl;
	cout << "3.�˳�;" << endl << "����:"; 
	cin >> operate;
	while(operate == 1 || operate == 2){
		switch (operate){
			case 1:
				CreateDALGraph(DG);
				Loop(DG);
				break;
			case 2:
				CreateUDALGraph(UDG);
				cout << "�����붥���Լ�·����:";
				cin >> v1 >> v2 >> k;
				v1 = tolower(v1);
				v2 = tolower(v2);
				if (ALGraphLocate(UDG,v1) != -1 && ALGraphLocate(UDG,v2) != -1){
					if (exist_path_dfs(UDG,ALGraphLocate(UDG,v1),ALGraphLocate(UDG,v2),k))
					  cout << "����!!" << endl;
					else
					  cout << "������!!" << endl;
				}else{
					cout << "���㲻����!!" << endl;
				}
				break;
		}
		cout << endl << "���������:" << endl;
		cout << "1.�ҳ�����ͼ�е����л�·;" << endl;
		cout << "2.�ж�����ͼ�������������Ƿ���ڳ���Ϊk�ļ�·��;" << endl;
		cout << "3.�˳�;" << endl << "����:"; 
		cin >> operate;
	}
} 
