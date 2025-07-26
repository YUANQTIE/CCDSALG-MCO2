/***********************************************************************************
**********************
Developed and Tested by: 
Yuan Miguel A. Panlilio, 12413135
Nigel Henry S. So, 12413801
Princess Ayesa A. Tullao, 12412112
************************************************************************************
*********************/

#include<stdio.h> 
#include"files.h"
#define MAX_STRING 100
#include "traversal.h"

/*Function that reads the contents of an input file and stores them in a graph.
    @param fileName- the name of the input file.
    @param graph - where the contents of the file will be stored.
    @param line - a 2D array which is used to store line by line of the input file
    @return 1 if successful or -1 if not successful
*/
int readInputFile(char* fileName, Graph* graph, char line[][1000]) {
	FILE* input = fopen(fileName, "r");
	int temp;
	int first;
	char oneLine[1000];
	char firstVertex[MAX_STRING];
	int flag = -1;
	//Checks if file exists
	if(input == NULL) {
		printf("File %s not found.", fileName);
		flag = 0;
	}
	else {
		//Scans the number of vertices
		fscanf(input, "%d\n", &(graph)->numOfVertices);
		createGraph(graph, graph->numOfVertices);
		
		
		//Obtains the main vertex of each line and adds it to the graph
		for(int i=0; i<graph->numOfVertices; i++) {
			if(fgets(oneLine, sizeof(oneLine), input) != NULL) {
				//Deletes new line
				if(oneLine[strlen(oneLine) - 1] == '\n') {
					oneLine[strlen(oneLine) - 1] = '\0';
				}
				strcpy(line[i], oneLine);
				char* vertex = strtok(oneLine, " \t");
				strcpy(firstVertex, vertex);
				addVertex(graph, firstVertex);
			}
			strcat(line[i], "a");
		}
		fseek(input, 0, SEEK_SET);
		fscanf(input, "%d\n", &temp);
		//Obtains the remaining vertices and adds them to the graph
		for(int i=0; i<graph->numOfVertices; i++) {
			if(fgets(oneLine, sizeof(oneLine), input) != NULL) {
				char* vertex = strtok(oneLine, " \t");
				strcpy(firstVertex, vertex);
				first = 1;
				while(vertex != NULL) {
					if(strcmp(vertex, "-1\n") != 0 && first == 0) {
						addVertex(graph, vertex);
						updateMatrix(graph, firstVertex, vertex);
						//strcat(line[ctr], vertex);
						//strcat(line[ctr], " ");
					}
					vertex = strtok(NULL, " \t");
					first = 0;
				}
			}
			//ctr++;
		}
		computeNumOfEdges(graph);
		flag = 1;
	}
	return flag;
}

/*Function that outputs a file detailing the vertices and edges of the graph
    @param fileName- the name of the output file.
    @param graph - contains the information
*/
void Output1(char* fileName, Graph graph) {
	int ctr = 0;
	int original;
	char outputFileName[100];
	char sort[MAX_VERTICES][100];
	strcpy(outputFileName, fileName);
	int len = strlen(outputFileName);
	//removes the .TXT
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
				//Checks if last edge
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

/*Function that outputs a file detailing the degree of each vertex of a graph
    @param fileName- the name of the output file.
    @param graph - contains the information
*/
void Output2(char* fileName, Graph graph) {
	int len;
	int max = 0;
	char outputFileName[100];
	char sort[MAX_VERTICES][100];
	strcpy(outputFileName, fileName);
	len = strlen(outputFileName);
	outputFileName[len-4] = '\0';
	strcat(outputFileName, "-DEGREE.txt");
	FILE* output = fopen(outputFileName, "w");
	for(int i=0; i<graph.numOfVertices; i++) {
		strcpy(sort[i], graph.vertices[i]);
		len = strlen(graph.vertices[i]);
		if(len > max) {
			max = len;
		}
	}
	sortAlphabetically(graph, sort);
	// Checks how much space should be within rows depending on the longest vertex in terms of character length
	if(max > 10) {
		max += max/3;
	}
	else if(max < 10 && max >= 5){
		max += max/2;
	}
	else {
		max += max;
	}
	for(int i=0; i<graph.numOfVertices; i++) {
		fprintf(output, "%-*s %d", max, sort[i], getDegree(graph, sort[i]));
		if(i != graph.numOfVertices-1) {
			fprintf(output, "\n");
		}
	}
	fclose(output);
}

/*Function that outputs a file containing the adjacency list representation of graph
    @param fileName- the name of the output file.
    @param graph - contains the information
    @param line - a 2D array which contains the line per line contents of the input file
*/
void Output3(char* fileName, Graph graph, char line[][1000]) {
	int first;
	char outputFileName[100];
	strcpy(outputFileName, fileName);
	int len = strlen(outputFileName);
	outputFileName[len-4] = '\0';
	strcat(outputFileName, "-LIST.txt");
	FILE* output = fopen(outputFileName, "w");
	for(int i=0; i<graph.numOfVertices; i++) {
		printf("%s\n", line[i]);
		char* vertex = strtok(line[i], " \t");
		fprintf(output, "%s->", vertex);
		first = 1;
		while(vertex!=NULL) {
			if(strcmp(vertex,"-1a")!= 0 && strcmp(vertex, "-1") && strcmp(vertex, "a") != 0 && first == 0) {
				fprintf(output, "%s->", vertex);
			}
			vertex = strtok(NULL, " \t");
			first = 0;
		}
		fprintf(output, "\\");
		if(i != graph.numOfVertices-1) {
			fprintf(output, "\n");
		}
	}
	fclose(output);
}

/*Function that outputs a file containing the adjeacency matrix representation of graph
    @param fileName- the name of the output file.
    @param graph - contains the information
*/
void Output4(char* fileName, Graph graph) {
	int len;
	int colWidths[graph.numOfVertices];
	int rowWidth = 0;
	char outputFileName[100];
	strcpy(outputFileName, fileName);
	len = strlen(outputFileName);
	outputFileName[len-4] = '\0';
	strcat(outputFileName, "-MATRIX.txt");
	FILE* output = fopen(outputFileName, "w");
	for(int i=0; i<graph.numOfVertices; i++) {
		colWidths[i] = strlen(graph.vertices[i]);
		colWidths[i] += 3;
		len = strlen(graph.vertices[i]);
		if(len > rowWidth) {
			rowWidth = len;
		}
	}
	// Checks how much space should be within rows depending on the longest vertex in terms of character length
	if(rowWidth > 10) {
		rowWidth += rowWidth/3;
	}
	else if(rowWidth < 10 && rowWidth >= 5){
		rowWidth += rowWidth/2;
	}
	else {
		rowWidth += rowWidth;
	}
	fprintf(output, "%*s", rowWidth, "");
	//Column Header
	for(int i=0; i<graph.numOfVertices; i++) {
		fprintf(output, "%-*s", colWidths[i], graph.vertices[i]);
	}
	fprintf(output, "\n");
	
	for (int i = 0; i < graph.numOfVertices; i++) {
		//Row Header
        fprintf(output, "%-*s", rowWidth, graph.vertices[i]);
        for (int j = 0; j < graph.numOfVertices; j++) {
        	//Aligns Per Column Width
            fprintf(output, "%-*d", colWidths[j], graph.adjacencyMatrix[i][j]);
        }
        if(i != graph.numOfVertices - 1) {
        	fprintf(output, "\n");
		}
    }
	fclose(output);
}

/* Function that writes the result of BFS traversal to an output file.
   @param fileName - the name of the original input file
   @param graph - the graph that contains all vertices and edges
   @param start - the name of the starting vertex for BFS traversal
*/
void Output5(char* fileName, Graph graph, char start[100]) {
    char outputFileName[100];
    strcpy(outputFileName, fileName);
    int len = strlen(outputFileName);
	int addedVertices = 0;
    outputFileName[len-4] = '\0';
    strcat(outputFileName, "-BFS.txt");
    FILE* output = fopen(outputFileName, "w");

    char bfsvertices[graph.numOfVertices][100];
    BFS(graph, start, bfsvertices, &addedVertices);

    if (addedVertices > 0){
		for (int j = 0; j < addedVertices - 1; j++) {
        	fprintf(output, "%s ", bfsvertices[j]);
    	}
		fprintf(output, "%s", bfsvertices[addedVertices - 1]);
	}
	else{
		fprintf(output, "%s ", bfsvertices[addedVertices]);
	}

    fclose(output);
}

/* Function that writes the result of DFS traversal to an output file.
   @param fileName - the name of the original input file
   @param graph - the graph that contains all vertices and edges
   @param start - the name of the starting vertex for DFS traversal
*/
void Output6(char* fileName, Graph graph, char start[100]) {
    char outputFileName[100];
    strcpy(outputFileName, fileName);
    int len = strlen(outputFileName);
	int addedVertices = 0;
    outputFileName[len - 4] = '\0';
    strcat(outputFileName,"-DFS.txt");
    FILE* output = fopen(outputFileName,"w");

    char dfsvertices[graph.numOfVertices][100];
    DFS(graph, start, dfsvertices, &addedVertices);

	if (addedVertices > 0){
		for (int j = 0; j < addedVertices - 1; j++) {
        	fprintf(output, "%s ", dfsvertices[j]);
    	}
		fprintf(output, "%s", dfsvertices[addedVertices - 1]);
	}
	else{
		fprintf(output, "%s ", dfsvertices[addedVertices]);
	}
    
    fclose(output);
}


/*Function that outputs a file which determines whether graph2 is a subgraph of graph1
    @param fileName- the name of the output file.
    @param fileName1 - the name of the file of the first graph
    @param fileName2 - the name of the file of the second graph
    @param graph1 - the first graph
    @param graph2 - the second graph
*/
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
