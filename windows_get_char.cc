#include <conio.h>
#include <iostream>

int main()
{
    while(1) {
        if (kbhit() != 0) {
            char c = my_getch();
            std::cout << c << std::endl;
            if (c == 'q') {
                break;
            }
        }
    }
}
