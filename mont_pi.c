#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

#include <windows.h>
#include <ntsecapi.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#define ITERATIONS 50000

int main(void) {
    unsigned int r = 0;
    double pi = 0;
    static const double div_num = 1 / (double)UINT32_MAX;

    double cnt = 0;
    for (int i = 0; i < ITERATIONS; i++) {
        RtlGenRandom((void *)&r, 4);
        double x = (double)r * div_num;
        x = x * 2.0 - 1.0;

        RtlGenRandom((void *)&r, 4);
        double y = (double)r * div_num;
        y = y * 2.0 - 1.0;

        if (sqrt(x * x + y * y) < 1.0) {
            cnt++;
        }
    }

    pi = 4 * cnt / (double)ITERATIONS;
    printf("Inside: %d out of %d\nEsimated pi = %f\n", (unsigned int)cnt, ITERATIONS, pi);
    printf("Diff from pi is %f%%\n", 100.0 * (pi - M_PI) / M_PI);

    return 0;
}
