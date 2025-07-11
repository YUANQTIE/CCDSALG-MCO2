#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph.h"

void sortAlphabetically(Graph graph, char order[][100]) {
	char temp[100];
	for(int i=0; i<graph.numOfVertices; i++) {
		for(int j=0; j<graph.numOfVertices - i - 1; j++) {
			if(strcmp(order[j], order[j+1]) > 0) {
				strcpy(temp, order[j]);
				strcpy(order[j], order[j+1]);
				strcpy(order[j+1], temp);
			}
		}
	}
}

void createGraph(Graph* graph, int numOfVertices) {
	graph->numOfVertices = numOfVertices;
	graph->indexOfRow = -1;
	for(int i=0; i<numOfVertices; i++) {
		for(int j=0; j<numOfVertices; j++) {
			graph->adjacencyMatrix[i][j] = 0;
		}
	}
}

int findVertexID(Graph graph, char* vertex) {
	int numOfVertices = graph.numOfVertices;
	int i;
	for(i=0; i<numOfVertices; i++) {
		if(strcmp(graph.vertices[i], vertex) == 0) {
			return i;
		}
	}
	return -1;
}

void addVertex(Graph* graph, char* vertex) {
	int indexOfRow = graph->indexOfRow;
	if(findVertexID(*graph, vertex) == -1) {
		strcpy(graph->vertices[indexOfRow+1], vertex);
		graph->indexOfRow += 1;
	}
}



void updateMatrix(Graph* graph, char* firstVertex, char* adjacentVertex) {
	int rowIndex = findVertexID(*graph, firstVertex);
	int colIndex = findVertexID(*graph, adjacentVertex);
	graph->adjacencyMatrix[rowIndex][colIndex] = 1;
}

int getDegree(Graph graph, char* vertex) {
	int degree = 0;
	int rowIndex = findVertexID(graph, vertex);
	for(int i=0; i<graph.numOfVertices; i++) {
		degree += graph.adjacencyMatrix[rowIndex][i];
	}
	return degree;
}

void computeNumOfEdges(Graph* graph) {
	int num=0;
	for(int i=0; i<graph->numOfVertices; i++) {
		num += getDegree(*graph, graph->vertices[i]);
	}
	num/=2;
	graph->numOfEdges = num;
}




