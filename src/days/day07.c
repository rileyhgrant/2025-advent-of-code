#include "hashtable.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
FILE *fptr;

void print_gr(int rows, char *grid[rows])
{
    printf("\n");
    for (int i = 0; i < rows; i++) {
        printf("\n%s", grid[i]);
    }
}

void beam(int row, int col, int rows, int cols, char *grid[rows],
          long long *part1)
{
    if (row == rows - 1)
        return;
    char below = grid[row + 1][col];
    if (below == '.') {
        grid[row + 1][col] = '|';
        beam(row + 1, col, rows, cols, grid, part1);
    } else if (below == '^') {
        grid[row + 1][col] = 'O';
        (*part1)++;
        grid[row + 1][col - 1] = '|';
        grid[row + 1][col + 1] = '|';
        beam(row + 1, col - 1, rows, cols, grid, part1);
        beam(row + 1, col + 1, rows, cols, grid, part1);
    }
}

long long observe(int row, int col, int rows, int cols, char *grid[rows],
                  HashTable *hash_table)
{
    if (row == rows - 1) {
        return 1LL;
    }

    char below = grid[row + 1][col];
    if (below == '.' || below == '|') {
        return observe(row + 1, col, rows, cols, grid, hash_table);

    } else if (below == '^' || below == 'O') {
        int required_size = snprintf(NULL, 0, "(%d, %d)", row + 1, col);
        char *key = (char *)malloc(required_size + 1);

        if (key != NULL) {
            snprintf(key, required_size + 1, "(%d, %d)", row + 1, col);
        } else {
            fprintf(stderr, "Memory allocation failed!\n");
        }

        if (lookup(hash_table, key) != NULL) {
            long long toReturn = atoll(lookup(hash_table, key)->val);
            return toReturn;
        }
        long long left =
            observe(row + 1, col - 1, rows, cols, grid, hash_table);
        long long right =
            observe(row + 1, col + 1, rows, cols, grid, hash_table);
        long long result = left + right;

        char value[30];
        sprintf(value, "%lld", result);
        install(hash_table, key, value);

        free(key);
        return left + right;
    }

    printf("\nSomething went horribly wrong");
    return -1LL;
}

int day07()
{
    int line_len = 1000;
    char buffer[line_len];

    char *input_path = "./input/day07.txt";

    fptr = fopen(input_path, "r");

    HashTable *hash_table = create_table(256);

    int rows = 0;
    int cols;

    while (fgets(buffer, line_len, fptr)) {
        buffer[strcspn(buffer, "\n")] = '\0';
        cols = strlen(buffer);
        rows++;
    }

    rewind(fptr);
    char *grid[rows];
    for (int i = 0; i < rows; i++) {
        fgets(buffer, line_len, fptr);
        buffer[strcspn(buffer, "\n")] = '\0';
        grid[i] = strdup(buffer);
        if (grid[i] == NULL) {
            perror("\nPanic! Couldn't allocate memory");
            return 1;
        }
    }

    // Part 1
    // ---
    long long *part1 = (long long *)malloc(sizeof(long long));
    *part1 = 0;

    beam(0, cols / 2, rows, cols, grid, part1);

    // Part 2
    // ---
    long long part2 = observe(0, cols / 2, rows, cols, grid, hash_table);

    fclose(fptr);
    printf("\n -- Part 1: %lld", *part1); // 1602 correct
    printf("\n -- Part 2: %lld", part2);  // 135656430050438 correct
    free(part1);
    return 0;
}
