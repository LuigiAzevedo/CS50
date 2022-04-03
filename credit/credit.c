#include <cs50.h>
#include <stdio.h>

int extractDigits(long number);
string identifyCreditCard(long number);
int luhnsAlgorithm(long number);
int concatenate(int x, int y);

int main(void)
{
    long credit_card = get_long("Please, insert your credit card number.\n");

    int validation_number = luhnsAlgorithm(credit_card);

    // Checks if the last digit of the sum is 0 to validate the card
    if (0 != extractDigits(validation_number))
    {
        printf("INVALID\n");
    }
    else
    {
        string type = identifyCreditCard(credit_card);
        printf("%s", type);
    }

}

// Extract the last digit of the credit card number
int extractDigits(long number)
{
    int dig = number % 10;
    return dig;
}

// Identify if the credit card is Visa, Mastercard, AMEX or Invalid
string identifyCreditCard(long credit_card)
{
    string card_type = "";
    int dig = 0;
    int dig1 = 0;
    int dig2 = 0;
    int credit_card_num_lengt = 0;
    while (credit_card > 0)
    {
        credit_card_num_lengt++;
        dig2 = dig1;
        dig1 = extractDigits(credit_card);
        credit_card = credit_card / 10;
    }

    dig = concatenate(dig1, dig2);

    // Test lengt and first digit to determine the card flag
    if (dig1 == 4 && credit_card_num_lengt > 12 && credit_card_num_lengt < 17)
    {
        card_type = "VISA\n";
    }
    else if ((credit_card_num_lengt == 15) && (dig == 34 || dig == 37))
    {
        card_type = "AMEX\n";
    }
    else if (credit_card_num_lengt == 16 && (dig == 51 || dig == 52 || dig == 53 || dig == 54 || dig == 55))
    {
        card_type = "MASTERCARD\n";
    }
    else
    {
        card_type = "INVALID\n";
    }


    return card_type;
}

// Algorithm to determine if the credit card number syntactically valid
int luhnsAlgorithm(long credit_card)
{

    int dig;
    int aux = 0;
    int total_number = 0;

    while (credit_card > 0)
    {
        dig = extractDigits(credit_card);
        credit_card = credit_card / 10;

        if (aux % 2)
        {
            dig = dig * 2;
            if (dig > 9)
            {

                int num = dig;
                while (num > 0)
                {
                    dig = extractDigits(num);
                    num = num / 10;
                    total_number = total_number + dig;
                }
            }
            else
            {
                total_number = total_number + dig;
            }
        }
        else
        {
            total_number = total_number + dig;
        }
        aux++;
    }

    return total_number;
}

// Concatenate 2 numbers in one
int concatenate(int num1, int num2)
{
    int x = 10;
    while (num2 >= x)
    {
        x *= 10;
    }

    return num1 * x + num2;
}