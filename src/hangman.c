/*
 * Hangman Game
 * Language: C
 * Description: Console-based word guessing game written in C.
 * Author: Hammad Qaiser
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>

#define MAX_TRIES 6
#define MAX_WORD_LENGTH 20

char* selectRandomWord();
void displayHangman(int);
void displayGuessedWord(char*);
int checkIfGuessed(char, char*);


int main()
{
    srand(time(NULL));
    int playAgain = 1;
    while (playAgain)
	{
        char* word = selectRandomWord();
        int wordLength = strlen(word);
        char guessedWord[MAX_WORD_LENGTH];
        char guessedLetters[MAX_WORD_LENGTH + 1] = {0}; // Array to store guessed letters
        int numGuessed = 0;

        int i;
        for (i = 0; i < wordLength; i++)
		{
            guessedWord[i] = '_';
        }
        guessedWord[i] = '\0';

        printf("\n \t\t\t\t Welcome to Hangman Game \n");
        printf("\n \t Rules : ");
		printf("\n\t - The game is case-sensitive.");
        printf("\n\t - Maximum 6 tries are allowed.");
        printf("\n\t - First letter of word is upper-case. Remaining's are lower-case.");
        printf("\n\t - No space is included.");
        printf("\n\t - Big Hint- Word is one of the names of our class-fellows.");

	    printf("\n\nLet's Play: \n");

        int tries = 0;
        while (tries < MAX_TRIES)
		{
            printf("\n");
            displayHangman(tries);
            printf("\n");
            displayGuessedWord(guessedWord);

            char guess;
            printf("\nEnter a letter: ");
            scanf(" %c", &guess);
            while (getchar() != '\n'); // Clear input buffer

            //guess = tolower(guess);

            // Check if the letter has already been guessed
            if (checkIfGuessed(guess, guessedLetters))
			{
                printf("\nYou have already guessed '%c'. Please try another letter.\n", guess);
                continue;
            }

            guessedLetters[numGuessed++] = guess;

            int found = 0;
            for (i = 0; i < wordLength; i++)
			{
                if (word[i] == guess && guessedWord[i] == '_')
				{
                    guessedWord[i] = guess;
                    found = 1;
                }
            }

            if (!found)
			{
                tries++;
                printf("\nIncorrect guess. Tries left: %d\n", MAX_TRIES - tries);
            }
			else
			{
                printf("\nGood guess.\n");
            }

            if (strcmp(guessedWord, word) == 0)
			{
                printf("\nCongratulations! You have guessed the word: %s\n", word);
                printf("\nNow, You are save from Hangman.\n");
                break;
            }
        }

        if (tries >= MAX_TRIES)
		{
            printf("\nGame Over! The word was: %s\n", word);
            printf("\nNow, You are fully hanged by a Hangman.\n");
            displayHangman(tries);
        }

        free(word);

        printf("\nWould you like to play Hangman again? \nPress 1 for Yes, 0 for No: ");
        scanf("%d", &playAgain);
        while (getchar() != '\n'); // Clear input buffer
    }

    printf("\nThanks for playing Hangman.\n");
    return 0;
}

char* selectRandomWord()
{
    char* wordList[] =
    {
        "Hammad", "Abdullah", "Ali", "Talha", "Noor",
        "Banoori", "Haider", "Omar", "Ahsan" , "Hania"
    }; // Add more words here

    int numWords = sizeof(wordList) / sizeof(wordList[0]);
    int randomIndex = rand() % numWords;

    char* selectedWord = (char*)malloc(MAX_WORD_LENGTH * sizeof(char));
    strcpy(selectedWord, wordList[randomIndex]);

    return selectedWord;
}

void displayHangman(int tries)
{
    const char* stages[] =
	{
        "  +---+	\n"
        "  |   |	\n"
        "  |    	\n"
        "  |    	\n"
        "  |    	\n"
        "  |    	\n"
        "=========\n",

        "  +---+	\n"
        "  |   |	\n"
        "  |   O	\n"
        "  |    	\n"
        "  |    	\n"
        "  |    	\n"
        "=========\n",

        "  +---+ 	\n"
        "  |   |	\n"
        "  |   O 	\n"
        "  |   | 	\n"
        "  |    	\n"
        "  |     	\n"
        "=========\n",

        "  +---+    \n"
        "  |   |    \n"
        "  |   O    \n"
        "  |  /|    \n"
        "  |        \n"
        "  |        \n"
        "=========\n",

        "  +---+	\n"
        "  |   |	\n"
        "  |   O	\n"
        "  |  /|\\	\n"
        "  |      	\n"
        "  |     	\n"
        "=========\n",

        "  +---+	\n"
        "  |   |	\n"
        "  |   O	\n"
        "  |  /|\\	\n"
        "  |  /   	\n"
        "       	\n"
        "=========\n",

        "  +---+	\n"
        "  |   |	\n"
        "  |   O	\n"
        "  |  /|\\  \n"
        "  |  / \\ 	\n"
        "  |    	\n"
        "=========\n"
    };

    printf("%s", stages[tries]);

}

void displayGuessedWord(char* guessedWord)
{
    printf("Word: ");
    int i;
    for ( i = 0; guessedWord[i] != '\0'; i++)
	{
        printf("%c ", guessedWord[i]);
    }
    printf("\n");
}

int checkIfGuessed(char guess, char* guessedLetters)
{
	int i;
    for ( i = 0; guessedLetters[i] != 0; i++)
	{
        if (guessedLetters[i] == guess)
		{
            return 1; // Letter already guessed
        }
    }
    return 0; // Letter not guessed
}

