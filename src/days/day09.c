#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
FILE *fptr;


bool line_intersects_box(int blx, int bly, int bgx, int bgy, int lx1, int ly1, int lx2, int ly2) {
    int llx = lx1 < lx2 ? lx1 : lx2;
    int lgx = lx1 >= lx2 ? lx1 : lx2;
    int lly = ly1 < ly2 ? ly1 : ly2;
    int lgy = ly1 >= ly2 ? ly1 : ly2;

    if (llx == lgx) {
        if (llx > blx && llx < bgx) { 
             if (lly < bgy && lgy > bly) {
                return true;
            }
        }
    } 
    else if (lly == lgy) {
        if (lly > bly && lly < bgy) { 
            if (llx < bgx && lgx > blx) {
                return true;
            }
        }
    }

    return false;
}


bool ray_crosses_line(int cx, int cy, int lx1, int ly1, int lx2, int ly2) {
    if (ly1 - ly2 == 0) {
        return false;
    } 

    int lly = ly1 < ly2 ? ly1 : ly2;
    int lgy = ly1 >= ly2 ? ly1 : ly2;

    bool line_is_to_right = cx < lx1;
    bool line_would_be_crossed_y = cy >= lly && cy <= lgy;
    return (line_is_to_right && line_would_be_crossed_y);
}



int day09() {
    int line_len = 30;
    char buffer[line_len];
    
    char* input_path = "./input/day09.txt";
    fptr = fopen(input_path, "r");

    int rows = 0;
    int cols;
    int array[500][2];

    while(fgets(buffer, line_len, fptr)) {
        char* innerPtr;
        buffer[strcspn(buffer, "\n")] = '\0';
        int first = atoi(strtok_r(buffer, ",", &innerPtr));
        int second = atoi(strtok_r(NULL, ",", &innerPtr));
        array[rows][0] = first;
        array[rows][1] = second;
        cols = strlen(buffer);
        rows++;
    }

    int lines[rows][4];
    for(int i = 0; i < rows; i++) {
        int ax = array[i][0];
        int ay = array[i][1];

        int bx, by;
        if (i != rows - 1) {
            bx = array[i + 1][0];
            by = array[i + 1][1];
        } else {
            bx = array[0][0];
            by = array[0][1];
        }

        lines[i][0] = ax;
        lines[i][1] = ay;
        lines[i][2] = bx;
        lines[i][3] = by;
    }

    long long part1 = 0;
    long long part2 = 0;
    for(int i = 0; i < rows; i++) {
        int ax = array[i][0];
        int ay = array[i][1];

        for(int j = 0; j < rows; j++) {
            if(i != j) {
                int bx = array[j][0];
                int by = array[j][1];

                long long x_delta = (long long)(abs(ax - bx) + 1);
                long long y_delta = (long long)(abs(ay - by) + 1);
                long long result = x_delta * y_delta; 

                if (result > part1) {
                    part1 = result;
                }

                if (result > part2) {
                    int k = 0;
                    bool no_intersects = 1;

                    int blx = ax < bx ? ax : bx;
                    int bly = ay < by ? ay : by;
                    int bgx = ax >= bx ? ax : bx;
                    int bgy = ay >= by ? ay : by;

                    int cx = ((bgx - blx) / 2) + blx;
                    int cy = ((bgy - bly) / 2) + bly;

                    int cross_count = 0;
                    while(k < rows && no_intersects == true) {
                        int lx1 = lines[k][0];
                        int ly1 = lines[k][1];
                        int lx2 = lines[k][2];
                        int ly2 = lines[k][3];

                        if (line_intersects_box(blx, bly, bgx, bgy, lx1, ly1, lx2, ly2)) {
                            no_intersects = false;
                        }

                        if (ray_crosses_line(cx, cy, lx1, ly1, lx2, ly2)) {
                            cross_count++;
                        }
                        k++;
                    }

                    bool inside_shape = cross_count % 2 == 1;
                    if (no_intersects == true && inside_shape) {
                        part2 = result;
                    }
                }
            }
        }
    }



    fclose(fptr);

    printf("\n\nDay 09: \n-----");
    printf("\n  Part 1: %lld", part1); // 4774877510 correct
    printf("\n  Part 2: %lld", part2); // 1560475800 correct 
    printf("\n");

    return 0;
}
