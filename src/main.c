#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "day01.h"


// Run with make run day=<DAY>
// e.g.:
//    `make run day=3`
int main(int argc, char **argv) {
    printf("\nAdvent of Code 2022!\n==========");

    printf("\n\n --- Debug ---");
    printf("\n - (  %d  )", argc);
    printf("\n - (  %s  )", argv[0]);
    printf("\n - (  %s  )\n\n", argv[1]);
   
    int day = atoi(argv[1]);

    switch(day) {
        case 1: day01(); break;
        default: printf("Day %d not found", day); break;
    }   
}
