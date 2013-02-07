#include<stdio.h>
#include<stdlib.h>
#include <math.h>
#include<string.h>

#define MEN 0
#define WOMEN 1

// Structs development
struct data
{
    int matchRatings[10];
    char matchNames[20];
};

struct datingEvents
{
    struct data matches[2][10];
    int highestScores[10], tempScores[10];
    int pairs, ratings, tempRatings;
};

void permutationFunction(struct datingEvents *head, int positionOne)
{
    int i, j, positionTwo;

    if(positionOne == head -> pairs)
    {
        for(i = 0; i < head -> pairs; i++)
        {
            if (head -> matches[MEN][i].matchRatings[head -> tempScores[i]] < head -> matches[WOMEN][head -> tempScores[i]].matchRatings[i])
            {
                head -> tempRatings += head -> matches[MEN][i].matchRatings[head -> tempScores[i]];
            }
            else
            {
                head -> tempRatings += head -> matches[WOMEN][head -> tempScores[i]].matchRatings[i];
            }
        }

        //Comparing ratings to tempRatings
        if(head -> tempRatings > head -> ratings)
        {
            head -> ratings = head -> tempRatings;
            for(i = 0; i < head -> pairs; i++)
            {
                head -> highestScores[i] = head -> tempScores[i];
            }
        }
        head -> tempRatings = 0;
    }

    else
    {
        for(positionTwo = positionOne; positionTwo < head -> pairs; positionTwo++)
        {
            Ex(head, positionOne, positionTwo);
            permutationFunction(head, positionOne + 1);
            Ex(head, positionTwo, positionOne);
        }
    }
}

void Ex(struct datingEvents *head, int valueOne, int valueTwo)
{
    int tempValue = head -> tempScores[valueOne];
    head -> tempScores[valueOne] = head -> tempScores[valueTwo];
    head -> tempScores[valueTwo] = tempValue;
}

// Permutation Functions
void  permutationFunction(struct datingEvents *head, int positionOne);
void Ex(struct datingEvents *head, int valueOne, int valueTwo);

// Main Function
int main()
{
    // Variable Declarations
    struct datingEvents *head = (struct datingEvents *)malloc(sizeof(struct datingEvents));
    FILE *matchingInputFile;
    int speedDatingSessions, amountOfPairs, bestMatch, i, j, k, m;
    char *matchNames;

    // Specifying Input file name/location and checking if file is present
    matchingInputFile = fopen ("Matching.txt", "r");

    if(matchingInputFile == NULL)
    {
        printf("Input file not present, please check the file and try again\n");
        return 0;
    }

    fscanf(matchingInputFile, "%d", &speedDatingSessions);

    // Loop to go through the groups
    for(i = 0; i < speedDatingSessions; i++)
    {
        // Scanning data from Input file
        fscanf(matchingInputFile, "%d", &amountOfPairs);
        head -> pairs = amountOfPairs;
        head -> ratings = 0;
        head -> tempRatings = 0;
        for(j = 0; j < 10; j++)
        {
            head -> tempScores[j] = j;
        }

        // Scanning names
        for (j = 0; j < 2; j++)
        {
            for(k = 0; k < head -> pairs; k++)
                fscanf(matchingInputFile, "%s", head -> matches[j][k].matchNames);
        }

        // Scanning scores from Input file
        for (j = 0; j < 2; j++)
        {
            for(k = 0; k < head -> pairs; k++)
            {
                for(m = 0; m < head -> pairs; m++)
                {
                    fscanf(matchingInputFile, "%d", &head -> matches[j][k].matchRatings[m]);
                }
            }
        }

        // Calculation and output of the best matches
        permutationFunction(head, 0);

        printf("\nMatching #%d: Maximum Score = %d.\n\n", i + 1, head -> ratings);

        for(j = 0; j < head -> pairs; j++)
        {
            bestMatch = head -> highestScores[j];
            printf("%s %s\n", head -> matches[MEN][j].matchNames, head -> matches[WOMEN][bestMatch].matchNames);
        }
        printf("\n");
    }

    // Closing Input file and freeing memory
    fclose(matchingInputFile);
    free(head);
    return 0;
}
