#include <stdio.h>

#define ROW_SIZE 50
#define COL_SIZE 50
#define COMMANDS_ROW_SIZE 50
#define COMMANDS_COL_SIZE 2
#define INCREASE 1
#define DECREASE -(1)
#define NONE 0

// commands
#define PEN_UP 1
#define PEN_DOWN 2
#define TURN_RIGHT 3
#define TURN_LEFT 4
#define MOVE_FORWARD 5
#define PRINT_FLOOR 6
#define END 9

void initializeFloor(char floor[][COL_SIZE]);
void getCommands(int commands[][COMMANDS_COL_SIZE]);
void printFloor(char floor[][COL_SIZE]);
void start(char floor[][COL_SIZE], int commands[][COMMANDS_COL_SIZE]);
void turnUp(int *xIncrement, int *yIncrement);
void turnDown(int *xIncrement, int *yIncrement);
void turnLeft(int *xIncrement, int *yIncrement);
void turnRight(int *xIncrement, int *yIncrement);

int main(void)
{
    char floor[ROW_SIZE][COL_SIZE];
    int commands[COMMANDS_ROW_SIZE][COMMANDS_COL_SIZE] = {{0, 0}};

    initializeFloor(floor);
    getCommands(commands);
    start(floor, commands);
}

void initializeFloor(char floor[][COL_SIZE])
{
    for (size_t row = 0; row < ROW_SIZE; row++)
    {
        for (size_t col = 0; col < COL_SIZE; col++)
        {
            floor[row][col] = ' ';
        }
    }
}

void getCommands(int commands[][COMMANDS_COL_SIZE])
{
    int first_command = 0;
    int second_command = 0;
    size_t row = 0;

    while (row < COMMANDS_ROW_SIZE && first_command != END)
    {
        printf("Enter a command (%d to end input): ", END);
        scanf("%d, %d", &first_command, &second_command);

        if ((first_command >= PEN_UP && first_command <= PRINT_FLOOR) ||
            first_command == END)
        {
            commands[row][0] = first_command;
            commands[row][1] = second_command;
            second_command = 0;
            row++;
        }
    }
}

void start(char floor[][COL_SIZE], int commands[][COMMANDS_COL_SIZE])
{
    size_t row = 0;
    int currentCommand[COMMANDS_COL_SIZE] = {commands[row][0], commands[row][1]};
    int xPos = 0;
    int yPos = 0;
    int penState = PEN_UP;
    int xIncrement = INCREASE;
    int yIncrement = NONE;

    while (row < COMMANDS_ROW_SIZE && currentCommand[0] != END)
    {
        switch (currentCommand[0])
        {
        case PEN_DOWN:
            penState = PEN_DOWN;
            break;
        case PEN_UP:
            penState = PEN_UP;
            break;
        case MOVE_FORWARD:
            for (size_t step = 1; step <= currentCommand[1]; step++)
            {
                if (penState == PEN_DOWN)
                {
                    floor[yPos][xPos] = '*';
                }

                xPos += xIncrement;
                yPos += yIncrement;
            }
            break;
        case TURN_LEFT:
            if (xIncrement == INCREASE && yPos > 0) // currently moving right -> turn up
            {
                turnUp(&xIncrement, &yIncrement);
            }
            else if (xIncrement == DECREASE && yPos < (ROW_SIZE - 1)) // currently moving left -> turn down
            {
                turnDown(&xIncrement, &yIncrement);
            }
            else if (yIncrement == INCREASE && xPos < (COL_SIZE - 1)) // currenty moving down -> turn right
            {
                turnRight(&xIncrement, &yIncrement);
            }
            else if (yIncrement == DECREASE && xPos > 0) // currently moving up -> turn left
            {
                turnLeft(&xIncrement, &yIncrement);
            }
            break;
        case TURN_RIGHT:
            if (xIncrement == INCREASE && yPos < (ROW_SIZE - 1)) // currently moving right -> turn down
            {
                turnDown(&xIncrement, &yIncrement);
            }
            else if (xIncrement == DECREASE && yPos > 0) // currently moving left -> turn up
            {
                turnUp(&xIncrement, &yIncrement);
            }
            else if (yIncrement == INCREASE && xPos > 0) // currently moving down -> turn left
            {
                turnLeft(&xIncrement, &yIncrement);
            }
            else if (yIncrement == DECREASE && xPos < (COL_SIZE - 1)) // currently moving up -> turn right
            {
                turnRight(&xIncrement, &yIncrement);
            }
            break;
        case PRINT_FLOOR:
            printFloor(floor);
            break;
        }

        row++;
        currentCommand[0] = commands[row][0];
        currentCommand[1] = commands[row][1];
    }
}

void turnUp(int *xIncrement, int *yIncrement)
{
    *xIncrement = NONE;
    *yIncrement = DECREASE;
}

void turnDown(int *xIncrement, int *yIncrement)
{
    *xIncrement = NONE;
    *yIncrement = INCREASE;
}

void turnRight(int *xIncrement, int *yIncrement)
{
    *xIncrement = INCREASE;
    *yIncrement = NONE;
}

void turnLeft(int *xIncrement, int *yIncrement)
{
    *xIncrement = DECREASE;
    *yIncrement = NONE;
}

void printFloor(char floor[][COL_SIZE])
{
    puts("");
    for (size_t row = 0; row < ROW_SIZE; row++)
    {
        for (size_t col = 0; col < COL_SIZE; col++)
        {
            printf("%c ", floor[row][col]);
        }

        puts("");
    }
}
