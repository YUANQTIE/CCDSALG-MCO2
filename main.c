#include<stdio.h>
#include"graph.h"
#include"files.h"

int main() {
	char fileName[100];
	char line[MAX_VERTICES][1000];
	Graph graph;
	printf("Enter Filename: ");
	scanf("%s", fileName);
	readInputFile(fileName, &graph, line);
	Output1(fileName, graph);
	Output2(fileName, graph);
	Output3(fileName, graph, line);
	Output4(fileName, graph);
}
