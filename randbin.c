// compile with clang:
// clang -march=skylake randbin.c
// or whatever architecture you have. It only works on certain architectures.

#include <math.h>
#include <stdio.h>

int main(int argc, char **argv) {
    int filesize = 0;
    char byte_multiplier = 0;
    if (argc <= 1) {
        filesize = 512 * 1024;
    } else {
        sscanf(argv[1], "%u%c", &filesize, &byte_multiplier);
    }

    switch (byte_multiplier) {
        case 'k':
        case 'K':
            filesize *= 1024;
            break;

        case 'm':
        case 'M':
            filesize *= 1024 * 1024;
            break;
    }

    FILE *fout = fopen("out.bin", "wb");

    if (filesize <= 4) {
        unsigned int a = 0;
        __builtin_ia32_rdrand32_step(&a);
        fwrite(&a, 1, filesize, fout);
    } else {
        int bytes = (int)floor((double)filesize / 4) + (filesize % 4);
        for (int i = 0; i < bytes; i++) {
            unsigned int a = 0;
            __builtin_ia32_rdrand32_step(&a);
            fwrite(&a, sizeof a, 1, fout);
        }
    }

    fclose(fout);
    return 0;
}
