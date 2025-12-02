#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
FILE *fptr;

int day02() {

    int line_size = 500;
    char buffer[line_size];

    char* input_path = "./input/day02.txt";
    fptr = fopen(input_path, "r");

    fgets(buffer, line_size, fptr);

    long long solution = 0;

    char *outerPtr;
    char *innerPtr;
    char* idRange = strtok_r(buffer, ",", &outerPtr);
    while(idRange != NULL) {

        long long first_int = atoll(strtok_r(idRange, "-", &innerPtr));
        long long second_int = atoll(strtok_r(NULL, "-", &innerPtr));

        int firstMag = (int)floor(log10(first_int)) + 1;
        int secondMag = (int)floor(log10(second_int)) + 1;

        int firstHalfLen = (firstMag / 2);
        int remove = firstMag - firstHalfLen;

        long long check = first_int / (int)pow(10, remove);
        int checkMag = (int)floor(log10(check)) + 1;
        long long toCheck = check * (int)pow(10, checkMag) + check;

        while (toCheck <= second_int) {
            if (toCheck >= first_int && toCheck <= second_int) {
                solution += toCheck;
            }

            check = check + 1;
            checkMag = (int)floor(log10(check)) + 1;
            toCheck = check * (int)pow(10, checkMag) + check;
        }

        idRange = strtok_r(NULL, ",", &outerPtr);
    }


    fclose(fptr);

    printf("\n\nDay 02: \n-----");
    printf("\n  Part 1: %lld", solution); // 19128774598 correct
    printf("\n");

    return 0;
}
