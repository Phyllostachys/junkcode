#include <cstdio>
#include <windows.h>

#define STATUS_NOT_FOUND 0xC0000225L

int main(int argc, char **argv) {
    void *algHandle;
    unsigned long ret = BCryptOpenAlgorithmProvider(&algHandle, BCRYPT_RNG_ALGORITHM, 0ul, 0ul);
    if (ret != 0ul) {
        switch (ret) {
            case STATUS_NOT_FOUND:
                printf("BCryptOpenAlgorithmProvider error, not found (0x%lx)\n", ret);
                break;

            case STATUS_INVALID_PARAMETER:
                printf("BCryptOpenAlgorithmProvider error, invalid parameter (0x%lx)\n", ret);
                break;

            case STATUS_NO_MEMORY:
                printf("BCryptOpenAlgorithmProvider error, no memory (0x%lx)\n", ret);
                break;

            default:
                printf("BCryptOpenAlgorithmProvider error, other (0x%lx)\n", ret);
                break;
        }
        return -1;
    }

    unsigned int num;
    if (argc > 1) {
        ret = sscanf(argv[1], "%d", &num);
        if (ret == 0) {
            num = 32;
        }
    } else {
        num = 32;
    }

    unsigned char *buf = new unsigned char[num];
    ret = BCryptGenRandom(algHandle, buf, num, 0l);
    switch (ret) {
        case 0l: {
                int counter = 0;
                for (int i = 0; i < num; i++) {
                    printf("%4d ", buf[i]);
                    if (++counter > 7) {
                        counter = 0;
                        puts("");
                    }
                }
            }
            break;

        case STATUS_INVALID_PARAMETER:
            printf("BCryptGenRandom error, invalid parameter (0x%lx)\n", ret);
            break;

        case STATUS_INVALID_HANDLE:
            printf("BCryptGenRandom error, invalid handle (0x%lx)\n", ret);
            break;

        default:
            printf("BCryptOpenAlgorithmProvider error, other (0x%lx)\n", ret);
            break;
    }



    ret = BCryptCloseAlgorithmProvider(algHandle, 0ul);
    switch (ret) {
        case 0ul:
        default:
            break;

        case STATUS_INVALID_HANDLE:
            printf("BCryptCloseAlgorithmProvider error, invalid handle (0x%lx)\n", ret);
            break;
    }



	return 0;
}
