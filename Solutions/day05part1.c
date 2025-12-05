#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INPUT_FILE "input.txt"

typedef struct {
    long low;
    long high;
} Range;

Range ranges[300];
int numRanges = 0;

int isFresh(long n) {
    for (int i = 0; i < numRanges; i++) {
        if (n >= ranges[i].low && n <= ranges[i].high) {
            return 1;
        }
    }
    return 0;
}

int main() {
    FILE* f = fopen(INPUT_FILE, "r");

    int count = 0;
    
    char nextChar = '0';

    while (nextChar != '\n') {
        long low, high;
        fscanf(f, "%ld-%ld", &low, &high);
        ranges[numRanges] = (Range){low, high};
        numRanges ++;
        nextChar = fgetc(f);
        nextChar = fgetc(f);
        ungetc(nextChar, f);
    }

    while (!feof(f)) {
        long n;
        fscanf(f, "%ld ", &n);
        if (isFresh(n)) {
            printf("%ld\n", n);
            count ++;
        }
    }

    printf("\n%d\n", count);

    return 0;
}