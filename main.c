#include <stdio.h>
#include <string.h>
#include "graph.h"
#include "algorithms.h"

int main(int argc, char* argv[]){
    if(argc < 2){
        printf("Error: No startup arguments.\n");
        printf("Use: %s --hamilton or %s --non-hamilton\n", argv[0],argv[0]);
        return 1;
    }

    int nodes = 0;
    int saturation = 0;
    Graph* my_graph = NULL;


    if(strcmp(argv[1], "--hamilton") == 0){
        printf("nodes> ");
        scanf("%d", &nodes);
        if(nodes <= 10){
            printf("Error: Nodes must be greater than 10!\n");
            return 1;
        } 
        printf("saturation> ");
        scanf("%d", &saturation);
        if(saturation != 30 && saturation != 70){
            printf("Error: Saturation must be 30 or 70!\n");
            return 1;
        }
        
        my_graph = create_graph(nodes);
        generate_hamilton_graph(my_graph, saturation);

    } else if(strcmp(argv[1], "--non-hamilton") == 0){
        printf("nodes> ");
        if(scanf("%d", &nodes) != 1 || nodes <= 0){
            printf("Error: Wrong number of nodes!\n");
            return 1;
        }
        saturation = 50;

        my_graph = create_graph(nodes);
        generate_non_hamilton_graph(my_graph, saturation);

    } else {
        printf("Error: Unknown argument '%s'\n", argv[1]);
        printf("Use: --hamilton or --non-hamilton\n");
        return 1;
    }

    char action[100];
    
    while(1){
        printf("action> ");
        if(scanf(" %99[^\n]",action) == EOF) break;
        if(strcmp(action, "print") == 0){
            print_graph(my_graph); 
        } else if(strcmp(action, "euler") == 0){
            find_euler_cycle(my_graph);
        } else if(strcmp(action, "exit") == 0){
        break;
        } else {
            printf("Unknown action! Try 'print' or 'exit'.\n");
        }
    } 

    free_graph(my_graph);
    return 0;
}