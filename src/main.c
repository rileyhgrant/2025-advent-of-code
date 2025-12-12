#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "day01.h"
#include "day02.h"
#include "day03.h"
#include "day04.h"
#include "day05.h"
#include "day06.h"
#include "day07.h"
#include "day08.h"
#include "day09.h"
#include "day10.h"

#define TOTAL_DAYS 12

void run_day(int day)
{
    printf("\n\n=== Day %02d ===", day);
    switch (day) {
    case 1:
        day01();
        break;
    case 2:
        day02();
        break;
    case 3:
        day03();
        break;
    case 4:
        day04();
        break;
    case 5:
        day05();
        break;
    case 6:
        day06();
        break;
    case 7:
        day07();
        break;
    case 8:
        day08();
        break;
    case 9:
        day09();
        break;
    case 10:
        day10();
        break;
    default:
        printf("\n -- Day %d not yet implemented", day);
        break;
    }
}

// Run with make run day=<DAY>
// e.g.:
//    `make run day=3`
int main(int argc, char **argv)
{
    printf("\n\n====================");
    printf("\nAdvent of Code 2025!");

    if (argc < 2) {
        printf("Usage: make run day=<NUMBER | all>\n");
        return 1;
    }

    char *day = argv[1];
    if (strcmp(day, "all") == 0) {
        for (int i = 1; i <= TOTAL_DAYS; i++) {
            run_day(i);
        }
    } else {
        int day_int = atoi(day);
        run_day(day_int);
    }
    printf("\n\n");

    return 0;
}
