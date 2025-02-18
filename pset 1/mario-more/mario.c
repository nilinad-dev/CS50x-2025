#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int height;

    // Prompt user for input until they enter a valid height
    do
    {
        height = get_int("Height: ");
    }
    while (height < 1);

    // Loop through each row
    for (int row = 1; row <= height; row++)
    {
        // Print spaces (left pyramid alignment)
        for (int col = 0; col < height - row; col++)
        {
            printf(" ");
        }

        // Print left-side hashes
        for (int col = 0; col < row; col++)
        {
            printf("#");
        }

        // Print the two spaces in the middle
        printf("  ");

        // Print right-side hashes
        for (int col = 0; col < row; col++)
        {
            printf("#");
        }

        // Move to the next line
        printf("\n");
    }
}
