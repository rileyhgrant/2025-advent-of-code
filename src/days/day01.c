#include <stdio.h>
#include <stdlib.h>
FILE *fptr;


int compare( const void* a, const void* b) {
    int int_a = * ( (int*) a );
    int int_b = * ( (int*) b );

    if ( int_a == int_b ) return 0;
    else if ( int_a < int_b ) return -1;
    else return 1;
}


int day01() 
{
    printf("\nAdvent of Code 2022!\n==========");
    printf("\n\nDay 01: \n-----");

    fptr = fopen("./input/day01/input.txt", "r");

    int size = 200;
    char buff[size];

    int curr;
    curr = 0;

    int max[4];
    max[0] = 0;
    max[1] = 0;
    max[2] = 0;
    max[3] = 0;

    while (fgets(buff, size, fptr)) {
        if (buff[0] == '\n') {
            max[0] = curr;
            qsort(max, 4, sizeof(int), compare);
            max[0] = 0;
            curr = 0;
        } else {
            int line = atoi(buff);
            curr += line;
        }
    };

    fclose(fptr);

    printf("\n  Part 1: %d", max[3]);

    int part_2;
    part_2 = max[1] + max[2] + max[3];
    printf("\n  Part 2: %d", part_2);

    printf("\n\n");
    return 0;
}
