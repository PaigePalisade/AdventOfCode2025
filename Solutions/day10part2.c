#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define INPUT_FILE "example.txt"

typedef struct {
    int buttons[20][20];
    int numButtons;
    int buttonSizes[20];
    int joltages[20];
    int numJoltages;
} Machine;

int main() {
    FILE* f = fopen(INPUT_FILE, "r");

    long sum = 0;

    Machine machines[200] = {0};
    int numMachines;

    for (int i = 0; !feof(f); i++) {
        Machine m = {0};
        char c = '0';
        char garbage[100];
        fscanf(f, "%s ", garbage);

        fscanf(f, " %c", &c);
        while (c != '{') {
            fscanf(f, "%d%c", &m.buttons[m.numButtons][m.buttonSizes[m.numButtons]++], &c);
            if (c == ')') {
                m.numButtons ++;
                fscanf(f, " %c", &c);
            }
        }
        while (c != '}') {
            fscanf(f, "%d%c", &m.joltages[m.numJoltages++], &c);
        }
        fscanf(f, " ");
        machines[i] = m;
    }

    printf("\n%ld\n", sum);

    return 0;
}