#include <cstdio>

const unsigned int BYTE_WIDTH = 8;
const char thing[] =
    "stuff\0"
    "stuff2\0"
    "stuff3\0";

int main()
{
    printf("%lu\n", sizeof(thing));
        
    for (unsigned int rows = 0; rows < sizeof(thing) / BYTE_WIDTH; rows++) {
        for (unsigned int col = 0; col < BYTE_WIDTH; col++) {
            printf("0x%02x ", thing[rows * BYTE_WIDTH + col]);
        }
        
        printf("    ");
        
        for (unsigned int col = 0; col < BYTE_WIDTH; col++) {
            unsigned char t = thing[rows * BYTE_WIDTH + col];
            if (t > 32 && t < 127) {
                printf("%c", t);
            } else {
                printf(".");
            }
        }
        
        printf("\n");
    }
    
    unsigned int remainder = sizeof(thing) % BYTE_WIDTH;
    if (remainder) {
        int lastRow = sizeof(thing) / BYTE_WIDTH;
        for (unsigned int col = 0; col < remainder; col++) {
            printf("0x%02x ", thing[lastRow * BYTE_WIDTH + col]);
        }
        
        for (unsigned int i = BYTE_WIDTH - remainder; i > 0; i--) {
            printf("     ");
        }
        printf("    ");
        
        for (unsigned int col = 0; col < remainder; col++) {
            unsigned char t = thing[lastRow * BYTE_WIDTH + col];
            if (t > 32 && t < 127) {
                printf("%c", t);
            } else {
                printf(".");
            }
        }
    }
}
