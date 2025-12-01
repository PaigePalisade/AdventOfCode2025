#include <stdio.h>
#include <stdlib.h>

#define INPUT_FILE "input.txt"

int main() {
    FILE* f = fopen(INPUT_FILE, "r");

    int dial = 50;

    int count = 0;

    for (int i = 0; !feof(f); i++) {
        char c; int d;
        fscanf(f, "%c%d ", &c, &d);
        if (c == 'L') {
            dial -= d;
        }
        if (c == 'R') {
            dial += d;
        }
        // C does mod incorrectly with negative numbers, adding a suffeciently large multiple of 100 fixes this
        dial += 10000;
        dial %= 100;
        printf("%d\n", dial);
        if (dial == 0) {
            count ++;
        }

    }

    printf("count: %d\n", count);

    return 0;
}