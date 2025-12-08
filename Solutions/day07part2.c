#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define INPUT_FILE "input.txt"

char grid[500][500];

int numLines = 0;

// timelines array caches values
// zero initializer is fine as this function will never return < 1
long timelines[500][500] = {0};
long getTimelines(int r, int c) {
    if (timelines[r][c] != 0) {
        return timelines[r][c];
    }
    if (r == numLines - 1) {
        timelines[r][c] = 1;
        return 1;
    }
    long res = 0;
    if (grid[r+1][c] == '.') {
        res = getTimelines(r+1,c);
    }
    if (grid[r+1][c] == '^') { 
        // col doesn't have to be bounds checked
        // as the input is designed so that beams never go off the sides
        res = getTimelines(r+1,c-1) + getTimelines(r+1,c+1);
    }
    timelines[r][c] = res;
    return res;
}

int main() {
    FILE* f = fopen(INPUT_FILE, "r");

    long count = 0;

    for (int i = 0; !feof(f); i++) {
        fscanf(f, "%s ", grid[i]);
        numLines = i + 1;
    }
    
    int len = strlen(grid[0]);

    // get start position
    int startCol = 0;
    for (int i = 0; i < len; i++) {
        if (grid[0][i] == 'S') {
            startCol = i;
        }
    }

    count = getTimelines(0, startCol);

    printf("\n%ld\n", count);

    return 0;
}