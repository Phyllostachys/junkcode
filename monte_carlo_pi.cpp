#include <cstdint>
#include <cstdio>
#include <cmath>
#include <ctime>

#include <random>

#define SHOW 0
int main() {
    static const uint32_t iterations = 100000000;
    uint32_t inside_cnt = 0;

    std::mt19937 random;
    random.seed(time(0));

    for (int i = 0; i < iterations; i++) {
        double x = (double)random() / ((double)INT32_MAX * 2.0);
        double y = (double)random() / ((double)INT32_MAX * 2.0);
        if (sqrt(x * x + y * y) < 1.0) {
            inside_cnt++;
        }

        if (SHOW && (i % 10000))
            printf("\rpi = %f", 4.0 * inside_cnt / (double)i);
    }

    if (SHOW)
        printf("\n");

    printf("Total: %d\tInside: %d\n", iterations, inside_cnt);
    printf("pi = %f\n", 4.0 * inside_cnt / (double)iterations);
    return 0;
}
