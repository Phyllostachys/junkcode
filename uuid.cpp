#include <cstdio>
#include <windows.h>

int main(int argc, char **argv) {
    int num;
    if (argc > 1) {
        sscanf(argv[1], "%d", &num);
    } else {
        num = 1;
    }

    for (int i = 0; i < num; i++) {
        UUID u;
        UuidCreate(&u);
        unsigned char *buf;
        UuidToStringA(&u, &buf);
        printf("%s\n", buf);
        RpcStringFree(&buf);
    }

    return 0;
}
