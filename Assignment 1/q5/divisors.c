#include <stdio.h>

int main() {
    int num;

    if (scanf("%d", &num) != 1) {
        return 1;
    }

    for (int i = 1; i <= num; i++) {
        if (num % i == 0) {
            printf("%d", i);
            if (i != num) {
                printf(" ");
            }
        }
    }
    printf("\n");
    
    return 0;
}