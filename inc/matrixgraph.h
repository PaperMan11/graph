#ifndef __MATRIXGRAPH_H__
#define __MATRIXGRAPH_H__
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linklistqueue.h"
#define MAX 100
#define MAX_INT 999
typedef char vtype[10];
typedef int adjtype;

typedef struct
{
	vtype v[MAX];
	adjtype a[MAX][MAX];
	int vexnum; // 顶点数
	int arcnum; // 边数
} AMGraph;

int vist[MAX]; // 顶点访问状态

void Create_UDN(AMGraph *G);							// 创建无向网
int LocateVex1(AMGraph *G, vtype vex);					// 查找下标
void print_graph(AMGraph *G);							// 打印
void DFSTraverse(AMGraph *G);							// 非连通图深度优先搜索
void DFS(AMGraph *G, int index);						// 连通图深度优先搜索
int FirstAdjVex(AMGraph *G, int index);					// 查找第一个邻接点
int NextAdjVex(AMGraph *G, int index, int i);			// 查找下一个邻接点
void BFSTraverse(AMGraph *G);							// 非连通图广度优先遍历
void BFS(AMGraph *G, int index);						// 连通图广度优先遍历
void ShortestPath(AMGraph *G, int v0);					// 最短路径
void print_path(AMGraph *G, int *path, int v0, int vi); // 打印路径
#endif