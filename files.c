#include<stdio.h> 
#include"files.h"

#define MAX_STRING 100
int readInputFile(char* fileName, Graph* graph, char line[][1000]) {
	FILE* input = fopen(fileName, "r");
	int ctr=0;
	int temp;
	int first;
	char oneLine[1000];
	char firstVertex[MAX_STRING];
	int flag;
	if(input == NULL) {
		printf("File %s not found.", fileName);
		flag = 0;
	}
	else {
		fscanf(input, "%d\n", &(graph)->numOfVertices);
		createGraph(graph, graph->numOfVertices);
		for(int i=0; i<graph->numOfVertices; i++) {
			if(fgets(oneLine, sizeof(oneLine), input) != NULL) {
				char* vertex = strtok(oneLine, " ");
				strcpy(firstVertex, vertex);
				addVertex(graph, firstVertex);
			}
		}
		fseek(input, 0, SEEK_SET);
		fscanf(input, "%d\n", &temp);
		for(int i=0; i<graph->numOfVertices; i++) {
			if(fgets(oneLine, sizeof(oneLine), input) != NULL) {
				char* vertex = strtok(oneLine, " ");
				strcat(line[ctr], vertex);
				strcat(line[ctr], " ");
				strcpy(firstVertex, vertex);
				first = 1;
				while(vertex != NULL) {
					if(strcmp(vertex, "-1\n") != 0 && first == 0) {
						addVertex(graph, vertex);
						updateMatrix(graph, firstVertex, vertex);
						strcat(line[ctr], vertex);
						strcat(line[ctr], " ");
					}
					vertex = strtok(NULL, " ");
					first = 0;
				}
			}
			ctr++;
		}
		computeNumOfEdges(graph);
		flag = 1;
	}

	return flag;

}


void Output1(char* fileName, Graph graph) {
	int ctr = 0;
	int original;
	char outputFileName[100];
	char sort[MAX_VERTICES][100];
	strcpy(outputFileName, fileName);
	int len = strlen(outputFileName);
	outputFileName[len-4] = '\0';
	strcat(outputFileName, "-SET.txt");
	FILE* output = fopen(outputFileName, "w");
	for(int i=0; i<graph.numOfVertices; i++) {
		strcpy(sort[i], graph.vertices[i]);
	}
	sortAlphabetically(graph, sort);
	fprintf(output, "V(G)={");
	for(int i=0; i<graph.numOfVertices; i++) {
		fprintf(output, "%s", sort[i]);
		if(i != graph.numOfVertices-1){
			fprintf(output, ",");
		}
	}
	fprintf(output, "}\n");
	fprintf(output, "E(G)={");
	for(int i=0; i<graph.numOfVertices; i++) {
		original = i;
		i = findVertexID(graph, sort[i]);
		for(int j=0; j<graph.numOfVertices; j++) {
			if(graph.adjacencyMatrix[i][j] == 1) {
				if(strcmp(graph.vertices[i], graph.vertices[j]) < 0) {
					fprintf(output, "(%s,", graph.vertices[i]);
					fprintf(output, "%s)", graph.vertices[j]);
				}
				else {
					fprintf(output, "(%s,", graph.vertices[j]);
					fprintf(output, "%s)", graph.vertices[i]);
				}
				graph.adjacencyMatrix[j][i] = 0;
				ctr++;
				if(ctr != graph.numOfEdges){
					fprintf(output, ",");
				}
			}
		}
		i = original;
	}
	fprintf(output, "}");
	fclose(output);
}

void Output2(char* fileName, Graph graph) {
	char outputFileName[100];
	char sort[MAX_VERTICES][100];
	strcpy(outputFileName, fileName);
	int len = strlen(outputFileName);
	outputFileName[len-4] = '\0';
	strcat(outputFileName, "-DEGREE.txt");
	FILE* output = fopen(outputFileName, "w");
	for(int i=0; i<graph.numOfVertices; i++) {
		strcpy(sort[i], graph.vertices[i]);
	}
	sortAlphabetically(graph, sort);
	for(int i=0; i<graph.numOfVertices; i++) {
		fprintf(output, "%s   %d", sort[i], getDegree(graph, sort[i]));
		if(i != graph.numOfVertices-1) {
			fprintf(output, "\n");
		}
	}
	fclose(output);
}

void Output3(char* fileName, Graph graph, char line[][1000]) {
	
	int first;
	char outputFileName[100];
	strcpy(outputFileName, fileName);
	int len = strlen(outputFileName);
	outputFileName[len-4] = '\0';
	strcat(outputFileName, "-LIST.txt");
	FILE* output = fopen(outputFileName, "w");
	for(int i=0; i<graph.numOfVertices; i++) {
		char* vertex = strtok(line[i], " ");
		fprintf(output, "%s->", vertex);
		first = 1;
		while(vertex!=NULL) {
			if(strcmp(vertex,"-1") != 0 && first == 0) {
				fprintf(output, "%s->", vertex);
			}
			vertex = strtok(NULL, " ");
			first = 0;
		}
		fprintf(output, "\\");
		fprintf(output, "\n");
	}
	fclose(output);
}

void Output4(char* fileName, Graph graph) {
	char outputFileName[100];
	strcpy(outputFileName, fileName);
	int len = strlen(outputFileName);
	outputFileName[len-4] = '\0';
	strcat(outputFileName, "-MATRIX.txt");
	FILE* output = fopen(outputFileName, "w");
	for(int i=0; i<graph.numOfVertices; i++) {
		fprintf(output, "%s ", graph.vertices[i]);
		for(int j=0; j<graph.numOfVertices; j++) {
			fprintf(output, "%d ", graph.adjacencyMatrix[i][j]);
		}
		fprintf(output, "\n");
	}
	fclose(output);
}





void Output7(char* fileName, char* fileName1, char* fileName2, Graph graph1, Graph graph2) {
	int ctrVertex = 0;
	int ctrEdge = 0;
	char outputFileName[100];
	char sort[MAX_VERTICES][100];
	for(int i=0; i<graph2.numOfVertices; i++) {
		strcpy(sort[i], graph2.vertices[i]);
	}
	sortAlphabetically(graph2, sort);
	strcpy(outputFileName, fileName);
	int len = strlen(outputFileName);
	outputFileName[len-4] = '\0';
	len = strlen(fileName1);
	fileName1[len-4] = '\0';
	len = strlen(fileName2);
	fileName2[len-4] = '\0';
	strcat(outputFileName, "-SUBGRAPH.txt");
	FILE* output = fopen(outputFileName, "w");
	//Check vertices
	for(int i=0; i<graph2.numOfVertices; i++) {
		printf("%s\n", sort[i]);
	}
	for(int i=0; i<graph2.numOfVertices; i++) {
		if(checkVertex(graph1, sort[i])==1) {
			fprintf(output, "%s +", sort[i]);
			ctrVertex++;
		}
		else
			fprintf(output, "%s -", sort[i]);
			
	fprintf(output, "\n");
	}
	//Check Edges
	getEdges(&graph1);
	getEdges(&graph2);
	for(int i=0; i<graph2.numOfEdges; i++) {
		if(checkEdge(graph1, graph2.edges[i]) == 1) {
			fprintf(output, "%s +", graph2.edges[i]);
			ctrEdge++;
		}
		else
			fprintf(output, "%s -", graph2.edges[i]);
			
		fprintf(output, "\n");
	}
	
	if(ctrVertex == graph2.numOfVertices && ctrEdge == graph2.numOfEdges) {
		fprintf(output, "%s is a subgraph of %s.", fileName2, fileName1);
	}
	else
		fprintf(output, "%s is not a subgraph of %s.", fileName2, fileName1);
		
	fclose(output);
}
