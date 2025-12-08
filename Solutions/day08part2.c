#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>

#define INPUT_FILE "input.txt"

// disjoint set structure of the junctions in a circuit
int set[1000];

// contains the sizes of each circutit at each root node in the set
int circuitSize[1000] = {0};

// boolean table to check if junction i (row) and j (col) are connected
int connections[1000][1000] = {0};

typedef struct {
    int x, y, z;
} Junction;

int compare(const void *a, const void *b) {
    int arg1 = *(const int *)a;
    int arg2 = *(const int *)b;
    return arg2 - arg1;
}

int find(int i) {
    if (set[i] == i) {
        return i;
    }
    return find(set[i]);
}

void unite(int i, int j) {
    int irep = find(i);
    int jrep = find(j);

    if (irep == jrep) {
        return;
    }

    // combine the size of the respective circuits
    int isize = circuitSize[irep];
    int jsize = circuitSize[jrep];

    set[irep] = jrep;
    circuitSize[irep] = 0;

    circuitSize[jrep] = isize + jsize;
}


double dist(Junction a, Junction b) {
    double x = (double)(a.x-b.x) * (double)(a.x-b.x);
    double y = (double)(a.y-b.y) * (double)(a.y-b.y);
    double z = (double)(a.z-b.z) * (double)(a.z-b.z);
    return sqrt(x + y + z);
}

int main() {
    FILE* f = fopen(INPUT_FILE, "r");

    long result = 1;

    Junction junctions[1000];
    int numJunctions = 0;

    for (int i = 0; !feof(f); i++) {
        fscanf(f, "%d,%d,%d ", &junctions[i].x, &junctions[i].y, &junctions[i].z);
        numJunctions ++;
    }

    for  (int i = 0; i < 1000; i++) {
        set[i] = i;
        circuitSize[i] = 1;
    }

    int currentsize = 0;

    while (currentsize != numJunctions) {
        int shortest[2] = {0,0};
        double minDist = __INT_MAX__;
        for (int i = 0; i < numJunctions; i++) {
            for (int j = 0; j < numJunctions; j++) {
                if (!connections[i][j] && i != j) {
                    double d = dist(junctions[i], junctions[j]);
                    if (d < minDist) {
                        minDist = d;
                        shortest[0] = i;
                        shortest[1] = j;
                    }
                }
            }
        }
        int i = shortest[0];
        int j = shortest[1];
        printf("Connecting %d, %d, %d ", junctions[i].x, junctions[i].y, junctions[i].z);
        printf("and %d, %d, %d\n", junctions[j].x, junctions[j].y, junctions[j].z); 
        connections[i][j] = 1;
        connections[j][i] = 1;
        unite(i, j);
        printf("%d\n", circuitSize[find(i)]);
        currentsize = circuitSize[find(i)];
        result = (long)junctions[i].x * junctions[j].x;
    }

    printf("\n%ld\n", result);

    return 0;
}