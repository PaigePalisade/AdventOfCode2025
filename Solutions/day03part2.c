#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INPUT_FILE "input.txt"

int main() {
    FILE* f = fopen(INPUT_FILE, "r");

    long sum = 0;

    char str[200];
    while (!feof(f)) {
        fscanf(f, "%s ", str);
        int len = strlen(str);

        int indexArr[200] = {0};
        for (int i = 0; i < 12; i++) {
            int start = 0;
            if (i != 0) {
                indexArr[i] = indexArr[i-1]+1;
                start = indexArr[i-1]+1;
            }
            for (int j = start; j < len-12+i+1; j++) {
                if (str[j] > str[indexArr[i]]) {
                    indexArr[i] = j;
                }
            }
        }
        long partial = 0;
        for (int i = 0; i < 12; i++) {
            printf("%c", str[indexArr[i]]);
            partial *= 10;
            partial += str[indexArr[i]] - '0';
        }
        printf("\n");
        sum += partial;
    }
    
    printf("%ld\n", sum);

    return 0;
}