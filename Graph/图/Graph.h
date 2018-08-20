#include<climits>
#include <iostream>
#include<stdlib.h>

#ifndef GRAPH
#define GRAPH

#define INFINITY INT_MAX
#define MAX_VERTEX_NUM 100
#define VertexType char
typedef enum {DG, UDG} GraphKind;

//邻接矩阵的定义 
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

//邻接表的定义 
typedef struct ArcNode{
	int adjvex;				//该弧所指向的顶点位置
	struct ArcNode *nextarc;//指向下一条弧的指针
}ArcNode;

typedef struct VNode{
	VertexType data;		//顶点信息
	ArcNode *firstarc;		//指向第一条依附该顶点的弧的指针
}VNode,AdjList[MAX_VERTEX_NUM];

typedef struct{
	AdjList vertices;
	int vexnum,arcnum;		//图的当前顶点数和弧数
	GraphKind kind;			//图的种类标志
}ALGraph;

struct CloseEdge{
	VertexType adjvex;
	int lowcost;
}mCloseEdge[MAX_VERTEX_NUM];

int Minimum(struct CloseEdge mCloseEdge[],int length);

/*
*定位用邻接矩阵表示的图的顶点vex的位置 
*/ 
int MGraphLocate(MGraph G,char vex){
	for (int i = 0; i < G.vexnum; i++)
	  if (G.vexs[i] == vex)  return i;
	return -1;								//返回-1为没有找到该顶点 
}


/*
*创建用邻接矩阵表示的有向图 
*/ 
void CreateDMGraph(MGraph &G){
	std::cout << "请输入图的顶点数和弧数:";
	std::cin >> G.vexnum >> G.arcnum;							//读入图的顶点数和边数 
	std::cout << "请输入各顶点:";
	for (int i = 0; i < G.vexnum; i++)  std::cin >> G.vexs[i];	//读入图的各个顶点 
	for (int i = 0; i < G.vexnum; i++)
	  for (int j = 0; j < G.vexnum; j++)
	    { G.arcs[i][j].adj = 0; G.arcs[i][j].info = '\0';}		//初始化邻接矩阵 
	    
	for (int k = 0; k < G.arcnum; k++){							//创建邻接矩阵 
		char v1,v2;
		std::cout << "请输入第" << k+1 << "条边依附的顶点:";
		std::cin >> v1 >> v2;
		int i = MGraphLocate(G,v1),j = MGraphLocate(G,v2);		//找到输入顶点的位置 
		G.arcs[i][j].adj = 1;
	}
}


/*
*创建用邻接矩阵表示的无向图 
*/ 
void CreateUDMGraph(MGraph &G){
	std::cout << "请输入图的顶点数和弧数:";
	std::cin >> G.vexnum >> G.arcnum;							//读入图的顶点数和边数 
	std::cout << "请输入各顶点:";
	for (int i = 0; i < G.vexnum; i++)  std::cin >> G.vexs[i];	//读入图的各个顶点 
	for (int i = 0; i < G.vexnum; i++)
	  for (int j = 0; j < G.vexnum; j++)
	    { G.arcs[i][j].adj = 0; G.arcs[i][j].info = '\0';}		//初始化邻接矩阵 
	    
	for (int k = 0; k < G.arcnum; k++){							//创建邻接矩阵 
		char v1,v2;
		std::cout << "请输入第" << k+1 << "条边依附的顶点:";
		std::cin >> v1 >> v2;
		int i = MGraphLocate(G,v1),j = MGraphLocate(G,v2);		//找到输入顶点的位置 
		G.arcs[i][j].adj = G.arcs[j][i].adj = 1;
	}
}

/*
*创建用邻接矩阵表示的无向网 
*/ 
void CreateUDMNet(MGraph &G){
	std::cout << "请输入图的顶点数和弧数:";
	std::cin >> G.vexnum >> G.arcnum;							//读入图的顶点数和边数 
	std::cout << "请输入各顶点:";
	for (int i = 0; i < G.vexnum; i++)  std::cin >> G.vexs[i];	//读入图的各个顶点 
	for (int i = 0; i < G.vexnum; i++)
	  for (int j = 0; j < G.vexnum; j++)
	    { G.arcs[i][j].adj = INT_MAX; G.arcs[i][j].info = '\0';}		//初始化邻接矩阵 
	    
	for (int k = 0; k < G.arcnum; k++){							//创建邻接矩阵 
		char v1,v2;
		int weight = 0;
		std::cout << "请输入第" << k+1 << "条边依附的顶点和该条边的权重:";
		std::cin >> v1 >> v2 >> weight;
		int i = MGraphLocate(G,v1),j = MGraphLocate(G,v2);		//找到输入顶点的位置 
		G.arcs[i][j].adj = G.arcs[j][i].adj = weight;
	}
}


/*
*定位用邻接表表示的图的顶点vex的位置 
*/ 
int ALGraphLocate(ALGraph G,char vex){
	for (int i = 0; i < G.vexnum; i++)
	  if (G.vertices[i].data == vex)  return i;
	return -1;										//返回-1为没有找到该顶点 
}

/*
*创建用邻接表表示的有向图 
*/ 
void CreateDALGraph(ALGraph &G){
	std::cout << "请输入图的顶点数和弧数:";
	std::cin >> G.vexnum >> G.arcnum;							//读入图的顶点数和边数 
	
	std::cout << "请输入各顶点:";								//读入图的各个顶点,并将该顶点初始化 
	for (int i = 0; i < G.vexnum; i++){
		std::cin >> G.vertices[i].data;
		G.vertices[i].firstarc = NULL;
	}
	
	for (int k = 0; k < G.arcnum; k++){							//创建每个顶点的邻接链表 
		char v1,v2;
		std::cout << "请输入第" << k+1 << "条边依附的顶点:";
		std::cin >> v1 >> v2;
		int i = ALGraphLocate(G,v1),j = ALGraphLocate(G,v2);	//找到输入顶点的位置 
		ArcNode* p = new ArcNode;								 
		if(!p)  exit(1);
																//将弧插入对应顶点的邻接链表中 
		p->adjvex = j;
		p->nextarc = G.vertices[i].firstarc;
		G.vertices[i].firstarc = p;
	}
}


/*
*创建用邻接表表示的无向图 
*/ 
void CreateUDALGraph(ALGraph &G){
	std::cout << "请输入图的顶点数和弧数:";
	std::cin >> G.vexnum >> G.arcnum;
	std::cout << "请输入各顶点:";
	for (int i = 0; i < G.vexnum; i++){
		std::cin >> G.vertices[i].data;
		G.vertices[i].firstarc = NULL;
	}
	for (int k = 0; k < G.arcnum; k++){
		char v1,v2;
		std::cout << "请输入第" << k+1 << "条边依附的顶点:";
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
