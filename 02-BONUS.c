#include<stdio.h>
#include"graph.h"
#include"files.h"

int main() {
	char fileName1[100];
	char fileName2[100];
	char line1[MAX_VERTICES][1000];
	char line2[MAX_VERTICES][1000];
	char outputFileName[100];
	Graph graph1;
	Graph graph2;
	printf("Enter Filename of Graph 1: ");
	scanf("%s", fileName1);
	readInputFile(fileName1, &graph1, line1);
	printf("\nEnter Filename of Graph 2: ");
	scanf("%s", fileName2);
	readInputFile(fileName2, &graph2, line2);
	int len = strlen(fileName1);
	fileName1[len-4] = '\0';
	strcpy(outputFileName, fileName1);
	strcat(outputFileName, "-");
	strcat(outputFileName, fileName2);
	Output7(outputFileName, fileName1, fileName2, graph1, graph2);
}
