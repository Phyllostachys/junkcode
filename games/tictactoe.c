#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

typedef struct {
    enum {empty, marked_x, marked_o} markedAs;
} TTT_cell_t;

struct {
    TTT_cell_t board[3][3];
    uint8_t playerTurn;
} gameBoard;

void gameBoard_init(void)
{
    int x,y;

    gameBoard.playerTurn = 1;
    for (y = 0; y < 3; y++)
    {
        for (x = 0; x < 3; x++)
        {
            gameBoard.board[y][x].markedAs = empty;
        }
    }
}

void gameBoard_display(void)
{
}

bool gameBoard_check(void)
{
    return false;
}

int main(int argc, char** argv)
{
    gameBoard_init();
    return 0;
}
