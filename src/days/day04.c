#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
FILE *fptr;


void print_grid(int rows, int cols, char grid[rows][cols]) {
    printf("\n");
    for(int i = 0; i < rows; i++) {
        printf("\n");
        for(int j = 0; j < cols; j++) {
            printf("%c", grid[i][j]);
        }
    }
}

bool can_be_moved(int rows, int cols, char grid[rows][cols], int i, int j) {
    if (grid[i][j] == '_' || grid[i][j] == '.') {
        return false;
    } 

    int count = 0;
    int r;
    int c;
    char ch;
    for(int m = -1; m < 2; m++) {
        for(int n = -1; n < 2; n++) {
            r = i - m;
            c = j - n;
            if(m == 0 && n == 0) {
                // pass
            } else {
                ch = grid[r][c];
                if(ch == '@') {
                    count++;
                }
            }
        }
    }

    return count < 4;
}


int day04() {
    int line_size = 500;
    char buffer[line_size];

    char* input_path = "./input/day04.txt";

    fptr = fopen(input_path, "r");

    int rows = 0;
    int cols = 0;
    int border = 1;
    char border_char = '_';

    while(fgets(buffer, line_size, fptr)) {
        buffer[strcspn(buffer, "\n")] = '\0';
        cols = strlen(buffer);
        rows += 1;
    }

    rows = rows + (border * 2);
    cols = cols + (border * 2);

    char grid[rows][cols];

    rewind(fptr);
    for(int i = 0; i < rows; i++) {
        if(!(i < border || i >= rows - border)) {
            fgets(buffer, line_size, fptr);
        }
        int k = 0;

        for(int j = 0; j < cols; j++) {
            if(i < border || i >= rows - border) {
                grid[i][j] = border_char;
            } else if (j < border || j >= cols - border) {
                grid[i][j] = border_char;
            } else {
                grid[i][j] = buffer[k];
                k++;
            }
        }
    }

    long long part1 = 0;
    for(int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (can_be_moved(rows, cols, grid, i, j)) {
                part1 += 1;
            }
        }
    }

    printf("\n\nDay 04: \n-----");
    printf("\n  Part 1: %lld", part1); // 1502 correct 
    // printf("\n  Part 2: %lld", (long long)-1);
    printf("\n");

    return 0;
}



