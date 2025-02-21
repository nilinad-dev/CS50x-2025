#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool key_validation(string key);
string substitute(string text, string key);

int main(int argc, string argv[])
{
    // Check for exactly one command-line argument
    if (argc != 2)
    {
        printf("Usage ./substitution key\n");
        return 1;
    }

    string key = argv[1];

    // Validate the key
    if (!key_validation(key))
    {
        return 1;
    }

    // Get plaintext from user
    string text = get_string("plaintext: ");

    // Encrypt plaintext
    string ciphertext = substitute(text, key);

    // Output ciphertext
    printf("ciphertext: %s\n", ciphertext);

    return 0;
}

// Validate the key: length, alphabetic, and uniqueness
bool key_validation(string key)
{
    int key_length = strlen(key);

    // Check length
    if (key_length != 26)
    {
        printf("Key must contain 26 characters.\n");
        return false;
    }

    // Track used characters
    bool used[26] = {false};

    for (int i = 0; i < key_length; i++)
    {
        if (!isalpha(key[i]))
        {
            printf("Key must only contain alphabetic characters.\n");
            return false;
        }

        int index = toupper(key[i]) - 'A';

        if (used[index])
        {
            printf("Key must not contain repeated characters.\n");
            return false;
        }

        used[index] = true;
    }

    return true;
}

// Perform the substitution cipher
string substitute(string text, string key)
{
    int text_length = strlen(text);
    string ciphertext = text;

    for (int i = 0; i < text_length; i++)
    {
        if (isalpha(text[i]))
        {
            bool is_lower = islower(text[i]);
            int letter_index = toupper(text[i]) - 'A';
            char cipher_letter = key[letter_index];

            // Preserve case
            if (is_lower)
            {
                ciphertext[i] = tolower(cipher_letter);
            }
            else
            {
                ciphertext[i] = toupper(cipher_letter);
            }
        }
    }

    return ciphertext;
}
