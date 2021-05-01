#include <stdio.h>

#define ROW_SIZE 50
#define COL_SIZE 50

void initializeFloor(int floor[][COL_SIZE]);
void printFloor(int floor[][COL_SIZE]);

int main(void)
{
    int floor[ROW_SIZE][COL_SIZE];

    initializeFloor(floor);
    printFloor(floor);
}

void initializeFloor(int floor[][COL_SIZE])
{
    int row, col;

    for (row = 0; row < ROW_SIZE; row++)
    {
        for (col = 0; col < COL_SIZE; col++)
        {
            floor[row][col] = 0;
        }
    }
}

void printFloor(int floor[][COL_SIZE])
{
    int row, col;

    for (row = 0; row < ROW_SIZE; row++)
    {
        for (col = 0; col < COL_SIZE; col++)
        {
            printf("%d", floor[row][col]);
        }

        puts("");
    }
}
