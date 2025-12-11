#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define INPUT_FILE "input.txt"

#define OUT 10003 //labelToIndex("out")
#define YOU 16608 //labelToIndex("you")

int connections[17576][17576];
int numConnections[17576] = {0};

// converts a three letter label into a base 26 index
int labelToIndex(char* label) {
    int res = 0;
    for (int i = 0; i < 3; i++) {
        res *= 26;
        res += label[i] - 'a';
    }
    return res;
}

// gets the number of paths that go from `index` to OUT
long getNumPaths(int index) {
    if (index == OUT) {
        return 1;
    }
    long res = 0;
    for (int i = 0; i < numConnections[index]; i++) {
        res += getNumPaths(connections[index][i]);
    }
    return res;
}

int main() {
    FILE* f = fopen(INPUT_FILE, "r");

    while (!feof(f)) {
        char label[6];
        fscanf(f, "%3s: ", label);
        int origin = labelToIndex(label);
        char c = ' ';
        while (c != '\n' && !feof(f)) {
            fscanf(f, "%3s%c", label, &c);
            connections[origin][numConnections[origin]++] = labelToIndex(label); 
        }
        ungetc('\n', f);
        fscanf(f, " ");
    }

    printf("\n%ld\n", getNumPaths(YOU));

    return 0;
}