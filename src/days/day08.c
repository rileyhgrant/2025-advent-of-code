#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
FILE *fptr;


#define MAX_ENTRIES 1000 * 1000

typedef struct {
    int key;
    char* value;
} KeyValuePair;

int compare_data_rows(const void *a, const void *b) {
    const KeyValuePair *oA = (const KeyValuePair *)a;
    const KeyValuePair *oB = (const KeyValuePair *)b;

    if (oA->key > oB->key) {
        return 1;
    }
    if (oA->key < oB->key) {
        return -1;
    }
    
    return 0;
}

int compare_int(const void* a, const void* b) {
    int ia = * ((int*)a);
    int ib = * ((int*)b);

    if ( ia == ib ) return 0;
    else if ( ia < ib ) return -1;
    else return 1;
}

int get_3d_distance(int x1, int x2, int y1, int y2, int z1, int z2) {
    float inner = pow((x1 - x2), 2) + pow((y1 - y2), 2) + pow((z1 - z2), 2);
    float val = sqrt(inner);
    return val;
}

static KeyValuePair data_table[MAX_ENTRIES];

int populate_data_table(int rows, int cols, int grid[rows][cols]) {
    int x1, y1, z1;
    int x2, y2, z2;

    int k = 0;

    for(int i = 0; i < rows; i++) {
        x1 = grid[i][0];
        y1 = grid[i][1];
        z1 = grid[i][2];

        for(int j = 0; j < rows; j++) {
            if(j != i) {
                x2 = grid[j][0];
                y2 = grid[j][1];
                z2 = grid[j][2];

                int distance = get_3d_distance(x1, x2, y1, y2, z1, z2);

                int required_size = snprintf(NULL, 0, "%d,%d,%d-%d,%d,%d", x1, y1, z1, x2, y2, z2);
                char *val = (char *)malloc(required_size + 1);
                if (val != NULL) {
                    snprintf(val, required_size + 1, "%d,%d,%d-%d,%d,%d", x1, y1, z1, x2, y2, z2);
                } else {
                    fprintf(stderr, "Memory allocation failed!\n");
                }

                data_table[k] = (KeyValuePair){distance, val};
                k++;
            }
        }
    }
    return k;
}


int day08() {
    int line_len = 100;
    char buffer[line_len];

    char* input_path = "./input/day08.txt";
    int iters = 1000;
    
    fptr = fopen(input_path, "r");

    int rows = 0;
    while(fgets(buffer, line_len, fptr)) {
        buffer[strcspn(buffer, "\n")] = '\0';
        rows++;
    }

    rewind(fptr);

    int grid[rows][3];
    char* circuits[rows];
    for(int i = 0; i < rows; i++) {
        char *innerPtr;
        fgets(buffer, line_len, fptr);
        buffer[strcspn(buffer, "\n")] = '\0';

        circuits[i] = strdup(buffer); 

        int first = atoi(strtok_r(buffer, ",", &innerPtr));
        int second = atoi(strtok_r(NULL, ",", &innerPtr));
        int third = atoi(strtok_r(NULL, ",", &innerPtr));
        grid[i][0] = first;
        grid[i][1] = second;
        grid[i][2] = third;
    }

    int size = populate_data_table(rows, 3, grid);
    size_t element_size = sizeof(KeyValuePair);
    qsort(data_table, size, element_size, compare_data_rows);

    int k = 0;
    long long part1;

    int num_dashes = 0;
    long long part2;

    while(true) {
        if(k == iters * 2) {
            int nums[4];
            nums[0] = 1;
            nums[1] = 1;
            nums[2] = 1;
            nums[3] = 1;

            for(int i = 0; i < rows; i++) {
                int count = 1;
                for(int n = 0; circuits[i][n] != '\0'; n++) {
                    if(circuits[i][n] == '&') {
                        count++;
                    }
                }
                nums[0] = count;
                qsort(nums, 4, sizeof(int), compare_int); 
            }

            part1 = (long long)(nums[1] * nums[2] * nums[3]);
        }


        KeyValuePair kvp = data_table[k];

        char* innerPtr2;
        char* first = strtok_r(kvp.value, "-", &innerPtr2);
        char* second = strtok_r(NULL, "-", &innerPtr2);

        int first_in;
        int second_in;

        for(int i = 0; i < rows; i++) {
            char* innerPtr3;

            char* circuitCopy = strdup(circuits[i]);

            char* node = strtok_r(circuitCopy, "&", &innerPtr3);
            while (node != NULL) {
                if(!strcmp(first, node)) {
                    first_in = i;
                }
                if(!strcmp(second, node)) {
                    second_in = i;
                }
                node = strtok_r(NULL, "&", &innerPtr3);
            }
        }

        if (first_in != second_in) {
            char* first_merge = circuits[first_in];
            char* second_merge = circuits[second_in];
            size_t total_len = strlen(first_merge) + strlen("&") + strlen(second_merge) + 1;

            char *new_first = (char *)malloc(total_len);
            if (new_first == NULL) {
                perror("Panic!");
                return 1; 
            }
            strcpy(new_first, first_merge);
            strcat(new_first, "&");
            strcat(new_first, second_merge);

            circuits[first_in] = new_first;
            circuits[second_in] = "-";
            num_dashes++;
        }

        if (num_dashes == rows - 1) {
            char* firstPtr;
            char* secondPtr;
            long long firstx = atoll(strtok_r(first, ",", &firstPtr));
            long long secondx = atoll(strtok_r(second, ",", &secondPtr));

            part2 = firstx * secondx;
            break;
        }

        k++;
    }

    fclose(fptr);

    printf("\n\nDay 08: \n-----");
    printf("\n  Part 1: %lld", part1); // 175500 - correct
    printf("\n  Part 2: %lld", part2); // 6934702555 - correct 
    printf("\n");

    return 0;
}

