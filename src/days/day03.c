#include <stdio.h>
#include <stdlib.h>
#include <string.h>
FILE *fptr;


int create_double_digit(char first, char second) {
    int first_int = first - '0';
    int second_int = second - '0';
    int sum = first_int * 10 + second_int;
    return sum; 
}

int day03() {
    int line_size = 500;
    char buffer[line_size];

    char* input_path = "./input/day03.txt";
    fptr = fopen(input_path, "r");

    long long part1 = 0;
    int double_digit = 0;

    while (fgets(buffer, line_size, fptr)) {
        int curr_highest = 0;

        buffer[strcspn(buffer, "\n")] = '\0';
        int line_length = strlen(buffer);

        for(int i = 0; i < line_length; i++) {
            for (int j = i + 1; j < line_length; j++) {
                double_digit = create_double_digit(buffer[i], buffer[j]);
                if (double_digit > curr_highest) {
                    curr_highest = double_digit;
                }
            }
        }
        part1 += curr_highest;
    }

    printf("\n\nDay 03: \n-----");
    printf("\n  Part 1: %lld", part1); // 17359 correct 
    printf("\n  Part 2: %lld", (long long)0); // 21932258645 correct
    printf("\n");

    return 0;
}



