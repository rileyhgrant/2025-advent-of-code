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

int compare_flat_pairs_by_start(const void *a, const void *b) {
    const long long *startA = (const long long *)a;
    const long long *startB = (const long long *)b;

    if (*startA > *startB) {
        return 1;
    }
    if (*startA < *startB) {
        return -1;
    }
    
    return 0;
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

    // Part 1
    // ---
    long long part1 = 0;
    while(fgets(buffer, line_len, fptr)) {
        buffer[strcspn(buffer, "\n")] = '\0';
        long long ingredient = atoll(buffer);

        if(is_valid_ingredient(ingredient, array_len, ranges)) {
            part1++;
        }
    }

    // Part 2 
    // ---
    long long part2 = 0;
    while(true) {
        size_t element_size = sizeof(long long) * 2;
        qsort(ranges, array_len / 2, element_size, compare_flat_pairs_by_start);

        bool shrunk = false;
        for(int i = 0; i < array_len; i+=2) {
            long long first = ranges[i];
            long long second = ranges[i + 1];

            if (first == -1 && second == -1) {
                // pass
            } else {
                for(int j = 0; j < i; j+=2) {
                    long long first2 = ranges[j];
                    long long second2 = ranges[j + 1];

                    if (first2 == -1 && second2 == -1) {
                        // pass
                    } else {
                        if(first >= first2 && first <= second2 + 1) {
                            if (second >= second2) {
                                ranges[j + 1] = second;
                            }
                            ranges[i] = -1;
                            ranges[i + 1] = -1;
                            shrunk = true;
                        } else if (second >= first2 - 1 && second <= second2) {
                            if (first <= first2) {
                                ranges[j] = first;
                            }
                            ranges[i] = -1;
                            ranges[i + 1] = -1;
                            shrunk = true;
                        }
                    }
                }
            }
        }

        if (!shrunk) {
            break;
        }
    }

    for(int i = 0; i < array_len; i+=2) {
        long long first = ranges[i];
        long long second = ranges[i + 1];

        if (first == -1 && second == -1) {
            // pass
        } else {
            long long to_add = (second - first) + 1;
            part2 += to_add;
        }

    }


    fclose(fptr);
    printf("\n -- Part 1: %lld", part1);  // 613 correct
    printf("\n -- Part 2: %lld", part2);  // 336495597913098 correct
    return 0;
}
