#include <stdio.h>
#include <string.h>

const char * const GREEN = "\x1b[32m";
const char * const YELLOW = "\x1b[33m";
const char * const WHITE = "\x1b[0m";
const char *current = WHITE;

void setColour(const char *colour) {
    if (current == colour) return;
    printf("%s", colour);
    current = colour;
}

int main(int argc, char **argv) {
    if (argc != 2) {
        printf("Usage: %s word\n", argv[0]);
        return 1;
    }

    char *theWord = argv[1];  // secret word from command-line argument
    int wordLen = strlen(theWord);
    char guess[20];  // words are at most 12 chars, so include a small buffer past that
    int attempts = 0;

    while (attempts < 6) {
        setColour(WHITE);
        printf("Enter guess: ");
        scanf("%s", guess);

        if (strlen(guess) != wordLen) {
            printf("Guess must be exactly %d letters.\n", wordLen);
            continue;
        }

        int correct[20] = {0};  // tracks green letters
        int counts[26] = {0};   // letter frequency in secret word

        // first time around, mark correct (green) letters
        for (int i = 0; i < wordLen; i++) {
            if (theWord[i] == guess[i]) {
                correct[i] = 2;  // mark as green
            } else {
                counts[theWord[i] - 'a']++;  // count occurrences of remaining letters
            }
        }

        // second time around, determine yellow and white letters
        for (int i = 0; i < wordLen; i++) {
            if (correct[i] == 2) {
                setColour(GREEN);
            } else if (counts[guess[i] - 'a'] > 0) {
                setColour(YELLOW);
                counts[guess[i] - 'a']--;  // reduce available occurrences
            } else {
                setColour(WHITE);
            }
            printf("%c", guess[i]);
        }

        // print newline
        printf("\n");

        // check if the word is guessed correctly
        if (strcmp(guess, theWord) == 0) {
            setColour(WHITE);
            printf("Finished in %d guesses\n", attempts + 1);
            return 0;
        }

        attempts++;
    }

    setColour(WHITE);
    printf("Failed to guess the word: %s\n", theWord);
    return 0;
}