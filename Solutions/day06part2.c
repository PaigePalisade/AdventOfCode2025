#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INPUT_FILE "input.txt"

int main() {
    FILE* f = fopen(INPUT_FILE, "r");

    long sum = 0;
    
    char lines[6][4000];

    int r = 0;

    while (!feof(f)) {
        fgets(lines[r], sizeof(lines[r]), f);
        r ++;
    }

    // this program expects no trailing newline, remove it from input file
    int numRows = r-1;

    // fgets includes the \n character
    int len = strlen(lines[0])-1;

    char operator;

    long subtotal = 0;
    for (int c = 0; c < len; c++) {
        if (lines[numRows][c] != ' ') {
            operator = lines[numRows][c];
            if (operator == '*') {
                subtotal = 1;
            }
            if (operator == '+') {
                subtotal = 0;
            }
        }
        // the col before the next operator is always blank, do not treat it as zeros
        if (c != len-1 && lines[numRows][c+1] != ' ') {
            sum += subtotal;
            printf("%ld\n", subtotal);
            continue;
        }
        // go row by row, and to construct the number digit by digit, ignoring spaces
        long number = 0;
        for (int r = 0; r < numRows; r++) {
            if (lines[r][c] != ' ') {
                number *= 10;
                number += lines[r][c] - '0';
            }
        }
        if (operator == '*') {
            subtotal *= number;
        }
        if (operator == '+') {
            subtotal += number;
        }
    }

    // our for loop doesn't handle the last col
    sum += subtotal;
    printf("%ld\n", subtotal);


    printf("\n%ld\n", sum);

    return 0;
}