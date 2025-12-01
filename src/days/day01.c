#include <stdio.h>
#include <stdlib.h>
FILE *fptr;

int day01() 
{
    int size = 30;
    char buff[size];

    fptr = fopen("./input/day01.txt", "r");

    int zeroes = 0;
    int curr = 50;

    while (fgets(buff, size, fptr)) {
        char dir = buff[0];
        int num = atoi(buff + 1);

        if (dir == 'L') {
            curr = curr - num;
            if (curr < 0) {
                curr = curr % 100;
                curr = curr + 100;
            }
            printf("\nRotated L%d to %d", num, curr);
        } else if (buff[0] == 'R') {
            curr = curr + num;
            if (curr > 99) {
                curr = curr % 100;
            }
            printf("\nRotated R%d to %d", num, curr);
        }

        if (curr == 0 || curr == 100) {
            printf("  <-- incrementing!");
            zeroes = zeroes + 1;
        }

    }

    fclose(fptr);

    printf("\n\nDay 01: \n-----");
    printf("\n  Part 1: %d", zeroes); // 1071 correct

    return 0;
}
