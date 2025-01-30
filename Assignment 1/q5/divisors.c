#include <stdio.h>

int main() {
    int num;

    if (scanf("%d", &num) != 1) {
        return 1;
    }

    int first = 1; // check if first divisor, then don't print leading space
    for (int i = 1; i <= num; i++) {
        if (num % i == 0) {
            if (!first) {
                printf(" ");
            }
            printf("%d", i);
            first = 0;
        }
    }
    printf("\n");
    
    return 0;
}