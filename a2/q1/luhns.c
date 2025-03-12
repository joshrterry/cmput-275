#include <stdio.h>
#include <stdlib.h>

// TEST CASE THAT FAILS: 123455

int main() {
    int sum = 0;
    int is_second = 0;
    int digit;
    long long card_no;

    scanf("%lld", &card_no);

    while (card_no > 0) {
        digit = card_no % 10; // Extract the last digit
        card_no /= 10; // Remove the last digit
        // printf("card_no: %lld, digit: %d\n", card_no, digit);

        if (is_second) {
            digit *= 2; // Double every second digit
            if (digit > 9) {
                digit -= 9; // Equivalent to adding individual digits (e.g., 12 → 1 + 2 = 3)
            }
        }

        sum += digit; // Add to total sum
        // printf("digit added: %d, newsum: %d\n", digit, sum);


        is_second = !is_second; // Toggle the flag for next iteration
    }
    sum -= digit;
    sum *= 9;

    // printf("%d\n", sum);
    // printf("%d\n", sum % 10);

    if (sum % 10 == digit) {
        printf("Valid\n");
    } else {
        printf("Invalid\n");
    }

    
}