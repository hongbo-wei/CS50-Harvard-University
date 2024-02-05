#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // Get the input height
    int height;
    do
    {
        height = get_int("Height: ");
    }
    // Input a positive integer between 1 and 8, inclusive.
    // If not, re-prompt the user until they cooperate.
    while (height > 8 || height < 1);

    // Build the mario block
    for(int i = 1; i <= height; i++)
    {
        // Build space
        int j;
        for (j = height - i; j > 0; j--)
        {
            printf(" ");
        }

        // Build hash sign #
        for (j = i; j > 0; j--)
        {
            printf("#");
        }

        // Build space in bettween hash sign
        printf("  ");

        // Build hash sign #
        for (j = i; j > 0; j--)
        {
            printf("#");
        }
        printf("\n");
    }
}