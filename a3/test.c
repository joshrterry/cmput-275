#include <stdio.h>

void processCommands() {
    char command, target;
    int value;

    while (1) {
        command = getchar();  // Read the command
        
        if (command == EOF) {
            break; // Exit on EOF (Ctrl+D or Ctrl+Z)
        }

        if (command == 'q') {
            break; // Quit the program
        }
        else if (command == 'u' || command == 'i') {
            printf("Command: %c\n", command);
        }
        else if (command == 'p') {
            if (scanf(" %c", &target) == 1) {
                printf("Command: %c, Target: %c\n", command, target);
            }
        }
        else if (command == 'a' || command == 'r') {
            if (scanf(" %c %d", &target, &value) == 2) {
                printf("Command: %c, Target: %c, Value: %d\n", command, target, value);
            }
        }
        else if (command != '\n' && command != ' ') { // Ignore spaces & newlines
            printf("Invalid command: %c\n", command);
        }

        while (getchar() != '\n' && getchar() != EOF); // Clear input buffer
    }
}


int main() {
    processCommands();
    return 0;
}