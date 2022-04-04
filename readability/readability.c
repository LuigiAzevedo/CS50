#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int count_letters(char c);
int count_words(char c);
int count_setences(char c);
float coleman_liau_index(int letters, int setences, int words);

int main(void)
{
    // Ask the user for the text to calculate the correct grade level
    string text = get_string("Text: ");

    int setences = 0;
    int words = 1;
    int letters = 0;

    // Go through every char in the string
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        // return the amount of lettert, words and setences to calculate the Coleman Liau Index
        letters = letters + count_letters(text[i]);
        words = words + count_words(text[i]);
        setences = setences + count_setences(text[i]);
    }

    // Return the text grade base on the Coleman Liau Index
    float index = coleman_liau_index(letters, setences, words);


    // Print the text grade level
    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index > 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %.0f\n", round(index));
    }
}

float coleman_liau_index(int letters, int setences, int words)
{
    float letters_per_100 = 100.00 * letters / words ;
    float setences_per_100 = 100.00 * setences / words;

    float index = 0.0588 * letters_per_100 - 0.296 * setences_per_100 - 15.8;

    return index;
}

int count_setences(char c)
{
    // 33 == !  //  46 == ;  //  63 == ?
    if (c == 33 || c == 46 || c == 63)
    {
        return 1;
    }

    return 0;
}

int count_words(char c)
{
    if (isspace(c))
    {
        return 1;
    }

    return 0;
}

int count_letters(char c)
{
    if (isalpha(c))
    {
        return 1;
    }

    return 0;
}