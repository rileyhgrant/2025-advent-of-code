#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "day01.h"
#include "day02.h"
#include "day03.h"
#include "day04.h"
#include "day05.h"
#include "day06.h"
#include "day07.h"


// Run with make run day=<DAY>
// e.g.:
//    `make run day=3`
int main(int argc, char **argv) {
    printf("\nAdvent of Code 2025!\n==========");
   
    int day = atoi(argv[1]);

    switch(day) {
        case 1: day01(); break;
        case 2: day02(); break;
        case 3: day03(); break;
        case 4: day04(); break;
        case 5: day05(); break;
        case 6: day06(); break;
        case 7: day07(); break;
        default: printf("Day %d not found", day); break;
    }   
}
