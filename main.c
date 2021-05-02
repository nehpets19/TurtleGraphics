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

void initializeFloor(int floor[][COL_SIZE]);
void getCommands(int commands[][COMMANDS_COL_SIZE]);
void printFloor(int floor[][COL_SIZE]);

int main(void)
{
    int floor[ROW_SIZE][COL_SIZE];
    int commands[COMMANDS_ROW_SIZE][COMMANDS_COL_SIZE] = {{0, 0}};

    initializeFloor(floor);
    getCommands(commands);

    size_t row = 0;
    int command[COMMANDS_COL_SIZE] = {commands[row][0], commands[row][1]};
    int xPos = 0;
    int yPos = 0;
    int penState = PEN_UP;
    int xIncrement = INCREASE;
    int yIncrement = NONE;

    while (row < COMMANDS_ROW_SIZE && command[0] != END)
    {
        switch (command[0])
        {
        case PEN_DOWN:
            penState = PEN_DOWN;
            break;
        case PEN_UP:
            penState = PEN_UP;
            break;
        case MOVE_FORWARD:
            for (size_t step = 1; step < command[1]; step++)
            {
                if (penState == PEN_DOWN)
                {
                    floor[yPos][xPos] = 1;
                }

                xPos += xIncrement;
                yPos += yIncrement;
            }
            break;
        case TURN_LEFT:
            if (xIncrement == INCREASE && yPos > 0) // currently moving right -> turn up
            {
                yIncrement = DECREASE;
                xIncrement = NONE;
            }
            else if (xIncrement == DECREASE && yPos < (ROW_SIZE - 1)) // currently moving left -> turn down
            {
                yIncrement = INCREASE;
                xIncrement = NONE;
            }
            else if (yIncrement == INCREASE && xPos < (COL_SIZE - 1)) // currenty moving down -> turn right
            {
                yIncrement = NONE;
                xIncrement = INCREASE;
            }
            else if (yIncrement == DECREASE && xPos > 0) // currently moving up -> turn left
            {
                yIncrement = NONE;
                xIncrement = DECREASE;
            }
            break;
        case TURN_RIGHT:
            if (xIncrement == INCREASE && yPos < (ROW_SIZE - 1)) // currently moving right -> turn down
            {
                yIncrement = INCREASE;
                xIncrement = NONE;
            }
            else if (xIncrement == DECREASE && yPos > 0) // currently moving left -> turn up
            {
                yIncrement = DECREASE;
                xIncrement = NONE;
            }
            else if (yIncrement == INCREASE && xPos > 0) // currently going down -> turn left
            {
                yIncrement = NONE;
                xIncrement = DECREASE;
            }
            else if (yIncrement == DECREASE && xPos < (COL_SIZE - 1)) // currently going up -> turn right
            {
                yIncrement = NONE;
                xIncrement = INCREASE;
            }
            break;
        case PRINT_FLOOR:
            printFloor(floor);
            break;
        }

        row++;
        command[0] = commands[row][0];
        command[1] = commands[row][1];
    }
}

void initializeFloor(int floor[][COL_SIZE])
{
    for (size_t row = 0; row < ROW_SIZE; row++)
    {
        for (size_t col = 0; col < COL_SIZE; col++)
        {
            floor[row][col] = 0;
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

void printFloor(int floor[][COL_SIZE])
{
    puts("");
    for (size_t row = 0; row < ROW_SIZE; row++)
    {
        for (size_t col = 0; col < COL_SIZE; col++)
        {
            printf("%d", floor[row][col]);
        }

        puts("");
    }
}
