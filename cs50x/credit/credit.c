#include <cs50.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    long int card;
    card = get_long("Number: ");

    char number[20];
    int len;
    sprintf(number, "%li", card);

    len = strlen(number);
    if ((len != 13) && (len != 15) && (len != 16))
    {
        printf("INVALID\n");
        return 0;
    }

    // To add digit as Luhn's Algorithm requires
    int digit_mutiplied;
    int one_digit;
    int ten_digit;
    int digit_not_mutiplied;

    // Luhn's Algorithm sum
    int sum = 0;

    // Get a copy for later use
    long int card_copy = card;

    // Get the second-to-last digit
    card /= 10;

    // Multiply every other digit by 2, starting with the number’s second-to-last digit,
    // and then add those products’ digits together.
    while (card > 0)
    {
        digit_mutiplied = card % 10;
        card /= 100;
        if (digit_mutiplied * 2 >= 10)
        {
            one_digit = digit_mutiplied * 2 % 10;
            ten_digit = digit_mutiplied * 2 / 10;
            sum += one_digit + ten_digit;
        }
        else
        {
            sum += digit_mutiplied * 2;
        }
    }

    // Add the sum to the sum of the digits that weren’t multiplied by 2.
    while (card_copy > 0)
    {
        digit_not_mutiplied = card_copy % 10;
        sum += digit_not_mutiplied;
        card_copy /= 100;
    }
    // printf("%d\n", sum);

    // If the total’s last digit is 0 (or, put more formally, if the total modulo 10 is congruent to 0), the number is valid!
    if (sum % 10 == 0)
    {
        if (number[0] == '4')
        {
            printf("VISA\n");
        }
        else if ((number[0] == '3') && ((number[1] == '4') || (number[1] == '7')))
        {
            printf("AMEX\n");
        }
        else if ((number[0] == '5') && ((number[1] == '1') || (number[1] == '2') ||
                                        (number[1] == '3') || (number[1] == '4') || (number[1] == '5')))
        {
            printf("MASTERCARD\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }

}