#include"matrixgraph.h"


void main(){
	AMGraph G;
	Create_UDN(&G);
	print_graph(&G);
	DFSTraverse(&G);
	BFSTraverse(&G);
	ShortestPath(&G, 0);
}