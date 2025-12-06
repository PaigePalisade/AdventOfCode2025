#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INPUT_FILE "input.txt"

int main() {
    FILE* f = fopen(INPUT_FILE, "r");

    long sum = 0;
    
    int numbers[5][6000];

    int row = 0;
    int col = 0;

    int numCols, numRows;

    // read numbers into big table
    char nextChar = '0';
    while (!(nextChar == '*' || nextChar == '+')) {
        fscanf(f, "%d", &numbers[row][col]);
        do {
            nextChar = fgetc(f);
        } while (nextChar == ' ');
        // when we reach the end of the line,
        // we record the number of columns and rows before we reset the position
        if (nextChar == '\n') {
            numCols = col + 1;
            numRows = row + 1;
            col = 0;
            row ++;
            nextChar = fgetc(f);
            ungetc(nextChar, f);
        } else {
            col ++;
            ungetc(nextChar, f);
        }
    }

    // scan the operations, and add/multiply the numbers in the table
    for (int c = 0; c < numCols; c++) {
        char operation;
        fscanf(f, "%c ", &operation);
        if (operation == '+') {
            long subtotal = 0;
            for (int r = 0; r < numRows; r++) {
                subtotal += numbers[r][c];
            }
            printf("%ld\n", subtotal);
            sum += subtotal;
        }
        if (operation == '*') {
            long subtotal = 1;
            for (int r = 0; r < numRows; r++) {
                subtotal *= numbers[r][c];
            }
            printf("%ld\n", subtotal);
            sum += subtotal;
        }
    }

    printf("\n%ld\n", sum);

    return 0;
}