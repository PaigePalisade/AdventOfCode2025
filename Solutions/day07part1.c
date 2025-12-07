#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INPUT_FILE "input.txt"

int main() {
    FILE* f = fopen(INPUT_FILE, "r");

    long count = 0;
    
    char grid[500][500];

    fscanf(f, "%s ", grid[0]);
    int len = strlen(grid[0]);

    // get first line, replace S with beam
    for (int i = 0; i < len; i++) {
        if (grid[0][i] == 'S') {
            grid[0][i] = '|';
        }
    }

    printf("%s\n", grid[0]);

    // for each character in the next lines
    // check if value above it is a beam
    // if the character is a ., copy the beam down
    // if it is a ^, copy the beam left and right, increase count
    for (int i = 1; !feof(f); i++) {
        fscanf(f, "%s ", grid[i]);
        for (int j = 0; j < len; j++) {
            if (grid[i][j] == '.' && grid[i-1][j] == '|') {
                grid[i][j] = '|';
            }
            if (grid[i][j] == '^' && grid[i-1][j] == '|') {
                count ++;
                grid[i][j-1] = '|';
                grid[i][j+1] = '|';
            }
        }
        printf("%s\n", grid[i]);
    }

    printf("\n%ld\n", count);

    return 0;
}