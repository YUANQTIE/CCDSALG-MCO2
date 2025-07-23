/***********************************************************************************
**********************
Developed by: 
Yuan Miguel A. Panlilio, 12413135
Nigel Henry S. So, 12413801
Princess Ayesa A. Tullao, 12413801
************************************************************************************
*********************/

#include<stdio.h>
#include"graph.h"
#include"files.h"
#include"queue.h"

/*Function that sorts adjacent vertex names and their corresponding indices alphabetically.
  This is typically used before DFS traversal to ensure consistent and ordered visiting of adjacent nodes.
	@param names   - a 2D array of strings representing the names of adjacent vertices.
 	@param indices - an array of integers representing the corresponding indices of the vertices in the graph.
  	@param count   - the number of adjacent vertices to sort.
*/
void sortAdjacentVerticesAndIndices(char names[][100], int indices[], int count) {
    char tempName[100];
    int tempIndex;
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (strcmp(names[j], names[j + 1]) > 0) {
                strcpy(tempName, names[j]);
                strcpy(names[j], names[j + 1]);
                strcpy(names[j + 1], tempName);
                tempIndex = indices[j];
                indices[j] = indices[j + 1];
                indices[j + 1] = tempIndex;
        	}	
    	}
	}
}


/* Function that performs Breadth-First Search (BFS) traversal on a graph.
   @param graph - the graph to be traversed
   @param start - the name of the starting vertex for traversal
   @param bfsvertices - a 2D array to store the order of visited vertices
*/
void BFS(Graph graph, char start[100], char bfsvertices[][100]){
    int checkedVertices[graph.numOfVertices];
    char sorted[graph.numOfVertices][100];
    for (int i = 0; i < graph.numOfVertices; i++) 
    {
        strcpy(sorted[i], graph.vertices[i]);
    }
    sortAlphabetically(graph, sorted);
    Queue queue;
    Create(&queue);
	
    for (int i = 0; i < graph.numOfVertices; i++) 
    {
        checkedVertices[i] = 0;
    }
	
    int startIndex = findVertexID(graph, start);
    int i = 0;
    checkedVertices[startIndex] = 1;
    Enqueue(&queue, start);

    while (!QueueEmpty(&queue)) 
    { //if all of queue elements have been added to the final BFs list, the loop terminates.
        char* readInput = QueueHead(&queue);
        strcpy(bfsvertices[i], Dequeue(&queue)); //copies the queue element to the final BFS list.
        i++;
        int readIndex = findVertexID(graph, readInput);
	    
        for (int j = 0; j < graph.numOfVertices; j++) 
	{
            int connected = findVertexID(graph, sorted[j]); //find the vertex ID of a possibly connected vertex from sorted list.
            if (!checkedVertices[connected] && graph.adjacencyMatrix[readIndex][connected] && !QueueFull(&queue)) //checks if vertex has already added and if the vertex is connected to the vertex at the head of the queue.
	    {
                checkedVertices[connected] = 1;
                Enqueue(&queue, sorted[j]);
            }
        }
    }
}

/* Function that performs Depth-First Search (DFS) traversal on a graph.
   @param graph - the graph to be traversed
   @param start - the name of the starting vertex for traversal
   @param dfsvertices - a 2D array to store the order of visited vertices
*/
void DFS(Graph graph, char start[100], char dfsvertices[][100]) {
    int visited[graph.numOfVertices];
    int i = 0;
	int stack[MAX_VERTICES];
    int top =-1;

    for (int j =0; j <graph.numOfVertices; j++) {
        visited[j] =0;
    }
    int startIndex =findVertexID(graph, start);
    stack[++top] =startIndex;

    while (top>= 0) {
        int current = stack[top--];

        if (!visited[current]) {
            visited[current] =1;
            strcpy(dfsvertices[i++], graph.vertices[current]);
            
            char adjacentVertices[graph.numOfVertices][100];
            int adjacentIndices[graph.numOfVertices]; 
            int count = 0;
            

            for (int j =0; j< graph.numOfVertices;j++) {
                if (graph.adjacencyMatrix[current][j] && !visited[j]) {
                    strcpy(adjacentVertices[count], graph.vertices[j]);
                    adjacentIndices[count] = j;
                    count++;
                }
        	}
        	
        	sortAdjacentVerticesAndIndices(adjacentVertices, adjacentIndices, count); //Since we're using an array-based tack, we also need to sort the indices
        	
        	for(int j = count-1; j>=0 ; j--){
				stack[++top] = adjacentIndices[j];
			}
        }
    }
}
