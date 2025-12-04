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
                if (!(r1 == r && c1 == c) && grid[r1][c1] == '@') {
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
    
    for (int r = 0; r < height; r++) {
        for (int c = 0; c < width; c++) {
            if (grid[r][c] == '@' && getNeighbors(grid, r, c) < 4) {
                count ++;
                printf("x");
            }
            else {
                printf("%c", grid[r][c]);
            }
        }
        printf("\n");
    }

    printf("%d\n", count);

    return 0;
}