/*
*图用邻接表的形式储存
*
*/
void Loop_dfs(ALGraph G,int current,int* loop,int depth){
	ArcNode* p = G.vertices[current].firstarc;
  	loop[depth] = current;
  	while (p) {
    	if (p->adjvex == loop[0]) {
      		cout << "第" << count++ << "条回路:";
      		for (int i = 0; i < depth; i ++)
        		cout << G.vertices[loop[i]].data << "->" << G.vertices[loop[i+1]];
      		cout << G.vertices[loop[i]].data << "->" << G.vertices[loop[0]] << endl;
    	}else if (flag[p->adjvex] == 0) {
      		flag[p->adjvex] == 1;
      		Loop_dfs(G,p->adjvex,loop,depth+1);
      		flag[p->adjvex] == 0;
    	}
    	p = p->nextarc;
  	}
}

int visited[MAXSIZE]
//出发点为i，终点为j，长度为k
int exist_path_dfs(ALGraph G,int i,int j,int k) {
    if (i == j && k == 0)
        return 1;
    else if (k > 0) {
        visited[i]=1;
        for (p=G.vertices[i].firstarc; p; p = p->nextarc) {
            int temp = p->adjvex;
            if(!visited[temp] && exist_path_dfs(temp,j,k-1))
              return 1;
        }
        visited[i]=0;
		//这里需要把已经访问的点重新置为0，因为如果当前不存在长度为k
		//到达j点，那么这个点还是可以使用的，因为有可能从其他点出发
		//可以到达j点并且长度为k
    }
    return 0;
}
