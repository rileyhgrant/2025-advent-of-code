#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
FILE *fptr;

bool is_valid_ingredient(long long ingredient, int array_size, long long array[array_size]) {
    for(int i = 0; i < array_size; i+=2) {
        long long first = array[i];
        long long second = array[i + 1];
        if (ingredient >= first && ingredient <= second) {
            return true;
        }
    }
    return false;
}

int day05() {
    int line_len = 500;
    char buffer[line_len];

    char* input_path = "./input/day05.txt";
    fptr = fopen(input_path, "r");

    int num_ranges = 0;

    while(fgets(buffer, line_len, fptr)) {
        if (buffer[0] == '\n') {
            break;
        }
        buffer[strcspn(buffer, "\n")] = '\0';
        num_ranges += 1;
    }

    int array_len = num_ranges * 2;
    long long ranges[array_len];
    int index = 0;
    rewind(fptr);
    char *innerPtr;
    while(fgets(buffer, line_len, fptr)) {
        if (buffer[0] == '\n') {
            break;
        }
        
        long long first = atoll(strtok_r(buffer, "-", &innerPtr));
        long long second = atoll(strtok_r(NULL, "-", &innerPtr));
        ranges[index] = first;
        ranges[index + 1 ] = second;
        index += 2;
    }

    long long part1 = 0;
    while(fgets(buffer, line_len, fptr)) {
        buffer[strcspn(buffer, "\n")] = '\0';
        long long ingredient = atoll(buffer);

        if(is_valid_ingredient(ingredient, array_len, ranges)) {
            part1++;
        }
    }

    fclose(fptr);

    printf("\n\nDay 02: \n-----");
    printf("\n  Part 1: %lld", part1);  // 613 correct
    // printf("\n  Part 2: %lld", (long long)-1); 
    printf("\n");

    return 0;
}
