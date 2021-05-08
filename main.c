#include <stdio.h>

// commands
#define PEN_UP 1
#define PEN_DOWN 2
#define TURN_RIGHT 3
#define TURN_LEFT 4
#define MOVE_FORWARD 5
#define PRINT_FLOOR 6
#define END 9

#define ROW_SIZE 50
#define COL_SIZE 50
#define COMMANDS_ROW_SIZE 50
#define COMMANDS_COL_SIZE 2
#define INCREASE 1
#define DECREASE -(1)
#define NONE 0
#define IS_MOVING_RIGHT(increment) (increment.xInc == INCREASE && increment.yInc == NONE)
#define IS_MOVING_LEFT(increment) (increment.xInc == DECREASE && increment.yInc == NONE)
#define IS_MOVING_UP(increment) (increment.xInc == NONE && increment.yInc == DECREASE)
#define IS_MOVING_DOWN(increment) (increment.xInc == NONE && increment.yInc == INCREASE)
#define WRITE_SYMBOL 0x2A // ASCII hex for '*' (asterisk)
#define EMPTY_SYMBOL 0x20 // ASCII hex for ' ' (SPACE)

typedef struct Point
{
    int x;
    int y;
} Point;

typedef struct Increment
{
    int xInc;
    int yInc;
} Increment;

void initializeFloor(char floor[][COL_SIZE]);
void getCommands(int commands[][COMMANDS_COL_SIZE]);
void printFloor(char floor[][COL_SIZE]);
void start(char floor[][COL_SIZE], int commands[][COMMANDS_COL_SIZE]);
void turnUp(Increment *increment);
void turnDown(Increment *increment);
void turnLeft(Increment *increment);
void turnRight(Increment *increment);
void updateFloor(int penState, char floor[][COL_SIZE], Point *currentPos);
void movePosition(char floor[][COL_SIZE], int totalSteps, Point *currentPos, Increment *increment);

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
            floor[row][col] = EMPTY_SYMBOL;
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
    Increment increment = {INCREASE, NONE}; // move right by default
    Point currentPos = {0, 0};
    size_t row = 0;
    int currentCommand = commands[row][0];
    int totalSteps;
    int penState = PEN_UP;

    while (row < COMMANDS_ROW_SIZE && currentCommand != END)
    {
        switch (currentCommand)
        {
        case PEN_DOWN:
            penState = PEN_DOWN;
            break;
        case PEN_UP:
            penState = PEN_UP;
            break;
        case MOVE_FORWARD:
            totalSteps = commands[row][1];

            for (size_t step = 1; step <= totalSteps; step++)
            {
                updateFloor(penState, floor, &currentPos);

                if (step < totalSteps)
                {
                    movePosition(floor, totalSteps, &currentPos, &increment);
                }
            }
            break;
        case TURN_RIGHT:
            if (IS_MOVING_RIGHT(increment)) // currently moving right -> turn down
            {
                turnDown(&increment);
            }
            else if (IS_MOVING_LEFT(increment)) // currently moving left -> turn up
            {
                turnUp(&increment);
            }
            else if (IS_MOVING_DOWN(increment)) // currently moving down -> turn left
            {
                turnLeft(&increment);
            }
            else if (IS_MOVING_UP(increment)) // currently moving up -> turn right
            {
                turnRight(&increment);
            }
            break;
        case TURN_LEFT:
            if (IS_MOVING_RIGHT(increment)) // currently moving right -> turn up
            {
                turnUp(&increment);
            }
            else if (IS_MOVING_LEFT(increment)) // currently moving left -> turn down
            {
                turnDown(&increment);
            }
            else if (IS_MOVING_DOWN(increment)) // currenty moving down -> turn right
            {
                turnRight(&increment);
            }
            else if (IS_MOVING_UP(increment)) // currently moving up -> turn left
            {
                turnLeft(&increment);
            }
            break;
        case PRINT_FLOOR:
            printFloor(floor);
            break;
        }

        row++;
        currentCommand = commands[row][0];
    }
}

void updateFloor(int penState, char floor[][COL_SIZE], Point *currentPos)
{
    if (penState == PEN_DOWN)
    {
        floor[currentPos->y][currentPos->x] = WRITE_SYMBOL;
    }
}

void movePosition(char floor[][COL_SIZE], int totalSteps, Point *currentPos, Increment *increment)
{
    int nextX = currentPos->x + increment->xInc;
    int nextY = currentPos->y + increment->yInc;

    if (nextX >= 0 && nextX <= (COL_SIZE - 1))
    {
        currentPos->x = nextX;
    }

    if (nextY >= 0 && nextY <= (ROW_SIZE - 1))
    {
        currentPos->y = nextY;
    }
}

void turnUp(Increment *increment)
{
    increment->xInc = NONE;
    increment->yInc = DECREASE;
}

void turnDown(Increment *increment)
{
    increment->xInc = NONE;
    increment->yInc = INCREASE;
}

void turnRight(Increment *increment)
{
    increment->xInc = INCREASE;
    increment->yInc = NONE;
}

void turnLeft(Increment *increment)
{
    increment->xInc = DECREASE;
    increment->yInc = NONE;
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
