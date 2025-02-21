#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

string caesar(string text, int key);

int main(int argc, string argv[])
{
    // Make sure program was run with just one command-line argument
    if (argc != 2)
    {
        printf("Usage ./caesar key\n");
        return 1;
    }

    // Make sure every character in argv[1] is a digit
    for (int i = 0, n = strlen(argv[1]); i < n; i++)
    {
        if (!(isdigit(argv[1][i])))
        {
            printf("Usage ./caesar key\n");
            return 1;
        }
    }

    // Convert argv[1] from a `string` to an `int`
    int key = atoi(argv[1]);

    // Prompt user for plaintext
    string text = get_string("plaintext: ");

    // Encrypt plaintext
    string ciphertext = caesar(text, key);

    // Output ciphertext
    printf("ciphertext: %s\n", ciphertext);

    return 0;
}

string caesar(string text, int key)
{
    string ciphertext = text;

    // For each character in the plaintext:
    for (int i = 0, length = strlen(text); i < length; i++)
    {
        char letter = text[i];

        // Rotate the character if it's a letter
        if (isupper(letter))
        {
            ciphertext[i] = (letter - 'A' + key) % 26 + 'A';
        }
        else if (islower(letter))
        {
            ciphertext[i] = (letter - 'a' + key) % 26 + 'a';
        }
    }

    return ciphertext;
}
