#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define INPUT_FILE "input.txt"

#define OUT 10003 //labelToIndex("out")
#define YOU 16608 //labelToIndex("you")
#define SVR 12731 //labelToIndex("srv")
#define FFT 3529  //labelToIndex("fft")
#define DAC 2030  //labelToIndex("dac")
#define LABEL_MAX 17576

int connections[LABEL_MAX][LABEL_MAX];
int numConnections[LABEL_MAX] = {0};
// memoization table
int numPaths[LABEL_MAX];

// converts a three letter label into a base 26 index
int labelToIndex(char* label) {
    int res = 0;
    for (int i = 0; i < 3; i++) {
        res *= 26;
        res += label[i] - 'a';
    }
    return res;
}

// gets the number of paths that go from `index` to `target`, ignoring any paths that go through `avoid`
long getNumPaths(int index, int target, int avoid) {
    if (index == avoid) {
        return 0;
    }
    if (numPaths[index] != -1) {
        return numPaths[index];
    }
    if (index == target) {
        return 1;
    }
    if (index == OUT) {
        return 0;
    }
    long res = 0;
    for (int i = 0; i < numConnections[index]; i++) {
        res += getNumPaths(connections[index][i], target, avoid);
    }
    numPaths[index] = res;
    return res;
}

// memoization table becomes out of date every time getNumPaths is called with a new `target`
void resetNumPaths() {
    for (int i = 0; i < LABEL_MAX; i++) {
        numPaths[i] = -1;
    }
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

    // get paths that go SVR->DAC->FFT->OUT and SVR->FFT-DAC->OUT
    // paths that go e.g. SVR->DAC->FFT = SVR->DAC * DAC->FFT

    resetNumPaths();
    long svrToDac = getNumPaths(SVR, DAC, FFT);

    resetNumPaths();
    long svrToFft = getNumPaths(SVR, FFT, DAC);

    resetNumPaths();
    long fftToDac = getNumPaths(FFT, DAC, -1);

    resetNumPaths();
    long dacToFft = getNumPaths(DAC, FFT, -1);

    resetNumPaths();
    long dacToOut = getNumPaths(DAC, OUT, FFT);

    resetNumPaths();
    long FftToOut = getNumPaths(FFT, OUT, DAC);


    printf("\n%ld\n", svrToDac * dacToFft * FftToOut + svrToFft * fftToDac * dacToOut);

    return 0;
}