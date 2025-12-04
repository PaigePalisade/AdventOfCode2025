#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INPUT_FILE "input.txt"

int width;
int height;

int getNeighbors(char grid[200][200], int r, int c) {
    int count = 0;
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            int r1 = r + i;
            int c1 = c + j;
            if (r1 >= 0 && r1 < height && c1 >= 0 && c1 < width) {
                if (!(r1 == r && c1 == c) && (grid[r1][c1] == '@' || grid[r1][c1] == 'x')) {
                    count ++;
                }
            }
        }
    }
    return count;
}

int main() {
    FILE* f = fopen(INPUT_FILE, "r");

    int count = 0;

    char grid[200][200];

    char line[200];

    for (int i = 0; !feof(f); i++) {
        fscanf(f, "%s ", line);
        width = strlen(line);
        height = i + 1;
        strcpy(grid[i], line);
    }
    
    // replace all removed @'s with x's which the getNeighbors counts as the same
    // then delete all of the x's
    // this way, the removed rolls still count as neighbors before the step is finished
    int removed = -1;
    while (removed != 0) {
        removed = 0;
        for (int r = 0; r < height; r++) {
            for (int c = 0; c < width; c++) {
                if (grid[r][c] == '@' && getNeighbors(grid, r, c) < 4) {
                    count ++;
                    printf("x");
                    grid[r][c] = 'x';
                    removed ++;
                }
                else {
                    printf("%c", grid[r][c]);
                }
            }
            printf("\n");
        }
        for (int r = 0; r < height; r++) {
            for (int c = 0; c < width; c++) {
                if (grid[r][c] == 'x') {
                    grid[r][c] = '.';
                }
            }
        }
        printf("\n");
    }

    printf("%d\n", count);

    return 0;
}