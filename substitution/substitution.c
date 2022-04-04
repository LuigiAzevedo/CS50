#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

void print_ciphertext(string key, string user_input);

int main(int argc, string argv[])
{

    if (argv[1] == NULL)
    {
        printf("You need to provide a key\n");
        return 1;
    }

    if (argv[2] != NULL)
    {
        printf("Too many arguments\n");
        return 1;
    }

    // Cryptographic key
    string key = argv[1];

    // Validade if the key has 26 chars
    if (strlen(key) != 26)
    {
        printf("Key must be exactly 26 characters long.");
        return 1;
    }

    for (int i = 0, len = strlen(key); i < len; i++)
    {
        // Validate if the entire key is alphabetic
        if (!isalpha(key[i]))
        {
            printf("Alphabetic characters only.");
            return 1;
        }
        // Validate if the key contains duplicated letters
        if (strchr(key + i + 1, key[i]))
        {
            printf("The key must not contain duplicate letters.\n");
            return 1;
        }
    }

    // Ask the user for the phrase to be encrypted
    string user_input = get_string("plaintext: ");

    print_ciphertext(key, user_input);
}


void print_ciphertext(string key, string user_input)
{
    printf("ciphertext: ");

    for (int i = 0, l = strlen(user_input); i < l; i++)
    {
        if (isalpha(user_input[i]))
        {
            if (islower(user_input[i]))
            {
                int position = user_input[i] - 'a';
                printf("%c", tolower(key[position]));
            }
            else
            {
                int position = user_input[i] - 'A';
                printf("%c", toupper(key[position]));
            }
        }
        else
        {
            printf("%c", user_input[i]);
        }
    }
    printf("\n");
}