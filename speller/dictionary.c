// Implements a dictionary's functionality
#include <ctype.h>
#include <stdbool.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

int words = 0;

// TODO: Choose number of buckets in hash table
const unsigned int N = 650;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    int index = hash(word);

    if (table[index] == NULL)
    {
        return false;
    }

    node *n = table[index];

    while (n != NULL)
    {
        if (!strcasecmp(n->word, word))
        {
            return true;
        }

        n = n->next;
    }

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // Return int letter position in alphabet

    int index = tolower(word[0]) - 'a';
    index = index * 25;

    if (word[1] != '\0')
    {
        index += tolower(word[1]) - 'a';
    }

    return index;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    FILE *p = fopen(dictionary, "r");

    if (p == NULL)
    {
        return false;
    }

    char word[LENGTH];

    while (fscanf(p, "%s", word) != EOF)
    {
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            return false;
        }

        strcpy(n->word, word);
        n->next = NULL;

        int index = hash(word);

        n->next = table[index];
        table[index] = n;

        words++;
    }

    fclose(p);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return words;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        if (table[i] != NULL)
        {
            node *n = table[i];

            while (n != NULL)
            {
                node *tmp = n;

                n = n->next;

                free(tmp);
            }
        }
    }

    return true;
}
