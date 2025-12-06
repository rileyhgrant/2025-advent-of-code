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
    // char* input_path = "./input/day06_test.txt";
    fptr = fopen(input_path, "r");

    int line_chars;
    int rows = 0;
    int cols;
    char* token;
    while(fgets(buffer, line_len, fptr)) {
        cols = 0;
        buffer[strcspn(buffer, "\n")] = '\0';
        line_chars = strlen(buffer);
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

    // Part 2
    rewind(fptr);
    long long part2 = 0;

    char* array[rows];
    int i = 0;
    while(i < rows && fgets(buffer, line_len, fptr)) {
        buffer[strcspn(buffer, "\n")] = '\0';
        array[i] = strdup(buffer);
        if (array[i] == NULL) {
            perror("\nPanic! Couldn't allocate memory");
            return 1;
        }
        i++;
    }

    long long vals[rows - 1];
    int index = 0;
    for(int col = line_chars; col >= 0; col--) {
        long long curr_val = -1;
        for(int row = 0; row < rows; row++) {
            if (row == rows - 1 && curr_val > 0) {
                vals[index] = curr_val;
                index++;
            }
            char v = array[row][col];
            if (v == '+') {
                long long this_sum = 0;
                for(int m = 0; m < index; m++) {
                    this_sum = add(this_sum, vals[m]);
                }
                part2 += this_sum;
                index = 0;
            } else if (v == '*') { 
                long long this_prod = 1;
                for(int m = 0; m < index; m++) {
                    this_prod = multiply(this_prod, vals[m]);
                }
                part2 += this_prod;
                index = 0;
            } else if (v == ' ' || v == '\0') {
                // PASS no value 
            } else {
                long long digit = (long long)v - '0';
                if (curr_val == -1) {
                    curr_val = digit;
                } else {
                    curr_val = (curr_val * 10) + digit;
                }
            }
        }
    }

    fclose(fptr);

    printf("\n\nDay 02: \n-----");
    printf("\n  Part 1: %lld", part1);  // 5784380717354 correct
    printf("\n  Part 2: %lld", part2);  // 7996218225744 correct
    printf("\n");

    return 0;
}

