#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // Prompts the username
    string name = get_string("What's your name?\n");

    // Prints the greetings and the username
    printf("hello, %s\n", name);
}