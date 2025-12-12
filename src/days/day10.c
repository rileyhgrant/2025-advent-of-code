#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define BUFFER_SIZE 256

void print_formatted_time(double seconds)
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

void print_binary(int n, int width)
{
    printf("0b");
    int start_idx = width - 1;

    for (int i = start_idx; i >= 0; i--) {
        unsigned int mask = 1U << i;
        if (n & mask) {
            printf("1");
        } else {
            printf("0");
        }
    }
}

int day10()
{
    struct timespec start, end;
    timespec_get(&start, TIME_UTC);

    char buffer[BUFFER_SIZE];

    FILE *fptr;

    char *input_path = "./input/day10.txt";
    fptr = fopen(input_path, "r");

    long long part1 = 0;

    while (fgets(buffer, BUFFER_SIZE, fptr)) {
        char *innerPtr;
        buffer[strcspn(buffer, "\n")] = '\0';

        // goal as binary
        char *goal = strdup(strtok_r(buffer, " ", &innerPtr));
        int b_goal = 0;
        int bit = 1;
        int goal_len = strlen(goal) - 2;
        for (int i = goal_len; i > 0; i--) {
            if (goal[i] == '#') {
                b_goal += bit;
            }
            bit = bit * 2;
        }

        // buttons as binary
        int num_buttons = 0;
        int b_buttons[16] = {0};
        int b_button;
        char *nextToken;
        while ((nextToken = strtok_r(NULL, " ", &innerPtr)) != NULL) {
            b_button = 0;
            if (nextToken[0] == '(') {
                for (unsigned int i = 1; i < (strlen(nextToken) - 1); i += 2) {
                    int num = pow(2, (goal_len - 1) - atoi(&nextToken[i]));
                    b_button += num;
                }
                b_buttons[num_buttons] = b_button;
                num_buttons++;
            }
        }

        int queue[4096];
        queue[0] = 0;

        int idx = 0;
        int assigned = 0;

        int seen[1024];
        memset(seen, -1, sizeof(seen));
        seen[0] = 0;

        int xor;
        bool found = false;

        int result = 0;

        while (!found && idx <= assigned) {
            int current = queue[idx];
            int current_depth = seen[current];

            int new_depth = current_depth + 1;
            for (int i = 0; i < num_buttons; i++) {
                int b_button = b_buttons[i];
                xor = current ^ b_button;

                if (xor == b_goal) {
                    found = true;
                    result = new_depth;
                    break;
                }

                if (seen[xor] == -1) {
                    seen[xor] = new_depth;
                    assigned++;
                    queue[assigned] = xor;
                }
            }
            idx++;
        }

        part1 += result;
    }

    fclose(fptr);

    timespec_get(&end, TIME_UTC);
    long long seconds = end.tv_sec - start.tv_sec;
    long long nanoseconds = end.tv_nsec - start.tv_nsec;
    double elapsed_s = ((seconds * 1000) + (nanoseconds / 1.0e6)) / 1000.0;

    printf("\n -- Part 1 (");
    print_formatted_time(elapsed_s);
    printf("): %lld", part1); // 419 correct

    printf("\n -- Part 2 (");
    print_formatted_time(elapsed_s);
    printf("): %lld", -1LL);

    return 0;
}
