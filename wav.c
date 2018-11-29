#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#define SQUARE
int main(void) {
    FILE *f, *f2;
    f = fopen("test.wav", "wb");
    if (!f) {
        puts("Cannot create file");
        return -1;
    }

    f2 = fopen("data.txt", "w");
    if (!f2) {
        puts("Cannot create file");
        return -1;
    }

    int16_t data[128];
    for (int i = 0; i < 128; i++) {
        data[i] = (int16_t)((double)INT16_MAX * sin(2.0 * 3.1415 * (double)i / 128.0));
    }

    int chunkSize = 16;
    int16_t formatCode = 0x1;
    int16_t numChannels = 1;
    int sampleRate = 44100;
    int16_t bitsPerSample = 16;
    int16_t blockAlignSize = (bitsPerSample + 7) / 8;
    int dataRate = sampleRate * blockAlignSize;
    int dataChunkSize = (128 * 1000) * blockAlignSize;
    int numChunks = 4 + 8 + 16 + 8 + ((128 * 1000) * blockAlignSize);

    fwrite("RIFF", sizeof(char), strlen("RIFF"), f);
    fwrite(&numChunks, sizeof(int), 1, f);
    fwrite("WAVEfmt ", sizeof(char), strlen("WAVEfmt "), f);
    fwrite(&chunkSize, sizeof(int), 1, f);
    fwrite(&formatCode, sizeof(int16_t), 1, f);
    fwrite(&numChannels, sizeof(int16_t), 1, f);
    fwrite(&sampleRate, sizeof(int), 1, f);
    fwrite(&dataRate, sizeof(int), 1, f);
    fwrite(&blockAlignSize, sizeof(int16_t), 1, f);
    fwrite(&bitsPerSample, sizeof(int16_t), 1, f);
    fwrite("data", sizeof(char), strlen("data"), f);
    fwrite(&dataChunkSize, sizeof(int), 1, f);
    for (int i = 0; i < (128 * 1000); i++) {
#if defined(SQUARE)
        if (data[i % 128] > (INT16_MAX / 2)) {
            int16_t out = INT16_MAX;
            fwrite(&out, sizeof(int16_t), 1, f);
            //fprintf(f2, "%d\n", out);
        } else {
            int16_t out = 0;
            fwrite(&out, sizeof(int16_t), 1, f);
            //fprintf(f2, "%d\n", out);
        }
#else
         fwrite(&data[i % 128], sizeof(int16_t), 1, f);
         //fprintf(f2, "%d\n", data[i % 128]);
#endif
    }

    return 0;
}
