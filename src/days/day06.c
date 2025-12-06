#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
FILE *fptr;


long long add(long long a, long long b) {
    return a + b;
}

long long multiply(long long a, long long b) {
    return a * b;
}

int day06() {
    int line_len = 4000;
    char buffer[line_len];

    char* input_path = "./input/day06.txt";
    fptr = fopen(input_path, "r");

    int rows = 0;
    int cols;
    char* token;
    while(fgets(buffer, line_len, fptr)) {
        cols = 0;
        buffer[strcspn(buffer, "\n")] = '\0';

        char* innerPtr;
        token = strtok_r(buffer, " ", &innerPtr);
        while(token != NULL) {
            token = strtok_r(NULL, " ", &innerPtr);
            cols++;
        }
        rows++;
    }

    rewind(fptr);
    long long grid[rows][cols];

    for(int i = 0; i < rows; i++) {
        fgets(buffer, line_len, fptr);
        buffer[strcspn(buffer, "\n")] = '\0';

        char* innerPtr2;
        token = strtok_r(buffer, " ", &innerPtr2);
        int j = 0;
        while(token != NULL) {
            if (*token == '*') {
                grid[i][j] = -1;
            } else if (*token == '+') {
                grid[i][j] = -2;
            } else {
                grid[i][j] = atoll(token);
            }

            j++;
            token = strtok_r(NULL, " ", &innerPtr2);
        }
    }


    // Part 1
    // ---
    long long part1 = 0;
  
    typedef long long (*Operation)(long long, long long);
    Operation oper;

    for(int j = 0; j < cols; j++) {
        long long curr;  
        long long op = grid[rows - 1][j];
        if (op == -1) {
            curr = 1;
            oper = multiply;
        } else if (op == -2) {
            curr = 0;
            oper = add;
        } else {
            return 1;
        }

        for(int i = 0; i < rows - 1; i++) {
            curr = oper(curr, grid[i][j]);
        }

        part1 += curr;
    }



    fclose(fptr);

    printf("\n\nDay 02: \n-----");
    printf("\n  Part 1: %lld", part1);  // 
    printf("\n  Part 2: %lld", -1LL); 
    printf("\n");

    return 0;
}



