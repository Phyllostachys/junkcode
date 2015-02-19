#include <iostream>

int gameBoard[5][5] = {
    {0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0}
};

void printBoard(int board[5][5]) {
    std::cout << std::endl << std::endl;
    for(int y = 0; y < 5; y++){
        for(int x = 0; x < 5; x++){
            std::cout << board[y][x] << " ";
        }
        std::cout << std::endl;
    }
}

int main(int argc, char** arg) {
    printBoard(gameBoard);
}