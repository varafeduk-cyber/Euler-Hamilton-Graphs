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