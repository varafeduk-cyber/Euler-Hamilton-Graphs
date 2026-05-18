#include "algorithms.h"

void find_euler_cycle(Graph* g){
    int n = g->nodes;

    //kopia matricy dla sterki reber vo vremia obchoda
    int** temp_matrix = (int**)malloc(n * sizeof(int*));
    for(int i = 0; i < n; i++){
        temp_matrix[i] = (int*)malloc(n * sizeof(int));
        for(int j = 0; j < n; j++){
            temp_matrix[i][j] = g->matrix[i][j];
        }
    }

    int max_size = n * n;
    int* stack = (int*)malloc(max_size * sizeof(int));
    int* result = (int*)malloc(max_size * sizeof(int));

    int stack_top = 0;
    int result_top = 0;

    //naczalo - verszina 0 (gora everest niczto po sravnenyu so mnooooooj)
    stack[stack_top] = 0;

    while(stack_top >= 0){
        int curr = stack[stack_top];
        int has_neigbor = 0;
        int next_node = -1;

        //looking for not  visited neigbor
        for(int i = 0; i < n; i++){
            if(temp_matrix[curr][i] == 1){
                has_neigbor = 1;
                next_node = i;
                break;
            }
        }

        if(has_neigbor){
            stack_top++;
            stack[stack_top] = next_node;
            temp_matrix[curr][next_node] = 0;
            temp_matrix[next_node][curr] = 0;
        } else {
            result[result_top] = curr;
            result_top++;
            stack_top--;
        }
    }

    printf("Euler Cycle: ");
    for(int i = result_top - 1; i >= 0; i--){
        printf("%d", result[i] + 1);
        if(i > 0) printf(" -> ");
    }
    printf("\n");

    for(int i = 0; i < n; i++){
        free(temp_matrix[i]);
    }
    free(temp_matrix);
    free(stack);
    free(result);
}

int hamilton_backtrack(Graph* g, int* path, int* visited, int pos){
    int n = g->nodes;

    if(pos == n){
        if(g->matrix[path[pos - 1]][path[0]] == 1){
            return 1;
        }
        return 0;
    }

    for(int v = 1; v < n; v++){
        if(g->matrix[path[pos-1]][v] == 1 && !visited[v]){
            path[pos] = v;
            visited[v] = 1;

            if(hamilton_backtrack(g, path, visited, pos + 1)){
                return 1;
            }
//jesli nie priwelo k reszeniu szag nazad
            visited[v] = 0;
            path[pos] = -1;
        }
    }
    return 0;
}

void find_hamilton_cycle(Graph* g){
    int n = g->nodes;

    int* path = (int*)malloc(n * sizeof(int));
    int* visited = (int*)calloc(n, sizeof(int));

    for(int i = 0; i < n; i++) path[i] = -1;

    path[0] = 0;
    visited[0] = 1;

    if(hamilton_backtrack(g, path, visited, 1)){
        printf("Hamilton cycle: ");
        for(int i = 0; i < n; i++){
            printf("%d -> ", path[i] + 1);
        }
        printf("%d\n", path[0] + 1);
    } else{
        printf("No Hamilton cycle found in this graph.\n");
    }
    free(path);
    free(visited);
}