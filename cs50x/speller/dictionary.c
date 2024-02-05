// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include <strings.h>
#include <stdio.h>
#include <stdlib.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 45;

// Hash table
node *table[N];

// Set a variable to count the size of a dictionary used
unsigned int count = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    // Hash the word to determine which linked list to check
    int index = hash(word);

    // Traverse the hash table to see if the word is in the linked list
    node *cursor = table[index];

    while (cursor)
    {
        // stracasecmp() is similar to strcmp(), but case insensitive
        if (strcasecmp(word, cursor->word) == 0) // If two words are the same, the function returns 0
        {
            return true;
        }
        // Move the cursor to next node
        cursor = cursor->next;
    }

    // If not, then the word is not in the dictionary
    return false;

}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    // Consider a hash function that uses a sum of ASCII values or the length of a word.
    // Words' Length is up to 45
    // 'A' - 65, 45 * 65 == 2925
    // 'Z' - 90, 45 * 90 == 4050
    int len = strlen(word) - 1;
    if (len > 44)
    {
        len = 44;
    }
    return len; // 0 < return value < N - 1
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    // Open the dictionary
    FILE *dict = fopen(dictionary, "r");
    int index;

    if (dict != NULL)
    {
        // Create a pointer to store a string one at a time from the file being read
        char word[LENGTH + 1];

        // Read strings from file one at a time
        while (fscanf(dict, "%s", word) != EOF)
        {
            // Create a poniter to make a linked list in hash table
            node *n = malloc(sizeof(node));

            if (n == NULL)
            {
                printf("Unable to allocate memory\n");
                return false;
            }

            n->next = NULL;

            // Copy the word and construct the linked list accordingly
            strcpy(n->word, word);
            index = hash(word);
            n->next = table[index];
            table[index] = n;

            // Increase the count by 1
            count++;
        }

        // After looping the entire file, close it.
        fclose(dict);
        return true;
    }

    else
    {
        printf("Unable to open %s\n", dictionary);
        return false;
    }
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return count;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    for (int index = 0; index < N; index++)
    {
        node *tmp = table[index];
        node *cursor = table[index];

        // Keep looping until reach the end of a linked list
        while (cursor)
        {
            cursor = cursor->next;
            free(tmp);
            tmp = cursor;
        }
    }
    return true;
}
