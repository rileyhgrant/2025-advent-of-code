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
    printf("0b-");
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
        }

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

long long solve_day_10_part_2(int goal_len, int joltages[goal_len],
                              int num_buttons, int binary_buttons[num_buttons],
                              int array_buttons[num_buttons][goal_len])
{
    bool any_nonzero = false;
    bool any_negative = false;
    for (int r = 0; r < goal_len; r++) {
        if (joltages[r] != 0) {
            any_nonzero = true;
        }
        if (joltages[r] < 0) {
            any_negative = true;
        }
    }
    if (!any_nonzero) {
        return 0LL;
    }
    if (any_negative) {
        return 999999LL;
    }

    unsigned long long int joltage_as_odd_target = 0;
    for (int i = 0; i < goal_len; i++) {
        int partial = joltages[i] % 2 == 1 ? 1 : 0;
        joltage_as_odd_target = (joltage_as_odd_target << 1) + partial;
    }

    ButtonResult candidates = get_button_combinations(
        joltage_as_odd_target, num_buttons, binary_buttons);

    long long minimum = 999999LL;

    for (int m = 0; m < candidates.count; m++) {
        ButtonCombination this_combo = candidates.combos[m];
        int next_joltages[goal_len];
        memcpy(next_joltages, joltages, goal_len * sizeof(int));

        for (int n = 0; n < this_combo.button_count; n++) {
            int *array_button = array_buttons[this_combo.button_indices[n]];
            for (int o = 0; o < goal_len; o++) {
                next_joltages[o] = next_joltages[o] - array_button[o];
            }
        }

        for (int p = 0; p < goal_len; p++) {
            next_joltages[p] = next_joltages[p] / 2;
            if (next_joltages[p] != 0) {
                any_nonzero = true;
            }
        }

        long long recur_result =
            solve_day_10_part_2(goal_len, next_joltages, num_buttons,
                                binary_buttons, array_buttons);

        long long this_result = this_combo.button_count + (2 * recur_result);
        if (this_result < minimum) {
            minimum = this_result;
        }
    }

    return minimum;
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
    long long part2 = 0;

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

        // buttons as binary, and as array
        int num_buttons = 0;
        int b_buttons[16] = {0};
        int index_buttons[16][goal_len];

        int joltages[goal_len];

        char *next_token;
        while ((next_token = strtok_r(NULL, " ", &innerPtr)) != NULL) {
            for (int n = 0; n < goal_len; n++) {
                index_buttons[num_buttons][n] = 0;
            }

            int b_button = 0;
            if (next_token[0] == '(') {
                for (unsigned int i = 1; i < (strlen(next_token) - 1); i += 2) {
                    int this_num = atoi(&next_token[i]);
                    int b_num = pow(2, (goal_len - 1) - this_num);
                    b_button += b_num;
                    index_buttons[num_buttons][this_num] = 1;
                }

                b_buttons[num_buttons] = b_button;
                num_buttons++;
            }

            if (next_token[0] == '{') {
                char *joltagePtr;
                char *next_joltage = strtok_r(next_token + 1, ",", &joltagePtr);
                int joltage_count = 0;
                while (next_joltage != NULL) {
                    joltages[joltage_count] = atoi(next_joltage);
                    next_joltage = strtok_r(NULL, ",", &joltagePtr);
                    joltage_count++;
                }
            }
        }

        // Part 1
        // ---
        ButtonResult part1_result =
            get_button_combinations(b_goal, num_buttons, b_buttons);

        part1 += part1_result.least_button_presses_required;

        // Part 2
        // ---
        long long part2_result = solve_day_10_part_2(
            goal_len, joltages, num_buttons, b_buttons, index_buttons);
        part2 += part2_result;
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
    printf("): %lld", part2); // 18369 correct

    return 0;
}
