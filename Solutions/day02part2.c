#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define INPUT_FILE "input.txt"

// this solution works on strings, not the longs because it seemed easier

// checks to see if a given number string is "invalid" (is a repeating string)
int checkStr(char* numstr) {
    int len = strlen(numstr);
    // j is the length of the repeating substring
    // it cannot be higher than len/2, as then it wouldn't be able to repeat
    // if len is divisible by j, check len/j substrings to see if they are all equal
    for (int j = 1; j <= len/2; j++) {
        if (len % j == 0) {
            int invalid = 1;
            for (int k = 0; k < len-j+1; k +=j) {
                if (strncmp(numstr, numstr+k, j) != 0) {
                    invalid = 0;
                    break;
                }
            }
            if (invalid) return 1;
        }
    }
    return 0;
}

int main() {
    FILE* f = fopen(INPUT_FILE, "r");

    long sum = 0;

    while (!feof(f)) {
        long fid, lid;
        char comma;
        fscanf(f, "%ld-%ld%c ", &fid, &lid, &comma);

        char numstr[100];
        int len;

        for (long i = fid; i <= lid; i++) {
            // convert i to a string
            sprintf(numstr, "%ld", i);
            if (checkStr(numstr)) {
                sum += i;
            }
        }
    }

    printf("%ld\n", sum);

    return 0;
}