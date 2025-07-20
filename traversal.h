#ifndef TRAVERSAL_H
#define TRAVERSAL_H
#include "graph.h"

void sortAdjacentVerticesAndIndices(char names[][100], int indices[], int count);
void BFS(Graph graph, char start[100], char bfsvertices[][100]);
void DFS(Graph graph, char start[100], char dfsvertices[][100]);

#endif
