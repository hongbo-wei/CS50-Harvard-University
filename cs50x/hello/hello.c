#include <stdio.h>
#include <cs50.h>

int main(void)
{
    // Get user input
    string name = get_string("What is your name? ");

    // Greet the person
    printf("Hello, %s\n", name);
}