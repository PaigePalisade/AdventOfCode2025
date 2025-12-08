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

double distances[1000][1000];

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

    long product = 1;

    int targetPairs = 1000;
    if (strcmp("example.txt", INPUT_FILE) == 0) {
        targetPairs = 10;
    }

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

    for (int i = 0; i < numJunctions; i++) {
        for (int j = 0; j < numJunctions; j++) {
            double d = dist(junctions[i], junctions[j]);
            distances[i][j] = d;
            distances[j][i] = d;
        }
    }

    for (int p = 0; p < targetPairs; p++) {
        int shortest[2] = {0,0};
        double minDist = __INT_MAX__;
        for (int i = 0; i < numJunctions; i++) {
            for (int j = 0; j < numJunctions; j++) {
                if (!connections[i][j] && i != j) {
                    double d = distances[i][j];
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
        connections[i][j] = 1;
        connections[j][i] = 1;
        unite(i, j);
    }

    printf("\n");

    qsort(circuitSize, numJunctions, sizeof(int), compare);

    for (int i = 0; i < 3; i++) {
        product *= circuitSize[i];
    }

    printf("\n%ld\n", product);

    return 0;
}