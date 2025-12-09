#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
FILE *fptr;

#define MAX_SEEN 10000

int orderOfMagnitude(long long num) {
    return (int)floor(log10(num)) + 1;
}

long long replicate(int targetMag, long long num) {
    long long toReturn = num;
    int originalMag = orderOfMagnitude(num);

    if (orderOfMagnitude(toReturn) >= targetMag) {
        return 0;
    }
    
    while(orderOfMagnitude(toReturn) < targetMag) {
        toReturn = (toReturn * (int)pow(10, originalMag)) + num;
    }
    
    return toReturn;
}

bool has_been_seen(long long val, long long seen_array[], int seen_count) {
    for (int i = 0; i < seen_count; i++) {
        if (seen_array[i] == val) {
            return true;
        }
    }
    return false;
}


int day02() {
    int line_size = 500;
    char buffer[line_size];

    char* input_path = "./input/day02.txt";
    fptr = fopen(input_path, "r");

    fgets(buffer, line_size, fptr);

    long long solution = 0;
    long long solution2 = 0;

    char *outerPtr;
    char *innerPtr;
    char* idRange = strtok_r(buffer, ",", &outerPtr);


    long long seen[MAX_SEEN];

    while(idRange != NULL) {
        long long first_int = atoll(strtok_r(idRange, "-", &innerPtr));
        long long second_int = atoll(strtok_r(NULL, "-", &innerPtr));

        int firstMag = (int)floor(log10(first_int)) + 1;
        int firstHalfLen = (firstMag / 2);
        int remove = firstMag - firstHalfLen;


        long long check = first_int / (int)pow(10, remove);
        int checkMag = (int)floor(log10(check)) + 1;
        long long toCheck = check * (int)pow(10, checkMag) + check;

        // Part 1
        // ---
        while (toCheck <= second_int) {
            if (toCheck >= first_int && toCheck <= second_int) {
                solution += toCheck;
            }

            check = check + 1;
            checkMag = (int)floor(log10(check)) + 1;
            toCheck = check * (int)pow(10, checkMag) + check;
        }


        // Part 2
        // ---
        memset(seen, 0, sizeof(seen));
        int seen_count = 0;

        int secondMag = (int)floor(log10(second_int)) + 1;

        long long toRepeat = 1;
        long long replicated = replicate(firstMag, toRepeat);
        while(orderOfMagnitude(toRepeat) <= (secondMag / 2)) {
            if (has_been_seen(replicated, seen, seen_count)) {
                // pass
            } else if (replicated >= first_int && replicated <= second_int) {
                seen[seen_count] = replicated;
                seen_count += 1;
                solution2 += replicated; 
            }
            toRepeat += 1;
            replicated = replicate(firstMag, toRepeat);
        }


        long long toRepeat2 = 1;
        long long replicated2 = replicate(secondMag, toRepeat2);
        while(orderOfMagnitude(toRepeat2) <= (secondMag / 2)) {
            if (has_been_seen(replicated2, seen, seen_count)) {
                // pass
            } else if (replicated2 >= first_int && replicated2 <= second_int) {
                seen[seen_count] = replicated2;
                seen_count += 1;
                solution2 += replicated2; 
            }
            toRepeat2 += 1;
            replicated2 = replicate(secondMag, toRepeat2);
        }

        idRange = strtok_r(NULL, ",", &outerPtr);
    }

    fclose(fptr);
    printf("\n -- Part 1: %lld", solution);  // 19128774598 correct
    printf("\n -- Part 2: %lld", solution2); // 21932258645 correct
    return 0;
}
