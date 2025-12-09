#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define INPUT_FILE "input.txt"

// abs uses ints, I use longs just in case
long absl(long a) {
    if (a < 0) {
        return -a;
    }
    return a;
}

typedef struct {
    long x, y;
} Tile;

int main() {
    FILE* f = fopen(INPUT_FILE, "r");

    long maxSize = 0;

    Tile tiles[500];

    int numTiles = 0;

    for (int i = 0; !feof(f); i++) {
        fscanf(f, "%ld,%ld ", &tiles[i].x, &tiles[i].y);
        numTiles ++;
    }

    for (int i = 0; i < numTiles; i++) {
        for (int j = 0; j < numTiles; j++) {
            long size = (absl(tiles[i].x-tiles[j].x)+1) * (absl(tiles[i].y-tiles[j].y)+1);
            if (size > maxSize) {
                maxSize = size;
            }
        }
    }

    printf("\n%ld\n", maxSize);

    return 0;
}