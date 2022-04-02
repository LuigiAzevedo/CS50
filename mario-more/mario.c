#include <cs50.h>
#include <stdio.h>

void printPyramid(int size);
void printPyramidBlock(int size, int column);

int main(void)
{
    int size = 0;

    // Ask the user the size of the pyramid and validates the input
    do
    {
        size = get_int("What pyramid size you want?\n");
    }
    while (size <= 0 || size > 8);

    // Print the pyramid
    printPyramid(size);
}

// Print the pyramid
void printPyramid(int size)
{
    // Count the current pyramid column
    int column = 0;

    // Place the correct spacing for each line of the pyramid
    for (int i = 0; i < size; i++)
    {
        for (int j = size - 1; j > i; j--)
        {
            printf(" ");
        }

        column++;

        // Print blocks to form the Mario pyramid
        printPyramidBlock(size, column);

        // Move to the next pyramid line
        printf("\n");
    }
}

// Mount blocks for the pyramid
void printPyramidBlock(int size, int column)
{
    // Print the blocks for the pyramid
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < column; j++)
        {
            printf("#");
        }

        // Put a space between blocks in the first interation
        if (i == 0)
        {
            printf("  ");
        }
    }
}