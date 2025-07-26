/***********************************************************************************
**********************
Developed by: 
Yuan Miguel A. Panlilio, 12413135
Nigel Henry S. So, 12413801
Princess Ayesa A. Tullao, 12412112
************************************************************************************
*********************/

#ifndef TRAVERSAL_H
#define TRAVERSAL_H
#include "graph.h"

void sortAdjacentVerticesAndIndices(char names[][100], int indices[], int count);
void BFS(Graph graph, char start[100], char bfsvertices[][100], int *addedVertices);
void DFS(Graph graph, char start[100], char dfsvertices[][100], int *addedVertices);

#endif
