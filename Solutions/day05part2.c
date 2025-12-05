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

void removeRange(int i) {
    numRanges --;
    for (int j = i; j < numRanges; j++) {
        ranges[j] = ranges[j+1];
    }
}

int main() {
    FILE* f = fopen(INPUT_FILE, "r");

    long count = 0;
    
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

    // merge ranges
    for (int i = 0; i < numRanges; i++) {
        // this for loop starts back at i+1 every time an overlap is found
        // so that previously checked ranges are checked in context of the bigger range
        for (int j = i+1; j < numRanges; j++) {
            long low1 = ranges[i].low;
            long high1 = ranges[i].high;
            long low2 = ranges[j].low;
            long high2 = ranges[j].high;
            // range 2 is a subrange of range 1
            if (low2 >= low1 && low2 <= high1 && high2 >= low1 && high2 <= high1) {
                removeRange(j);
                j = i;
            }
            // range 1 is a subrange of range 2
            else if (low1 >= low2 && low1 <= high2 && high1 >= low2 && high1 <= high2) {
                ranges[i].low = low2;
                ranges[i].high = high2;
                removeRange(j);
                j = i;
            }
            // range 2 overlaps and has a higher high than range 1
            else if (low2 >= low1 && low2 <= high1 && high2 > high1) {
                ranges[i].high = high2;
                removeRange(j);
                j = i;
            }
            // range 2 overlaps and has a lower low than range 1
            else if (high2 >= low1 && high2 <= high1 && low2 < low1) {
                ranges[i].low = low2;
                removeRange(j);
                j = i;
            }
        }
    }
    for (int i = 0; i < numRanges; i++) {
        printf("%ld-%ld\n", ranges[i].low, ranges[i].high);
        count += ranges[i].high - ranges[i].low + 1;
    }

    printf("\n%ld\n", count);

    return 0;
}