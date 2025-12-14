#include "hashtable.h"
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

long long traverse(Graph *graph, Node *this_node, char *end_node_label,
                   HashTable *memo)
{
    if (strcmp(this_node->label, end_node_label) == 0) {
        return 1;
    }

    char *key = strdup(this_node->label);

    if (lookup(memo, key) != NULL) {
        int toReturn = atoi(lookup(memo, key)->val);
        return toReturn;
    }

    long long sum = 0;
    for (int i = 0; i < this_node->to_count; i++) {
        Node *to_node = this_node->to_nodes[i];
        char *to_label = to_node->label;

        long long this_result = traverse(graph, to_node, end_node_label, memo);
        sum += this_result;
    }

    char value[30];
    sprintf(value, "%lld", sum);
    install(memo, key, value);
    return sum;
}

int day11()
{

    struct timespec start, end;
    timespec_get(&start, TIME_UTC);

    struct timespec start2, end2;
    timespec_get(&start2, TIME_UTC);

    char buffer[BUFFER_SIZE];
    FILE *fptr;
    char *input_path = "./input/day11.txt";
    fptr = fopen(input_path, "r");

    Graph graph;
    init_graph(&graph);

    Node *start_node;
    Node *svr_node;
    Node *fft_node;
    Node *dac_node;

    while (fgets(buffer, BUFFER_SIZE, fptr)) {
        buffer[strcspn(buffer, "\n")] = '\0';

        char *innerPtr;
        char *from_label = strdup((strtok_r(buffer, ":", &innerPtr)));
        Node *from_node = get_or_create_node(&graph, from_label);

        if (strcmp(from_label, "you") == 0) {
            start_node = from_node;
        }

        if (strcmp(from_label, "svr") == 0) {
            svr_node = from_node;
        }

        if (strcmp(from_label, "fft") == 0) {
            fft_node = from_node;
        }

        if (strcmp(from_label, "dac") == 0) {
            dac_node = from_node;
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

    HashTable *p1_memo = create_table(2048);
    long long part1 = traverse(&graph, start_node, "out", p1_memo);

    timespec_get(&end, TIME_UTC);
    long long p1_seconds = end.tv_sec - start.tv_sec;
    long long p1_nanoseconds = end.tv_nsec - start.tv_nsec;
    double p1_elapsed_s =
        ((p1_seconds * 1000) + (p1_nanoseconds / 1.0e6)) / 1000.0;

    HashTable *svr_to_fft_memo = create_table(2048);
    long long svr_to_fft = traverse(&graph, svr_node, "fft", svr_to_fft_memo);
    HashTable *fft_to_dac_memo = create_table(2048);
    long long fft_to_dac = traverse(&graph, fft_node, "dac", fft_to_dac_memo);
    HashTable *dac_to_out_memo = create_table(2048);
    long long dac_to_out = traverse(&graph, dac_node, "out", dac_to_out_memo);
    long long fft_first = svr_to_fft * fft_to_dac * dac_to_out;

    HashTable *svr_to_dac_memo = create_table(2048);
    long long svr_to_dac = traverse(&graph, svr_node, "dac", svr_to_dac_memo);
    HashTable *dac_to_fft_memo = create_table(2048);
    long long dac_to_fft = traverse(&graph, dac_node, "fft", dac_to_fft_memo);
    HashTable *fft_to_out_memo = create_table(2048);
    long long fft_to_out = traverse(&graph, fft_node, "out", fft_to_out_memo);
    long long dac_first = svr_to_dac * dac_to_fft * fft_to_out;

    long long part2 = fft_first + dac_first;

    timespec_get(&end2, TIME_UTC);
    long long p2_seconds = end2.tv_sec - start2.tv_sec;
    long long p2_nanoseconds = end2.tv_nsec - start2.tv_nsec;
    double p2_elapsed_s =
        ((p2_seconds * 1000) + (p2_nanoseconds / 1.0e6)) / 1000.0;

    printf("\n -- Part 1 (");
    print_formatted_time_11(p1_elapsed_s);
    printf("): %lld", part1); // 523 correct

    printf("\n -- Part 2 (");
    print_formatted_time_11(p2_elapsed_s);
    printf("): %lld", part2); // 517315308154944 correct

    return 0;
}
