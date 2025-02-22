#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
} pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
bool creates_cycle(int winner, int loser);
void lock_pairs(void);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }

    // Populate array of candidates
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        // Update global preferences based on this voter's ranks
        record_preferences(ranks);
        printf("\n");
    }

    add_pairs();    // Find all winning pairs
    sort_pairs();   // Sort pairs by strength of victory
    lock_pairs();   // Lock pairs into the graph, avoiding cycles
    print_winner(); // Determine and print the winner
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(candidates[i], name) == 0)
        {
            ranks[rank] = i; // Store candidate index in ranks
            return true;
        }
    }
    return false; // Invalid candidate name 
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // For each higher-ranked candidate, increment preference over lower-ranked
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            preferences[ranks[i]][ranks[j]]++;
        }
    }
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            // Swap if current pair is weaker than the next
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }
        }
    }
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    for (int i = 0; i < pair_count - 1; i++)
    {
        for (int j = i + 1; j < pair_count; j++)
        {
            int strength_i = preferences[pairs[i].winner][pairs[i].loser] -
                             preferences[pairs[i].loser][pairs[i].winner];
            int strength_j = preferences[pairs[j].winner][pairs[j].loser] -
                             preferences[pairs[j].loser][pairs[j].winner];

            if (strength_j > strength_i)
            {
                pair temp = pairs[i];
                pairs[i] = pairs[j];
                pairs[j] = temp;
            }
        }
    }
}

bool creates_cycle(int winner, int loser)
{
    if (winner == loser)
    {
        return true; // Cycle detected
    }
    for (int i = 0; i < candidate_count; i++)
    {
        if (locked[loser][i] && creates_cycle(winner, i))
        {
            return true; // Indirect cycle detected
        }
    }
    return false;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    for (int i = 0; i < pair_count; i++)
    {
        if (!creates_cycle(pairs[i].winner, pairs[i].loser))
        {
            locked[pairs[i].winner][pairs[i].loser] = true; // Safe to lock
        }
    }
}

// Print the winner of the election
void print_winner(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        bool source = true; // Assume candidate has no incoming edges

        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[j][i])
            {
                source = false; // Found incoming edge
                break;
            }
        }
        if (source)
        {
            printf("%s\n", candidates[i]);
            return; // Winner found
        }
    }
}
