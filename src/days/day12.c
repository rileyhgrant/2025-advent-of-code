#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define BUFFER_SIZE 256
#define MAX_NODES 2048

void print_formatted_time_12(double seconds)
{
    if (seconds >= 1.0) {
        printf("%.3fs", seconds);
    } else if (seconds >= 1e-3) {
        printf("%.3fms", seconds * 1e3);
    } else if (seconds >= 1e-6) {
        printf("%.0fus", seconds * 1e6);
    } else {
        printf("%.0fns", seconds * 1e9);
    }
}

int day12()
{
    struct timespec start, end;
    timespec_get(&start, TIME_UTC);

    char buffer[BUFFER_SIZE];
    FILE *fptr;
    char *input_path = "./input/day12.txt";
    fptr = fopen(input_path, "r");

    int present_areas[6];
    int curr_area;
    int count = 0;

    long long part1 = 0;

    while (fgets(buffer, BUFFER_SIZE, fptr)) {
        buffer[strcspn(buffer, "\n")] = '\0';

        if (buffer[1] == ':') {
            curr_area = 0;
            char curr_char;
            for (int i = 0; i < 3; i++) {
                fgets(buffer, BUFFER_SIZE, fptr);
                for (int j = 0; j < 3; j++) {
                    curr_char = buffer[j];
                    if (curr_char == '#') {
                        curr_area++;
                    }
                }
            }
            present_areas[count] = curr_area;
            count++;
        } else if (strlen(buffer) != 0) {
            char *innerPtr;

            char *area = strtok_r(buffer, ":", &innerPtr);
            char *areaPtr;
            int total_area = atoi(strtok_r(area, "x", &areaPtr));
            total_area = total_area * atoi(strtok_r(NULL, "x", &areaPtr));

            char *presents = strtok_r(NULL, ":", &innerPtr);
            int presents_array[6];
            char *presentsPtr;
            presents_array[0] = atoi(strtok_r(presents, " ", &presentsPtr));
            for (int k = 1; k < 6; k++) {
                presents_array[k] = atoi(strtok_r(NULL, " ", &presentsPtr));
            }

            int presents_area = 0;
            for (int m = 0; m < 6; m++) {
                int add_area = present_areas[m] * presents_array[m];
                presents_area += add_area;
            }

            if (presents_area < total_area) {
                part1++;
            }
        }
    }

    fclose(fptr);

    timespec_get(&end, TIME_UTC);
    long long p1_seconds = end.tv_sec - start.tv_sec;
    long long p1_nanoseconds = end.tv_nsec - start.tv_nsec;
    double p1_elapsed_s =
        ((p1_seconds * 1000) + (p1_nanoseconds / 1.0e6)) / 1000.0;

    printf("\n -- Part 1 (");
    print_formatted_time_12(p1_elapsed_s);
    printf("): %lld", part1);

    return 0;
}
