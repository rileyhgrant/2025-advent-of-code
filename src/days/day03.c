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

    long long part2 = 0;

    while (fgets(buffer, line_size, fptr)) {
        int curr_highest = 0;

        buffer[strcspn(buffer, "\n")] = '\0';
        int line_length = strlen(buffer);

        // Part 1
        // ---
        for(int i = 0; i < line_length; i++) {
            for (int j = i + 1; j < line_length; j++) {
                double_digit = create_double_digit(buffer[i], buffer[j]);
                if (double_digit > curr_highest) {
                    curr_highest = double_digit;
                }
            }
        }
        part1 += curr_highest;

        // Part 2 
        // ---
        long long curr_number = 0;
        int window = line_length - 11;
        int index = 0;
        int offset;

        while (curr_number <= 99999999999) {
            int highest_digit = 0;

            for(int k = 0; k < window; k++) {
                int digit = buffer[index + k] - '0';
                if (digit > highest_digit) {
                    highest_digit = digit;
                    offset = k;
                }
            }
            curr_number = (curr_number * 10) + highest_digit;
            window -= offset;
            index += offset + 1;
        }

        part2 += curr_number;

    }

    fclose(fptr);
    printf("\n -- Part 1: %lld", part1); // 17359 correct 
    printf("\n -- Part 2: %lld", part2); // 172787336861064 correct
    return 0;
}
