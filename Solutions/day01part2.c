#include <stdio.h>
#include <stdlib.h>

#define INPUT_FILE "input.txt"

int main() {
    FILE* f = fopen(INPUT_FILE, "r");

    int dial = 50;
    int count = 0;

    for (int i = 0; !feof(f); i++) {
        char c; int d;
        int t = 0;
        fscanf(f, "%c%d ", &c, &d);
        if (c == 'L') {
            // if the dial is already zero, we will always underflow at least once
            if (dial == 0) {
                t --;
            }
            dial -= d;
            // count underflows
            while (dial < 0) {
                t ++;
                dial += 100;
            }
            // check zero without underflow
            if (dial == 0) {
                t ++;
            }
        }
        if (c == 'R') {
            dial += d;
            // count overflows
            while (dial >= 100) {
                t ++;
                dial -= 100;
            }
        }

        printf("%c%d %d: %d times\n", c, d, dial, t);
        count += t;

    }

    printf("count: %d\n", count);

    return 0;
}