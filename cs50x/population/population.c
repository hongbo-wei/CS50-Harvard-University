#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // TODO: Prompt for start size
    int start;
    do
    {
        start = get_int("Please enter the start population (greater than 9): ");
    }
    while (start < 9);

    // TODO: Prompt for end size
    int end;
    do
    {
                end = get_int("Please enter the end population: ");
    }
    while (end < start);

    // TODO: Calculate number of years until we reach threshold
    int n = 0;
    while (start < end)
    {
        start += (int)start/3 - (int)start/4;
        n ++;
    }

    // TODO: Print number of years
    printf("Years: %i", n);
}
