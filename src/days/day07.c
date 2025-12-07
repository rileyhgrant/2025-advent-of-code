#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
FILE *fptr;


void print_gr(int rows, int cols, char* grid[rows]) {
    printf("\n");
    for(int i = 0; i < rows; i++) {
        printf("\n%s", grid[i]);
    }
}

void beam(int row, int col, int rows, int cols, char* grid[rows], long long *part1) {
    if (row == rows - 1) return;
    char below = grid[row + 1][col];
    if(below == '.') {
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

int day07() {
    int line_len = 1000;
    char buffer[line_len];

    char* input_path = "./input/day07.txt";

    fptr = fopen(input_path, "r");

    int rows = 0;
    int cols;

    while(fgets(buffer, line_len, fptr)) {
        buffer[strcspn(buffer, "\n")] = '\0';
        cols = strlen(buffer);
        rows++;
    }

    rewind(fptr);
    char* grid[rows];
    for(int i = 0; i < rows; i++) {
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


    fclose(fptr);

    printf("\n\nDay 02: \n-----");
    printf("\n  Part 1: %lld", *part1); //1602 correct
    printf("\n  Part 2: %lld", -1LL);
    printf("\n");

    free(part1);
    
    return 0;
}

