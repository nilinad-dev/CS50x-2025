#include <cs50.h>
#include <stdio.h>

bool check_luhn(long number);
void card_identify(long number);
int get_length(long number);

int main(void)
{
    // Prompt user for credit card number
    long number = get_long("Number: ");

    // Validate number using Luhn’s Algorithm
    if (check_luhn(number))
    {
        card_identify(number);
    }
    else
    {
        printf("INVALID\n");
    }
}

// Function to validate the credit card using Luhn’s Algorithm
bool check_luhn(long number)
{
    int sum = 0;
    bool multiply = false;

    while (number > 0)
    {
        int digit = number % 10;

        if (multiply)
        {
            digit *= 2;
            sum += (digit / 10) + (digit % 10);
        }
        else
        {
            sum += digit;
        }

        multiply = !multiply;
        number /= 10;
    }

    return (sum % 10 == 0);
}

// Get first two digits
void card_identify(long number)
{
    int length = get_length(number);
    int first_two_digits;
    int first_digit;

    // Get first two digits
    while (number > 100)
    {
        number /= 10;
    }

    first_two_digits = number;
    first_digit = number / 10;

    // Identify the card type
    if (length == 15 && (first_two_digits == 34 || first_two_digits == 37))
    {
        printf("AMEX\n");
    }
    else if (length == 16 && (first_two_digits >= 51 && first_two_digits <= 55))
    {
        printf("MASTERCARD\n");
    }
    else if ((length == 13 || length == 16) && first_digit == 4)
    {
        printf("VISA\n");
    }
    else
    {
        printf("INVALID\n");
    }
}

// Function to get the length of the credit card number
int get_length(long number)
{
    int length = 0;
    while (number > 0)
    {
        number /= 10;
        length++;
    }
    return length;
}
