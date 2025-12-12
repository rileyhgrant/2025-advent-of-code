#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define BUFFER_SIZE 256
#define MAX_NODES 2048

void print_formatted_time_11(double seconds)
{
    if (seconds >= 1.0) {
        printf("%.3fs", seconds);
    } else if (seconds >= 1e-3) {
        printf("%.3fms", seconds * 1e3);
    } else if (seconds >= 1e-6) {
        printf("%.0fus", seconds * 1e6);
    } else {
        printf("%.0fns", seconds * 1e9);
    }
}

typedef struct Node {
    char label[4];
    int to_count;
    struct Node *to_nodes[32]; // based on input max is 20, 30 to be safe
} Node;

typedef struct {
    Node *nodes[MAX_NODES];
    int node_count;
} Graph;

void init_graph(Graph *graph)
{
    graph->node_count = 0;
    for (int i = 0; i < MAX_NODES; i++) {
        graph->nodes[i] = NULL;
    }
}

Node *get_or_create_node(Graph *graph, char *label)
{
    if (graph->node_count >= MAX_NODES) {
        printf("\nPANIC! graph overflowed");
    }

    for (int i = 0; i < graph->node_count; i++) {
        if (strcmp(graph->nodes[i]->label, label) == 0) {
            return graph->nodes[i];
        }
    }

    Node *new_node = malloc(sizeof(Node));
    strncpy(new_node->label, label, 3);
    new_node->label[3] = '\0';
    new_node->to_count = 0;

    graph->nodes[graph->node_count] = new_node;
    graph->node_count++;

    return new_node;
}

void traverse(Graph *graph, Node *node, int num_seen, char *seen[MAX_NODES],
              long long *part1)
{
    for (int i = 0; i < node->to_count; i++) {
        Node *to_node = node->to_nodes[i];
        char *to_label = to_node->label;

        if (strcmp(to_label, "out") == 0) {
            (*part1)++;
            return;
        }

        // linear search -- bad but hopefully tolerable here
        for (int j = 0; j < num_seen; j++) {
            if (strcmp(seen[j], to_label) == 0) {
                return;
            }
        }

        seen[num_seen] = to_label;
        int new_seen = num_seen + 1;
        traverse(graph, to_node, new_seen, seen, part1);
    }
}

int day11()
{

    struct timespec start, end;
    timespec_get(&start, TIME_UTC);

    char buffer[BUFFER_SIZE];
    FILE *fptr;
    char *input_path = "./input/day11.txt";
    fptr = fopen(input_path, "r");

    Graph graph;
    init_graph(&graph);

    Node *start_node;

    while (fgets(buffer, BUFFER_SIZE, fptr)) {
        buffer[strcspn(buffer, "\n")] = '\0';

        char *innerPtr;
        char *from_label = strdup((strtok_r(buffer, ":", &innerPtr)));
        Node *from_node = get_or_create_node(&graph, from_label);

        if (strcmp(from_label, "you") == 0) {
            start_node = from_node;
        }

        char *token = strtok_r(NULL, " ", &innerPtr);
        while (token != NULL) {
            char *to_label = strdup(token);
            Node *to_node = get_or_create_node(&graph, to_label);

            from_node->to_nodes[from_node->to_count] = to_node;
            from_node->to_count++;

            token = strtok_r(NULL, " ", &innerPtr);
        }
    }

    fclose(fptr);

    long long *part1 = (long long *)malloc(sizeof(long long));
    *part1 = 0;

    char *seen[MAX_NODES];
    seen[0] = "you";
    int num_seen = 1;
    traverse(&graph, start_node, num_seen, seen, part1);

    timespec_get(&end, TIME_UTC);
    long long p1_seconds = end.tv_sec - start.tv_sec;
    long long p1_nanoseconds = end.tv_nsec - start.tv_nsec;
    double p1_elapsed_s =
        ((p1_seconds * 1000) + (p1_nanoseconds / 1.0e6)) / 1000.0;

    printf("\n -- Part 1 (");
    print_formatted_time_11(p1_elapsed_s);
    printf("): %lld", *part1); // 523 correct

    printf("\n -- Part 2 (");
    print_formatted_time_11(p1_elapsed_s);
    printf("): %lld", -1LL);

    return 0;
}
