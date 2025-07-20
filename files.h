#ifndef FILES_H
#define FILES_H
#include"graph.h"
#include"queue.h"

int readInputFile(char* fileName, Graph* graph, char line[][1000]);
void Output1(char* fileName, Graph graph);
void Output2(char* fileName, Graph graph);
void Output3(char* fileName, Graph graph, char line[][1000]);
void Output4(char* fileName, Graph graph);
void Output5(char* fileName, Graph graph, char start[100]) ;
void Output6(char* fileName, Graph graph, char start[100]);
void Output7(char* fileName, char* fileName1, char* fileName2, Graph graph1, Graph graph2);
#endif
