#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

int count_letters(string text);
int count_words(string text);
int count_sentences(string text);

int main(void)
{
    // Get the text from user input
    string text = get_string("Text: ");

    // Define varaiables to count: letters, words, sentences
    int letters_count = count_letters(text);
    int words_count = count_words(text);
    int sentences_count = count_sentences(text);

    // A formula for computing the reading level of a text: Coleman-Liau index
    float L = 1.0 * letters_count / words_count * 100;
    float S = 1.0 * sentences_count / words_count * 100;
    float index = 0.0588 * L  - 0.296 * S - 15.8;

    // Round the result to nearest integer.
    int grade = round(index);

    // Print result depends on its value.
    if (grade >= 16)
    {
        printf("Grade 16+\n");
    }
    else if (grade <= 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade %i\n", grade);
    }
}

// Count the number of letters
int count_letters(string text)
{
    int length = strlen(text);
    int count = 0;
    for (int i = 0; i < length; i++)
    {
        if (((text[i] >= 'A') && (text[i] <= 'Z')) || ((text[i] >= 'a') && (text[i] <= 'z')))
        {
            count++;
        }
    }
    return count;
}

// Count the number of words
int count_words(string text)
{
    int length = strlen(text);
    int count = 0;
    for (int i = 0; i < length; i++)
    {
        if (text[i] == ' ')
        {
            count++;
        }
    }
    count++;
    return count;
}

// Count the number of sentences
int count_sentences(string text)
{
    int length = strlen(text);
    int count = 0;
    for (int i = 0; i < length; i++)
    {
        if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            count++;
        }
    }
    return count;
}