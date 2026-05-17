#include <time.h>
#include "graph.h"

Graph*create_graph(int nodes){
    Graph* g = (Graph*)malloc(sizeof(Graph));
    if(!g) return NULL;

    g->nodes = nodes;
    g->matrix = (int**)malloc(nodes * sizeof(int*));

    for(int i = 0; i < nodes; i++){
        g->matrix[i] = (int*)calloc(nodes, sizeof(int));
    }
    return g;
}

void free_graph(Graph* g){
    if(!g) return;
    for(int i = 0; i < g->nodes; i++){
        free(g->matrix[i]);
    }
    free(g->matrix);
    free(g);
}

void print_graph(Graph* g){
    if(!g) return;
    printf("\n     | ");
    for(int i = 0; i < g->nodes; i++) printf("%2d ", i + 1);
    printf("\n-----+");
    for(int i = 0; i < g->nodes; i++) printf("---");
    printf("\n");

    for(int i = 0; i < g->nodes; i++){
        printf("%2d   | ", i + 1);
        for(int j = 0; j < g->nodes; j++){
            printf("%2d ", g->matrix[i][j]);
        }
        printf("\n");
    }

}

