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
        // Try to read an integer
        if (scanf("%d", &num) == 1) {
            push(ll, num);
        } 
        else if (scanf(" %c", &ch) == 1) {             

            // Read a non-integer character after skipping whitespace
            if ((ch >= '0' && ch <= '9')) {
                // This shouldn't happen, just a safety check
                printf("Unexpected number as char: %c\n", ch);
            } else {
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
                        result = a / b;
                        break;
                    // default:
                    //     printf("Invalid operator detected.\n");
                }
                // printf("%d", result);
                
                push(ll, result);


            }
        } 
         
        else {
            break; // Stop reading on EOF
        }
    }

    printf("\n%d\n", pop(ll));

}