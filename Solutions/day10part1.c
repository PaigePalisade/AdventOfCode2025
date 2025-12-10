#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define INPUT_FILE "input.txt"

typedef struct {
    unsigned target;
    unsigned buttons[20];
    int numButtons;
} Machine;

Machine machines[200] = {0};
int numMachines;

int checkCombination(unsigned arr[], int size, unsigned target) {
    unsigned value = 0;
    for (int i = 0; i < size; i++) {
        value ^= arr[i];
    }
    if (value == target) {
        for (int i = 0; i < size; i++) {
            printf("%d ", arr[i]);
        }
        printf("\n");
    }
    return value == target;
}

// modified from https://www.w3resource.com/c-programming-exercises/array/c-array-exercise-82.php
int checkCombosHelper(unsigned arr[], unsigned data[], int st, int end, int index, int r, unsigned target) {
    if (index == r) {
        return checkCombination(data, r, target);
    }

    for (int i = st; i <= end && end - i + 1 >= r - index; i++) {
        data[index] = arr[i];
        if (checkCombosHelper(arr, data, i+1, end, index+1, r, target)) {
            return 1;
        }
    }
    return 0;
}

int checkAllCombinationsR(Machine m, int r) {
    unsigned data[20];
    return checkCombosHelper(m.buttons, data, 0, m.numButtons-1, 0, r, m.target);
}

int main() {
    FILE* f = fopen(INPUT_FILE, "r");

    long sum = 0;

    for (int i = 0; !feof(f); i++) {
        Machine m = {0};
        char c = '0';
        fscanf(f, "[%c", &c);
        int j = 0;
        while (c != ']') {
            if (c == '#') {
                m.target |= (1 << j);
            }
            fscanf(f, "%c", &c);
            j++;
        }
        fscanf(f, " %c", &c);
        while (c != '{') {
            int n;
            fscanf(f, "%d%c", &n, &c);
            m.buttons[m.numButtons] |= (1 << n);
            if (c == ')') {
                m.numButtons ++;
                fscanf(f, " %c", &c);
            }
        }
        char garbage[100];
        fscanf(f, "%s ", garbage);
        machines[numMachines] = m;
        numMachines ++;
    }

    for (int i = 0; i < numMachines; i++) {
        Machine m = machines[i];
        for (int r = 1; r <= m.numButtons; r++) {
            if (checkAllCombinationsR(m, r)) {
                sum += r;
                break;
            }
        }
    }

    printf("\n%ld\n", sum);

    return 0;
}