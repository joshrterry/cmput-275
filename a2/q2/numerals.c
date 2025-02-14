#include <stdio.h>
#include <string.h>

// function to get the integer value of a roman numeral
int romanValue(char c) {
    switch (c) {
        case 'I': return 1;
        case 'V': return 5;
        case 'X': return 10;
        case 'L': return 50;
        case 'C': return 100;
        case 'D': return 500;
        case 'M': return 1000;
        default: return 0; // defualt value for invalid characters
    }
}

// function to convert roman numeral string to integer
int romanToInt(const char *s) {
    int total = 0;
    int length = strlen(s);

    for (int i = 0; i < length; i++) {
        int current = romanValue(s[i]);
        int next = (i + 1 < length) ? romanValue(s[i + 1]) : 0;

        // if the next value is greater, subtract current value, else add it
        if (current < next) {
            total -= current;
        } else {
            total += current;
        }
    }
    
    return total;
}

int main() {
    char roman[20]; // buffer for Roman numeral input
    printf("Enter Roman numeral: ");
    scanf("%s", roman);

    int result = romanToInt(roman);
    printf("Integer value: %d\n", result);

    return 0;
}