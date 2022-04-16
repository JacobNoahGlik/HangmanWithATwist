#include "unit_test.h"

#define NUMBER_OF_VECTORS 30

void printStringsInVector(Vector *Location);
void printStatus(Status stat);
void eatChars();
Boolean getPreGameDecitions(int *lengthOfWords, int *numGuesses);
void printTurn(int turnNumber, int numGuesses, int size, int numCharsFound, Boolean showWR, int WR);
Status runGame();
void printGuessedLetters(char *LettersGuessed, int size);
char MakeGuess(char *LettersGuessed, int Size);
Status wishToPlayAgain();

//

//

int main(int argc, char *argv[])
{

    while (runGame())
    {
        printf("\n\n\n\n\n\n\nNEW GAME...\n\n\n");
    }
    printf("\n\nGame closed.\n");

    return 0;
}

//

//

//

//

Status runGame()
{
    int lengthOfWords, numGuesses;
    Boolean bRunningTotal = getPreGameDecitions(&lengthOfWords, &numGuesses);

    Vector *Master = VectorInitDefault();

    MY_STRING hMy_string = NULL;
    FILE *Dictionary;
    Dictionary = fopen("dictionary.txt", "r");
    //printf("exec\n");
    hMy_string = my_string_init_default();
    while (my_string_extraction(hMy_string, Dictionary))
    {
        if (my_string_get_size(hMy_string) == lengthOfWords)
        {
            MY_STRING str = my_string_init_c_string(my_string_c_str(hMy_string));
            addMyStringToVector(Master, str);
        }
    }
    fclose(Dictionary);
    my_string_destroy(&hMy_string);

    SuperVector *svMaster = initSV(Master, nameMaker(lengthOfWords));

    tNode *Tree = NULL;
    tNode *toBeRemoved = NULL;
    SuperVector *BiggestBucket = svMaster;

    MY_STRING pointToFree = nameMaker(lengthOfWords);
    MY_STRING *PreviousName = &pointToFree;

    char LettersGuessed[27];
    int guessCounter = 0;

    Boolean PlayerGuessedWord = FALSE;
    Boolean first_round = TRUE;

    while (!PlayerGuessedWord)
    {

        printf("\n\n\n\n\n\n");
        if (bRunningTotal)
        {
            printSV(BiggestBucket); // --a-a--- 5420
        }
        else
        {
            printf("%s\n", my_string_c_str(BiggestBucket->Name)); // --a-a---
        }

        if (!first_round)
        {
            if (my_string_compare(*PreviousName, BiggestBucket->Name) != 0)
            {
                printf("You guessed correctly!\n");
            }
            else
            {
                printf("Sorry, you guessed wrong\n");
                numGuesses--;
            }
        }
        PreviousName = &BiggestBucket->Name;

        if (numGuesses == 1)
        {
            printf("You've got 1 guess left\n");
        }
        else if (numGuesses == 0)
        {
            break;
        }
        else
        {
            printf("You've got %d guesses left\n", numGuesses);
        }

        printGuessedLetters(LettersGuessed, guessCounter);
        char Guess = MakeGuess(LettersGuessed, guessCounter);
        LettersGuessed[guessCounter] = Guess;
        guessCounter++;

        softWhipeTree(toBeRemoved);
        toBeRemoved = Tree;
        Tree = newGuessTree(BiggestBucket, Guess);

        if (bRunningTotal)
        {
            printf("\nbuilding new tree with guess '%c'\n", Guess);
            printTree(Tree);
        }

        //printf("\nThe Biggest Bucket in this tree is\n");
        BiggestBucket = getBiggestBucket(Tree, -1, NULL);
        //printSV(BiggestBucket);

        //Guess decition

        PlayerGuessedWord = SV_IsKnown(BiggestBucket);
        first_round = FALSE;
    }
    my_string_destroy(&pointToFree);

    if (PlayerGuessedWord)
    {
        printf("\n\n\n\n\n\nCongradulations! You guessed the word correctly with %d guesses remaining!\n", numGuesses);
    }
    else
    {
        printf("\n\n\n\n\n\nI'm sorry, you didn't guess the word.\n");
    }
    printf("The word was %s!\n", my_string_c_str(BiggestBucket->Data->data[0]));
    softWhipeTree(toBeRemoved);
    softWhipeTree(Tree);

    destroySV(svMaster);

    return wishToPlayAgain();
}

Status wishToPlayAgain()
{
    char ch;
    printf("Would you like to play again?(y/n) ... ");
    scanf("%c", &ch);
    eatChars();

    while (ch != 'Y' && ch != 'y' && ch != 'n' && ch != 'N')
    {
        printf("I'm sorry, %c is not (y/n), please respond with (y/n)\n", ch);
        printf("Would you like to play again?(y/n) ... ");
        scanf("%c", &ch);
        eatChars();
    }

    if (ch == 'n' || ch == 'N')
        return FAILURE;

    return SUCCESS;
}

void printGuessedLetters(char *LettersGuessed, int size)
{
    if (size == 0)
        return;

    printf("The letters you've already guessed are ... \n%c", LettersGuessed[0]);
    for (int i = 1; i < size; ++i)
    {
        printf(", %c", LettersGuessed[i]);
    }
    printf("\n");
}

char MakeGuess(char *LettersGuessed, int Size)
{
    char ch;
    printf("Guess a letter... ");
    scanf("%c", &ch);
    eatChars();

    Boolean duplicate = FALSE;
    for (int i = 0; i < Size; ++i)
    {
        if (ch == LettersGuessed[i])
            duplicate = TRUE;
    }

    while ((duplicate) || (ch < 65 || ch > 122) || (ch < 95 && ch > 90))
    {
        printf("Sorry '%c' is not a letter or has already been guessed. Please guess again... ", ch);
        scanf("%c", &ch);
        eatChars();
        duplicate = FALSE;

        for (int i = 0; i < Size; ++i)
        {
            if (ch == LettersGuessed[i])
                duplicate = TRUE;
        }
    }

    return ch;
}

void printStringsInVector(Vector *Location)
{
    for (int i = 0; i < Location->size; ++i)
    {
        printMy_String(Location->data[i]);
        printf("\n");
    }
}

void printTurn(int turnNumber, int numGuesses, int size, int numCharsFound, Boolean showWR, int WR)
{
    printf("Turn number %d\n", turnNumber);
    printf("Number of guesses remaining: %d\n", numGuesses);

    for (int i = 0; i < size; ++i)
    {
        if (numCharsFound == 0)
            printf("_");

        printf(" ");
    }

    printf("\n");
    if (showWR)
    {
        printf("You have %d possible words remaining\n", WR);
    }
}

void eatChars()
{
    char ch;
    scanf("%c", &ch);
    while (ch != '\n' && ch != '\0')
    {
        scanf("%c", &ch);
    }
}

Boolean getPreGameDecitions(int *lengthOfWords, int *numGuesses)
{
    char cRunningTot;
    printf("Please enter the length of a word you would like: ");
    scanf("%d", lengthOfWords);
    eatChars();
    while (*lengthOfWords <= 1 || *lengthOfWords >= 30)
    {
        printf("Please enter the length of a word you would like (must be from 2 to 29): ");
        scanf("%d", lengthOfWords);
        eatChars();
    }

    printf("Please enter the number of guesses you will be using (Must be grator then zero): ");
    scanf("%d", numGuesses);
    eatChars();
    while (*numGuesses < 1)
    {
        printf("Please enter the number of guesses you will be using (Must be grator then zero): ");
        scanf("%d", numGuesses);
        eatChars();
    }
    printf("Would you like a running total? (y/n)\n");
    scanf("%c", &cRunningTot);
    eatChars();
    while (cRunningTot != 'y' && cRunningTot != 'Y' && cRunningTot != 'n' && cRunningTot != 'N')
    {
        printf("What the heck is '%c'??\nWould you like a running total? (y/n)\n", cRunningTot);
        scanf("%c", &cRunningTot);
        eatChars();
    }
    if (cRunningTot == 'y' || cRunningTot == 'Y')
        return TRUE;

    return FALSE;
}

void printStatus(Status stat)
{
    if (stat == SUCCESS)
    {
        printf("SUCCESS\n");
    }
    else
    {
        printf("FAILURE\n");
    }
}

/*
OLD CODE


    printSV(superMaster);
    printf("\nbuilding new tree with guess 'a'\n");
    tNode *Tree = newGuessTree(superMaster, 'a');

    printTree(Tree);

    printf("\nThe Biggest Bucket in this tree is\n");
    SuperVector *biggestBucket = getBiggestBucket(Tree, -1, NULL);
    printSV(biggestBucket);

    tNode *toBeRemoved = Tree;

    Tree = newGuessTree(biggestBucket, 'p');
    softWhipeTree(toBeRemoved);
    printf("softWhiped old tree\n");

    printf("\nbuilding tree new tree with guess 'p'\n");
    printTree(Tree);

    printf("\nThe Biggest Bucket is\n");
    biggestBucket = getBiggestBucket(Tree, -1, NULL);
    printSV(biggestBucket);

    free(biggestBucket);


*/