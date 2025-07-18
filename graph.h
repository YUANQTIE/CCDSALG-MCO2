#ifndef GRAPH_H
#define GRAPH_H
#define MAX_VERTICES 20
#define MAX_EDGES 190
#include<string.h>
typedef struct {
	int numOfVertices;
	int numOfEdges;
	int indexOfRow;
	int adjacencyMatrix[MAX_VERTICES][MAX_VERTICES];
	char vertices[MAX_VERTICES][100];
	char edges[MAX_EDGES][1000];
} Graph;

void sortAlphabetically(Graph graph, char order[][100]);
void createGraph(Graph* graph, int numOfVertices);
int findVertexID(Graph graph, char* vertex);
void addVertex(Graph* graph, char* vertex);
void updateMatrix(Graph* graph, char* firstVertex, char* adjacentVertex);
int getDegree(Graph graph, char* vertex);
void computeNumOfEdges(Graph* graph);
int checkVertex(Graph graph1, char* vertex);
void getEdges(Graph* graph);
int checkEdge(Graph graph1, char* edge); 
int getIndex(Graph graph, char* name);

#endif
