#include <stdio.h>
#include <stdlib.h>

#define INPUT_FILE "input.txt"

// counts the number of digits by just dividing n by 10 until it is 0
int numDigits(long n) {
    int res = 0;
    while (n > 0) {
        n /= 10;
        res ++;
    }
    return res;
}

// I'm like 90% sure that math.h has integer to the power of integer
// but it was faster for me to write this function than to look it up
long tenPow(long n) {
    long res = 1;
    for (long i = 0; i < n; i++) {
        res *= 10;
    }
    return res;
}

int main() {
    FILE* f = fopen(INPUT_FILE, "r");

    // first attempt was wrong because I used ints instead of longs, whoops
    long sum = 0;

    while (!feof(f)) {
        long fid, lid;
        char comma;
        fscanf(f, "%ld-%ld%c ", &fid, &lid, &comma);

        for (long i = fid; i <= lid; i++) {
            int digits = numDigits(i);
            // the input text states that 101 would not be considered symmetrical
            // so digits must be even
            if (digits % 2 == 0) {
                // split the number in half
                long split = tenPow(digits/2);
                long lhalf = i / split;
                long rhalf = i % split;
                if (lhalf == rhalf) {
                    sum += i;
                }
            }
        }
    }

    printf("%ld\n", sum);

    return 0;
}