#include <stdio.h>

int main() {
    int num;
    char ch;

    printf("Enter input: ");

    while (1) {
        // Try to read an integer
        if (scanf("%d", &num) == 1) {
            printf("Read integer: %d\n", num);
        } 
        else if (scanf(" %c", &ch) == 1) { 
            // Read a non-integer character after skipping whitespace
            if ((ch >= '0' && ch <= '9')) {
                // This shouldn't happen, just a safety check
                printf("Unexpected number as char: %c\n", ch);
            } else {
                printf("Read non-integer: %c\n", ch);
            }
        } 
        else {
            break; // Stop reading on EOF
        }
    }

    return 0;
}