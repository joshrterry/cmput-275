#include <stdio.h>
#include <stdlib.h>


// node for linked list
struct Node {
    int data;
    struct Node *next;
};

struct List {
    struct Node *head;
    size_t len;
};

struct List *mkList() {
    struct List *ret = malloc(sizeof(struct List));
    ret->head = NULL;
    ret->len = 0;
    return ret;
};

struct List *push(struct List *l, int val) {
    struct Node *node = malloc(sizeof(struct Node));
    node->data = val;
    node->next = l->head;
    l->head = node;
    l->len += 1;
    return l;
}

int pop(struct List *l) {
    struct Node *tmp = l->head;
    int retval = tmp->data;
    l->head = l->head->next;
    free(tmp);
    l->len = l->len-1;
    return retval;
}

int main() {
    struct List *ll = mkList();

    int num;
    char ch;

    while (1) {
        // Skip leading whitespace and attempt to read an integer
        if (scanf(" %d", &num) == 1) {
            push(ll, num);
        } 
        // If not a number, try to read a character (operator)
        else if (scanf(" %c", &ch) == 1) {  
            if (ch == '\n') {
                continue;  // Ignore newlines and keep processing input
            }
            
            int b = pop(ll);
            int a = pop(ll);
            int result = -1;

            switch (ch) {
                case 'p':
                    result = a + b;
                    break;
                case 's':
                    result = a - b;
                    break;
                case '*':
                    result = a * b;
                    break;
                case '/':
                    if (b == 0) {
                        printf("Error: Division by zero\n");
                        exit(1);
                    }
                    result = a / b;
                    break;
                default:
                    printf("Invalid operator: %c\n", ch);
                    exit(1);
            }

            push(ll, result);
        } 
        else {
            break; // Stop reading on EOF
        }
    }

    printf("%d\n", pop(ll));
    free(ll);
}