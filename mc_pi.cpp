// An implementation of this: https://en.wikipedia.org/wiki/Monte_Carlo_method#Introduction

#include <cstdint>
#include <cstdio>
#include <cmath>
#include <ctime>

#include <random>

#define SHOW 0
int main() {
    static const uint32_t iterations = 500000;
    static const double div_num = 1.0 / ((double)INT32_MAX * 2.0);
    uint32_t inside_cnt = 0;

    std::mt19937 random;
    random.seed(time(0));

    for (int i = 0; i < iterations; i++) {
        double x = (double)random() * div_num;
        double y = (double)random() * div_num;
        double z = (double)random() * div_num;
        if (sqrt(x * x + y * y + z * z) < 1.0) {
            printf("v %f %f %f\n", x, y, z);
        }

        if (SHOW && (i % 10000))
            printf("\rpi = %f", 4.0 * inside_cnt / (double)i);
    }

    if (SHOW)
        printf("\n");

    //printf("Total: %d\tInside: %d\n", iterations, inside_cnt);
    //printf("pi = %f\n", 4.0 * inside_cnt / (double)iterations);
    return 0;
}
