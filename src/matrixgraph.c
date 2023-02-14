#include"matrixgraph.h"


//创建无向网
void Create_UDN(AMGraph* G){
	printf("input vexnum: ");
	scanf("%d", &G->vexnum);
	printf("input arcnum: ");
	scanf("%d", &G->arcnum);
	
	for(int i = 0; i < G->vexnum; i++){
		printf("input No.%d vexname: ", i+1);
		scanf("%s", G->v[i]);
	}

	//初始化邻接矩阵
	for(int i = 0; i < G->vexnum; i++){
		for(int j = 0; j < G->vexnum; j++){
			G->a[i][j] = MAX_INT;
		}
	}

	//输入顶点与邻接结点的信息
	printf("input vex and arc: \n");
	for(int k = 0; k < G->arcnum; k++){
		vtype vex1, vex2;
		int w = 0;
		printf("vex: ");
		scanf("%s", vex1);
		printf("arc: ");
		scanf("%s", vex2);
		printf("w: ");
		scanf("%d", &w);

		int i = LocateVex1(G, vex1);
		int j = LocateVex1(G, vex2);
		if(i == -1 || j == -1) return;

		G->a[i][j] = w;
		G->a[j][i] = w;
	}
	
}


//查找下标
int LocateVex1(AMGraph* G, vtype vex){
	int index = -1;
	for(int i = 0; i < G->vexnum; i++){
		if(strcmp(G->v[i], vex) == 0){
			index = i;
			break;
		}
	}
	return index;
}

//打印
void print_graph(AMGraph* G){
	printf("output AMGraph: \n");
	printf("\t");
	for(int i = 0; i < G->vexnum; i++){
		printf("\t%s", G->v[i]);
	}
	printf("\n");
	for(int i = 0; i < G->vexnum; i++){
		printf("\t%s", G->v[i]);
		for(int j = 0; j < G->vexnum; j++){
			printf("\t%d", G->a[i][j]);
		}
		printf("\n");
	}
}



//深度优先搜索
void DFSTraverse(AMGraph* G){
	for(int i = 0; i < G->vexnum; i++){//初始化访问状态
		vist[i] = 0;	
	}
	printf("DFS Traverse: ");
	for(int i = 0; i < G->vexnum; i++){
		if(!vist[i]){
			DFS(G, i);
		}
	}
	printf("\n");
}
void DFS(AMGraph* G, int index){
	printf("->%s ", G->v[index]);
	vist[index] = 1;//跟新访问状态
	for(int i = FirstAdjVex(G, index); i >= 0; i = NextAdjVex(G, index, i)){
		if(!vist[i]){
			DFS(G, i);
		}
	}
}


//查找index第一个邻接点
int FirstAdjVex(AMGraph* G, int index){
	int deflutweight = MAX_INT;
	for(int j = 0; j < G->vexnum; j++){
		if(G->a[index][j] != deflutweight){
			return j;
		}
	}
	return -1;
}
//查找index除i以外的下一个邻接点
int NextAdjVex(AMGraph* G, int index, int i){
	int deflutweight = MAX_INT;
	for(int j = i+1; j < G->vexnum; j++){
		if(G->a[index][j] != deflutweight){
			return j;
		}
	}
	return -1;
}


//非连通图广度优先遍历
void BFSTraverse(AMGraph* G){
	for(int i = 0; i < G->vexnum; i++){
		vist[i] = 0;
	}
	printf("BFS Traverse: ");
	for(int i = 0; i < G->vexnum; i++){
		if(!vist[i]){
			BFS(G, i);
		}
	}
}


//广度优先遍历
void BFS(AMGraph* G, int index){
	QHead* q = initqueue();
	enqueue(q, index);//入队
	while(!queueisempty(q)){
		int u = 0;
		dequeue(q, &u);//出队
		for(int i = FirstAdjVex(G, u); i >= 0; i = NextAdjVex(G, u, i)){
			if(!vist[i]){
				printf("%s ", G->v[i]);
				vist[i] = 1;
				enqueue(q, i);
			}
		}
	}
	printf("\n");
}


//最短路径
void ShortestPath(AMGraph* G, int v0){
	int D[MAX] = {0};//记录最短距离
	int path[MAX] = {0};//记录结点的前驱
	int S[MAX] = {0};//记录访问状态
	/*------------------------初始化---------------------------*/
	
	for(int v = 0; v < G->vexnum; v++){
		S[v] = 0;
		D[v] = G->a[v0][v];
		if(D[v] < MAX_INT) path[v] = v0;//若有边,则v的前驱就是v0
		else path[v] = -1;				//否则前驱初始化为-1
	}
	S[v0] = 1;
	D[v0] = 0;	//源点到源点的距离为0
	
	/*------------循环,计算v0到各个顶点v间的最短路径-----------*/
	
	for(int i = 1; i < G->vexnum; i++){
		int min = MAX_INT;//记录最小路径
		int v = -1;		//记录最小路径的下标
		for(int j = 0; j < G->vexnum; j++){
			if(!S[j] && min > D[j]){//找到没访问过的最小路径和下标
				min = D[j];
				v = j;
			}
		}
		S[v] = 1;
		for(int k = 0; k < G->vexnum; k++){
			if(!S[k] && (D[v] + G->a[v][k] < D[k])){//更新路径和前驱
				D[k] = D[v] + G->a[v][k];
				path[k] = v;
			}
		}
	}

	/*-------------------------打印----------------------------*/
	for(int i = 0; i < G->vexnum; i++){
		printf("%s->%s: ", G->v[v0], G->v[i]);
		print_path(G, path, v0, i);
		printf("[%d]\n", D[i]);
	}
	
}

/*
	打印路径: v0->vi
	@G: 用邻接矩阵表示的图
	@path: 结点的前驱数组
*/
void print_path(AMGraph* G, int* path, int v0, int vi){
	if(v0 == vi) return;
	int a[100] = {0};
	int k = 0;
	a[k++] = vi;
	while(path[vi] != v0){
		int i = path[vi];
		a[k++] = i;
		vi = i;
	}
	a[k] = v0;
	for(int i = k; i > 0; i--){
		printf("%s->", G->v[a[i]]);
	}
	printf("%s  ", G->v[a[0]]);
}


