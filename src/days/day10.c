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

typedef struct {
    int current_b_value;
    int history_indices[16];
    int history_count;
    int last_index_pressed;
} Path;

typedef struct {
    int *button_indices;
    int button_count;
} ButtonCombination;

typedef struct {
    ButtonCombination *combos;
    int count;
    int least_button_presses_required;
} ButtonResult;

int compare_ints(const void *a, const void *b)
{
    return (*(int *)a - *(int *)b);
}

// Get all states that result in goal, in preparation to use this strategy:
//   https://www.reddit.com/r/adventofcode/comments/1pk87hl/2025_day_10_part_2_bifurcate_your_way_to_victory/
//   from reddit user: https://www.reddit.com/user/tenthmascot/
ButtonResult get_button_combinations(int b_target, int num_buttons,
                                     int b_button_array[16])
{
    Path *queue = malloc(4096 * sizeof(Path));
    queue[0] = (Path){
        .current_b_value = 0,
        .history_count = 0,
        .last_index_pressed = -1,
    };

    int idx = 0;
    int assigned = 0;

    ButtonCombination temp_results[1024];
    int num_found = 0;
    int least_button_pressed_required = 999;

    while (idx <= assigned) {

        Path current_path = queue[idx];
        idx++;

        if (current_path.current_b_value == b_target) {
            int *saved_indices =
                malloc(current_path.history_count * sizeof(int));
            memcpy(saved_indices, current_path.history_indices,
                   current_path.history_count * sizeof(int));

            temp_results[num_found].button_indices = saved_indices;
            temp_results[num_found].button_count = current_path.history_count;
            if (current_path.history_count < least_button_pressed_required) {
                least_button_pressed_required = current_path.history_count;
            }
            num_found++;
        } else {
            for (int i = current_path.last_index_pressed + 1; i < num_buttons;
                 i++) {
                int b_button = b_button_array[i];
                int xor_val = current_path.current_b_value ^ b_button;

                Path new_path = current_path;
                new_path.current_b_value = xor_val;

                new_path.history_count = current_path.history_count + 1;
                new_path.history_indices[new_path.history_count - 1] = i;
                new_path.last_index_pressed = i;

                assigned++;
                queue[assigned] = new_path;
            }
        }
    }

    ButtonResult result;
    result.count = num_found;
    result.combos = malloc(num_found * sizeof(ButtonCombination));
    for (int i = 0; i < num_found; i++) {
        result.combos[i] = temp_results[i];
    }
    result.least_button_presses_required = least_button_pressed_required;

    free(queue);

    return result;
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

        // Part 1
        // ---
        ButtonResult part1_result =
            get_button_combinations(b_goal, num_buttons, b_buttons);

        part1 += part1_result.least_button_presses_required;
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
