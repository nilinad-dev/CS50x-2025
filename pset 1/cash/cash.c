#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int cents;
    int coins = 0;

    // Prompt user until a valid input is given
    do
    {
        cents = get_int("Change owed: ");
    }
    while (cents < 0);

    // Use as many quarters (25 cents) as possible
    coins += cents / 25;
    cents %= 25;

    // Use as many dimes (10 cents) as possible
    coins += cents / 10;
    cents %= 10;

    // Use as many nickels (5 cents) as possible
    coins += cents / 5;
    cents %= 5;

    // Use as many pennies (1 cent) as possible
    coins += cents;

    printf("%d\n", coins);
}
