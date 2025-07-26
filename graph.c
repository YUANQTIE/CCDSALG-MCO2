/***********************************************************************************
**********************
Developed and Tested by: 
Yuan Miguel A. Panlilio, 12413135
Nigel Henry S. So, 12413801
Princess Ayesa A. Tullao, 12412112
************************************************************************************
*********************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph.h"

/*Function that sorts the vertices of a graph in alphabetical order.
    @param graph - contains the vertices.
    @param order - contains the alphabetically sorted vertices of the graph
*/
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

/*Function that returns the vertex ID of a specific vertex.
    @param graph - contains the information.
    @param vertex - the specific vertex
    @return the vertex ID
*/
int findVertexID(Graph graph, char* vertex) {
	int flag = -1;
	int numOfVertices = graph.numOfVertices;
	int i;
	for(i=0; i<numOfVertices; i++) {
		if(strcmp(graph.vertices[i], vertex) == 0) {
			flag = i;
		}
	}
	return flag;
}

/*Function that adds a vertex to the graph.
    @param graph - where the vertex will be added.
    @param vertex - the vertex to be added
*/
void addVertex(Graph* graph, char* vertex) {
	int indexOfRow = graph->indexOfRow;
	if(findVertexID(*graph, vertex) == -1) {
		strcpy(graph->vertices[indexOfRow+1], vertex);
		graph->indexOfRow += 1;
	}
}

/*Function that updates the matrix by indicating an edge between the firstVertex
  and the adjacentVertex.
    @param graph - contains the adjacency matrix to be updated.
    @param firstVertex - a vertex 
    @param adjacentVertex - a vertex adjacent to the firstVertex
*/
void updateMatrix(Graph* graph, char* firstVertex, char* adjacentVertex) {
	int rowIndex = findVertexID(*graph, firstVertex);
	int colIndex = findVertexID(*graph, adjacentVertex);
	graph->adjacencyMatrix[rowIndex][colIndex] = 1;
}

/*Function that returns the degree of a specific vertex.
    @param graph - contains the information.
    @param vertex - the specific vertex
    @return the degree
*/
int getDegree(Graph graph, char* vertex) {
	int degree = 0;
	int rowIndex = findVertexID(graph, vertex);
	for(int i=0; i<graph.numOfVertices; i++) {
		degree += graph.adjacencyMatrix[rowIndex][i];
	}
	return degree;
}

/*Function that computes the number of edges of a graph and stores the information
  in the graph.
    @param graph - contains and stores the information.
*/
void computeNumOfEdges(Graph* graph) {
	int num=0;
	Graph tempGraph = *graph;
	
	for(int i=0; i<tempGraph.numOfVertices; i++) {
		for(int j=0; j<tempGraph.numOfVertices; j++) {
			if(tempGraph.adjacencyMatrix[i][j] == 1) {
				num++;
				tempGraph.adjacencyMatrix[j][i] = 0;
			}
		}
	}
	graph->numOfEdges = num;
}

/*Function that checks if a specific vertex is found in the graph.
    @param graph1 - contains the information.
    @param vertex - the specific vertex
    @return 1 if found otherwise -1
*/
int checkVertex(Graph graph1, char* vertex) {
	for(int i=0; i<graph1.numOfVertices; i++) {
		if(strcmp(graph1.vertices[i], vertex) == 0) {
			return 1;
		}
	}
	return -1;
}

/*Function that checks if a specific edge is found in the graph.
    @param graph1 - contains the information.
    @param edge - the specific edge
    @return 1 if found otherwise -1
*/
int checkEdge(Graph graph1, char* edge) {
	for(int i=0; i<graph1.numOfEdges; i++) {
		if(strcmp(graph1.edges[i], edge) == 0) {
			return 1;
		}
	}
	return -1;
}

/*Function that finds the edges of a graph and stores them in the graph.
    @param graph - contains and stores the information.
*/
void getEdges(Graph* graph) {
	Graph tempGraph = *graph;
	char sort[MAX_VERTICES][100];
	char line[1000];
	int original;
	int ctr=0;
	for(int i=0; i<tempGraph.numOfVertices; i++) {
		strcpy(sort[i], tempGraph.vertices[i]);
	}
	sortAlphabetically(tempGraph, sort);
	for(int i=0; i<tempGraph.numOfVertices; i++) {
		original = i;
		i = findVertexID(tempGraph, sort[i]);
		for(int j=0; j<tempGraph.numOfVertices; j++) {
			line[0] = '\0';
			if(tempGraph.adjacencyMatrix[i][j] == 1) {
				if(strcmp(tempGraph.vertices[i], tempGraph.vertices[j]) < 0) {
					strcat(line, "(");
					strcat(line, tempGraph.vertices[i]);
					strcat(line, ",");
					strcat(line, tempGraph.vertices[j]);
					strcat(line, ")");
				}
				else {
					strcat(line, "(");
					strcat(line, tempGraph.vertices[j]);
					strcat(line, ",");
					strcat(line, tempGraph.vertices[i]);
					strcat(line, ")");
				}
				tempGraph.adjacencyMatrix[j][i] = 0;
				strcpy(graph->edges[ctr], line);
				ctr++;
			}
		}
		i = original;
	}
}

/*Function that creates a graph.
    @param graph - the graph to be created.
    @param numOfVertices - the number of vertices of the graph
*/
void createGraph(Graph* graph, int numOfVertices) {
	graph->numOfVertices = numOfVertices;
	graph->indexOfRow = -1;
	for(int i=0; i<numOfVertices; i++) {
		for(int j=0; j<numOfVertices; j++) {
			graph->adjacencyMatrix[i][j] = 0;
		}
	}
}
