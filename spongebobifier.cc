#include <cstdio>
#include <ctime>

#include <string>

void usage(char **argv) {
    printf("Usage: %s <string to spongebobify>", argv[0]);
}

int main(int argc, char **argv) {
    if (argc <= 1) {
        usage(argv);
        return -1;
    }

    srand(time(nullptr));

    std::string inp{argv[1]};
    std::string out{};
    int flopper = rand() & 1;
    for (char c : inp) {
        //out += ' ';
        if (flopper == 1) {
            if (c >= 65 && c <= 90) {
                out += (c + 32);
            } else if (c >= 97 && c <= 122) {
                out += (c - 32);
            } else {
                out += c;
            }
            flopper = 0;
        } else {
            out += c;
            flopper = 1;
        }
    }

    printf("%s\n", out.c_str() + 1);


    return 0;
}
