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

void generate_hamilton_graph(Graph* g, int saturation){
    int n = g->nodes;
    int max_edges = (n * (n - 1)) / 2;
    int target_edges = (max_edges * saturation) / 100;
    int current_edges = 0;

    srand(time(NULL));

    //bazowyj hamilton cykl
    for(int i = 0; i < n; i++){
        int next = (i + 1) % n;
        g->matrix[i][next] = 1;
        g->matrix[next][i] = 1;
        current_edges++;
    }

    int attempts = 0; //cztoby nie zacyklitca u know bro
    while(current_edges < target_edges && attempts < 10000){
        attempts++;
        int a = rand() % n;
        int b = rand() % n;
        int c = rand() % n;

        if(a == b || b == c || a == c) continue;

        //is free places for triangle 
        if(g->matrix[a][b] == 0 && g->matrix[b][c] == 0 && g->matrix[c][a] == 0){
            g->matrix[a][b] = 1; g->matrix[b][a] = 1;
            g->matrix[b][c] = 1; g->matrix[c][b] = 1;
            g->matrix[c][a] = 1; g->matrix[a][c] = 1;
            current_edges += 3;
        }
    }
    printf("Generated Hamiltonian graph with %d edges (Target: %d)\n", current_edges, target_edges);
}

void generate_non_hamilton_graph(Graph* g, int saturation){
    int n = g->nodes;
    int max_edges = (n * (n - 1)) / 2;
    int target_edges = (max_edges * saturation) / 100;
    int current_edges = 0;

    srand(time(NULL));

    //plus sluczajnye rebra - posledniya werszina 
    int attempts = 0;
    while(current_edges < target_edges && attempts < 10000){
        attempts++;
        int u = rand() % (n - 1);
        int v = rand() % (n - 1);

        if(u != v && g->matrix[u][v] == 0){
            g->matrix[u][v] = 1;
            g->matrix[v][u] = 1;
            current_edges++;
        }
    }
    printf("Generated Non-Hamiltonian graph (Node %d is isolated). Edges: %d\n", n, current_edges);
}