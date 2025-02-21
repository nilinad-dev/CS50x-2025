#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

// Points assigned to each letters
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

// Function prototype
int compute_score(string word);

int main(void)
{
    // Get input words from both players
    string player1 = get_string("Player 1: ");
    string player2 = get_string("Player 2: ");

    // Calculate scores
    int score_player1 = compute_score(player1);
    int score_player2 = compute_score(player2);

    // Print the winner or tie
    if (score_player1 > score_player2)
    {
        printf("Player 1 wins!\n");
    }
    else if (score_player1 < score_player2)
    {
        printf("Player 2 wins!\n");
    }
    else
    {
        printf("Tie!\n");
    }
}

// Compute and return score for a given word
int compute_score(string word)
{
    int score = 0;

    for (int i = 0, n = strlen(word); i < n; i++)
    {
        if isalpha (word[i])
        {
            // Convert to uppercase and find index
            int index = toupper(word[i]) - 'A';
            score += POINTS[index];
        }
    }
    return score;
}
