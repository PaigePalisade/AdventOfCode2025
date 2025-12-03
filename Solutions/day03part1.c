#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INPUT_FILE "input.txt"

int main() {
    FILE* f = fopen(INPUT_FILE, "r");

    int sum = 0;

    char str[200];
    while (!feof(f)) {
        fscanf(f, "%s ", str);
        // indexes of first and second battery
        int d1 = 0;
        int d2 = 0;
        int len = strlen(str);
        for (int i = 0; i < len-1; i++) {
            if (str[i] > str[d1]) {
                d1 = i;
            }
        }
        d2 = d1 + 1;
        for (int i = d1+1; i < len; i++) {
            if (str[i] > str[d2]) {
                d2 = i;
            }
        }
        printf("%c%c\n", str[d1], str[d2]);
        sum += (str[d1] - '0') * 10 + (str[d2] - '0');
    }
    
    printf("%d\n", sum);

    return 0;
}