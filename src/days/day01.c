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

    int parttwo = 0;

    int spins = 0;
    int remain = 0;

    int dial = 100;

    while (fgets(buff, size, fptr)) {
        char dir = buff[0];
        int num = atoi(buff + 1);

        spins = num / dial; 
        remain = num % dial; 

        parttwo = parttwo + spins;

        if (dir == 'L') {

            if (remain > curr && curr != 0) {
                parttwo = parttwo + 1;
            }

            curr = curr - num;

            if (curr < 0) {
                curr = curr % 100;
                if (curr != 0) {
                    curr = curr + 100;
                }
            }
            
        } else if (buff[0] == 'R') {

            if (remain > (100 - curr) && curr != 0) {
                parttwo = parttwo + 1;
            }

            curr = curr + num;

            if (curr > 99) {
                curr = curr % 100;
            }
        }

        if (curr == 0) {
            zeroes = zeroes + 1;
        }

    }

    fclose(fptr);

    printf("\n\nDay 01: \n-----");
    printf("\n  Part 1: %d", zeroes); // 1071 correct
    printf("\n  Part 2: %d\n", zeroes + parttwo); // 6700 correct

    return 0;
}
