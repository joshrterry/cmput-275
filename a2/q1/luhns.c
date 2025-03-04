#include <stdio.h>
#include <stdlib.h>

// TEST CASE THAT FAILS: 123455

int main() {
    int sum = 0;
    int pos = 0; // position from right (1-based)
    int check_digit = -1;
    char ch;
    
    while ((ch = getchar()) >= '0' && ch <= '9') {
        int digit = ch - '0'; // convert from char to int
        printf("Digit looking at now: %d\n", digit);

        if (check_digit == -1) {
            check_digit = digit; // Store the last digit as check digit
        } else {
            pos++;
            if (pos % 2 == 1) { // Double every second digit from the right
                digit *= 2;
                if (digit >= 10) {
                    digit -= 9;
                }
            }
            printf("Digit to add: %d\n", digit);
            sum += digit;
            printf("New sum: %d\n", sum);
        }
    }
    
    sum *= 9;
    if (sum % 10 == check_digit) {
        printf("Valid\n");
    } else {
        printf("Invalid\n");
    }
    
    return 0;
}
