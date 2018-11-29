//#define RTL

#include <cstdio>
#include <windows.h>

#ifdef RTL
#include <ntsecapi.h>
#endif

int main(int argc, char **argv) {
    unsigned long ret;
#ifndef RTL
    void *algHandle;
    ret = BCryptOpenAlgorithmProvider(&algHandle, BCRYPT_RNG_ALGORITHM, 0ul, 0ul);
    if (ret != 0ul) {
        switch (ret) {
            case 0xC0000225L:
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
#endif

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

#ifndef RTL
    ret = BCryptGenRandom(algHandle, buf, num, 0l);
    switch (ret) {
        case 0l: {
                int counter = 0;
                for (int i = 0; i < num; i++) {
                    printf("%02x", buf[i]);
                    if (++counter > 3) {
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
#else
    //ret = SystemFunction036(buf, num);
    ret = RtlGenRandom(buf, num);
    switch (ret) {
        case TRUE: {
                int counter = 0;
                for (int i = 0; i < num; i++) {
                    printf("%02x", buf[i]);
                    if (++counter > 3) {
                        counter = 0;
                        puts("");
                    }
                }
            }
            break;

        default:
        case FALSE:
            printf("RtlGenRandom error (0x%lx)\n", ret);
            break;

    }
#endif

#ifndef RTL
    ret = BCryptCloseAlgorithmProvider(algHandle, 0ul);
    switch (ret) {
        case 0ul:
        default:
            break;

        case STATUS_INVALID_HANDLE:
            printf("BCryptCloseAlgorithmProvider error, invalid handle (0x%lx)\n", ret);
            break;
    }
#endif

	return 0;
}
