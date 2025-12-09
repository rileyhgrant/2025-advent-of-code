#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
FILE *fptr;

int day09() {
    int line_len = 30;
    char buffer[line_len];
    
    char* input_path = "./input/day09.txt";
    fptr = fopen(input_path, "r");

    int rows = 0;
    int array[500][2];

    while(fgets(buffer, line_len, fptr)) {
        char* innerPtr;
        buffer[strcspn(buffer, "\n")] = '\0';
        int first = atoi(strtok_r(buffer, ",", &innerPtr));
        int second = atoi(strtok_r(NULL, ",", &innerPtr));
        array[rows][0] = first;
        array[rows][1] = second;
        rows++;
    }

    long long part1 = 0;
    for(int i = 0; i < rows; i++) {
        int ax = array[i][0];
        int ay = array[i][1];

        for(int j = 0; j < rows; j++) {
            int bx = array[j][0];
            int by = array[j][1];

            long long x_delta = (long long)(abs(ax - bx) + 1);
            long long y_delta = (long long)(abs(ay - by) + 1);

            long long result = x_delta * y_delta; 

            if (result > part1) {
                part1 = result;
            }
        }
    }

    fclose(fptr);

    printf("\n\nDay 09: \n-----");
    printf("\n  Part 1: %lld", part1);
    printf("\n  Part 2: %lld", -1LL);
    printf("\n");

    return 0;
}
