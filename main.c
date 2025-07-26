/***********************************************************************************
**********************
Developed and Tested by: 
Yuan Miguel A. Panlilio, 12413135
Nigel Henry S. So, 12413801
Princess Ayesa A. Tullao, 12412112
************************************************************************************
*********************/

#include<stdio.h>
#include"graph.h"
#include"files.h"
#include"queue.h"

int main() {
	char fileName[100];
	char line[MAX_VERTICES][1000];
	char startingVertex[100];
	int flag1;
	int flag2;
	Graph graph;
	printf("Enter Filename: ");
	scanf("%s", fileName);

	flag1 = readInputFile(fileName, &graph, line);
	

	if (flag1){
		Output1(fileName, graph);
		Output2(fileName, graph);
		Output3(fileName, graph, line);
		Output4(fileName, graph);
		printf("What would be the starting vertex for Output 5 & 6? (Case sensitive): ");
		scanf("%s", startingVertex);
		flag2 = findVertexID(graph, startingVertex);
		if (flag2 == -1){
			printf(("Vertex %s not found."), startingVertex);
		}
		else{
			Output5(fileName, graph, startingVertex);
			Output6(fileName, graph, startingVertex);
		}
	}
}
