#include<climits>
#include <iostream>
#include<stdlib.h>

#ifndef GRAPH
#define GRAPH

#define INFINITY INT_MAX
#define MAX_VERTEX_NUM 100
#define VertexType char
typedef enum {DG, UDG} GraphKind;

//�ڽӾ���Ķ��� 
typedef struct ArcCell{
	int adj;
	VertexType info;
}ArcCell,AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];

typedef struct{
	VertexType vexs[MAX_VERTEX_NUM];
	AdjMatrix arcs;
	int vexnum,arcnum;
	GraphKind kind;
}MGraph;

//�ڽӱ�Ķ��� 
typedef struct ArcNode{
	int adjvex;				//�û���ָ��Ķ���λ��
	struct ArcNode *nextarc;//ָ����һ������ָ��
}ArcNode;

typedef struct VNode{
	VertexType data;		//������Ϣ
	ArcNode *firstarc;		//ָ���һ�������ö���Ļ���ָ��
}VNode,AdjList[MAX_VERTEX_NUM];

typedef struct{
	AdjList vertices;
	int vexnum,arcnum;		//ͼ�ĵ�ǰ�������ͻ���
	GraphKind kind;			//ͼ�������־
}ALGraph;

struct CloseEdge{
	VertexType adjvex;
	int lowcost;
}mCloseEdge[MAX_VERTEX_NUM];

int Minimum(struct CloseEdge mCloseEdge[],int length);

/*
*��λ���ڽӾ����ʾ��ͼ�Ķ���vex��λ�� 
*/ 
int MGraphLocate(MGraph G,char vex){
	for (int i = 0; i < G.vexnum; i++)
	  if (G.vexs[i] == vex)  return i;
	return -1;								//����-1Ϊû���ҵ��ö��� 
}


/*
*�������ڽӾ����ʾ������ͼ 
*/ 
void CreateDMGraph(MGraph &G){
	std::cout << "������ͼ�Ķ������ͻ���:";
	std::cin >> G.vexnum >> G.arcnum;							//����ͼ�Ķ������ͱ��� 
	std::cout << "�����������:";
	for (int i = 0; i < G.vexnum; i++)  std::cin >> G.vexs[i];	//����ͼ�ĸ������� 
	for (int i = 0; i < G.vexnum; i++)
	  for (int j = 0; j < G.vexnum; j++)
	    { G.arcs[i][j].adj = 0; G.arcs[i][j].info = '\0';}		//��ʼ���ڽӾ��� 
	    
	for (int k = 0; k < G.arcnum; k++){							//�����ڽӾ��� 
		char v1,v2;
		std::cout << "�������" << k+1 << "���������Ķ���:";
		std::cin >> v1 >> v2;
		int i = MGraphLocate(G,v1),j = MGraphLocate(G,v2);		//�ҵ����붥���λ�� 
		G.arcs[i][j].adj = 1;
	}
}


/*
*�������ڽӾ����ʾ������ͼ 
*/ 
void CreateUDMGraph(MGraph &G){
	std::cout << "������ͼ�Ķ������ͻ���:";
	std::cin >> G.vexnum >> G.arcnum;							//����ͼ�Ķ������ͱ��� 
	std::cout << "�����������:";
	for (int i = 0; i < G.vexnum; i++)  std::cin >> G.vexs[i];	//����ͼ�ĸ������� 
	for (int i = 0; i < G.vexnum; i++)
	  for (int j = 0; j < G.vexnum; j++)
	    { G.arcs[i][j].adj = 0; G.arcs[i][j].info = '\0';}		//��ʼ���ڽӾ��� 
	    
	for (int k = 0; k < G.arcnum; k++){							//�����ڽӾ��� 
		char v1,v2;
		std::cout << "�������" << k+1 << "���������Ķ���:";
		std::cin >> v1 >> v2;
		int i = MGraphLocate(G,v1),j = MGraphLocate(G,v2);		//�ҵ����붥���λ�� 
		G.arcs[i][j].adj = G.arcs[j][i].adj = 1;
	}
}

/*
*�������ڽӾ����ʾ�������� 
*/ 
void CreateUDMNet(MGraph &G){
	std::cout << "������ͼ�Ķ������ͻ���:";
	std::cin >> G.vexnum >> G.arcnum;							//����ͼ�Ķ������ͱ��� 
	std::cout << "�����������:";
	for (int i = 0; i < G.vexnum; i++)  std::cin >> G.vexs[i];	//����ͼ�ĸ������� 
	for (int i = 0; i < G.vexnum; i++)
	  for (int j = 0; j < G.vexnum; j++)
	    { G.arcs[i][j].adj = INT_MAX; G.arcs[i][j].info = '\0';}		//��ʼ���ڽӾ��� 
	    
	for (int k = 0; k < G.arcnum; k++){							//�����ڽӾ��� 
		char v1,v2;
		int weight = 0;
		std::cout << "�������" << k+1 << "���������Ķ���͸����ߵ�Ȩ��:";
		std::cin >> v1 >> v2 >> weight;
		int i = MGraphLocate(G,v1),j = MGraphLocate(G,v2);		//�ҵ����붥���λ�� 
		G.arcs[i][j].adj = G.arcs[j][i].adj = weight;
	}
}


/*
*��λ���ڽӱ��ʾ��ͼ�Ķ���vex��λ�� 
*/ 
int ALGraphLocate(ALGraph G,char vex){
	for (int i = 0; i < G.vexnum; i++)
	  if (G.vertices[i].data == vex)  return i;
	return -1;										//����-1Ϊû���ҵ��ö��� 
}

/*
*�������ڽӱ��ʾ������ͼ 
*/ 
void CreateDALGraph(ALGraph &G){
	std::cout << "������ͼ�Ķ������ͻ���:";
	std::cin >> G.vexnum >> G.arcnum;							//����ͼ�Ķ������ͱ��� 
	
	std::cout << "�����������:";								//����ͼ�ĸ�������,�����ö����ʼ�� 
	for (int i = 0; i < G.vexnum; i++){
		std::cin >> G.vertices[i].data;
		G.vertices[i].firstarc = NULL;
	}
	
	for (int k = 0; k < G.arcnum; k++){							//����ÿ��������ڽ����� 
		char v1,v2;
		std::cout << "�������" << k+1 << "���������Ķ���:";
		std::cin >> v1 >> v2;
		int i = ALGraphLocate(G,v1),j = ALGraphLocate(G,v2);	//�ҵ����붥���λ�� 
		ArcNode* p = new ArcNode;								 
		if(!p)  exit(1);
																//���������Ӧ������ڽ������� 
		p->adjvex = j;
		p->nextarc = G.vertices[i].firstarc;
		G.vertices[i].firstarc = p;
	}
}


/*
*�������ڽӱ��ʾ������ͼ 
*/ 
void CreateUDALGraph(ALGraph &G){
	std::cout << "������ͼ�Ķ������ͻ���:";
	std::cin >> G.vexnum >> G.arcnum;
	std::cout << "�����������:";
	for (int i = 0; i < G.vexnum; i++){
		std::cin >> G.vertices[i].data;
		G.vertices[i].firstarc = NULL;
	}
	for (int k = 0; k < G.arcnum; k++){
		char v1,v2;
		std::cout << "�������" << k+1 << "���������Ķ���:";
		std::cin >> v1 >> v2;
		int i = ALGraphLocate(G,v1),j = ALGraphLocate(G,v2);
		ArcNode* p = new ArcNode;
		if(!p)  exit(1);
		p->adjvex = j;
		p->nextarc = G.vertices[i].firstarc;
		G.vertices[i].firstarc = p;
		ArcNode* p1 = new ArcNode;
		if (!p1)  exit(1);
		p1->adjvex = i;
		p1->nextarc = G.vertices[j].firstarc;
		G.vertices[j].firstarc = p1;
	}
}

void MiniSpanTree_PRIM(MGraph G){
	for (int j = 1; j < G.vexnum; j++){
		mCloseEdge[j].adjvex = G.vexs[0];
		mCloseEdge[j].lowcost = G.arcs[0][j].adj;
	}
	mCloseEdge[0].lowcost = 0;
	
	for (int i = 0; i < G.vexnum; i++){
		int min = Minimum(mCloseEdge,G.vexnum);
		std::cout << mCloseEdge[min].adjvex << G.vexs[min] << std::endl;
		mCloseEdge[min].lowcost = 0;
		for (int j = 0; j < G.vexnum; j++){
			if (G.arcs[min][j].adj < mCloseEdge[j].lowcost)
		    	mCloseEdge[j] = {G.vexs[min],G.arcs[min][j].adj}; 
		}
	}
}

int Minimum(struct CloseEdge mCloseEdge[],int length){
	int min = 0,low_cost = INT_MAX;
	for (int i = 0; i < length; i++)
	  if (mCloseEdge[i].lowcost != 0 && mCloseEdge[i].lowcost < low_cost) {
	  	min = i;
	  	low_cost = mCloseEdge[i].lowcost;
	  } 
	 return min; 
}

#endif
