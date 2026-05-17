#ifndef GRAPH_H
#define GRAPH_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    int nodes;
    int** matrix;
}Graph;

Graph* create_graph(int nodes);
void free_graph(Graph* g);
void print_graph(Graph* g);
void generate_hamilton_graph(Graph* g, int saturation);
void generate_non_hamilton_graph(Graph* g, int saturation);

#endif