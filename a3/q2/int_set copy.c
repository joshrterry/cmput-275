#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node {
    int data;
    struct Node *next;
};

struct Set {
    struct Node *head;
    size_t len;
};

struct Set *mkset() {
    struct Set *ret = malloc(sizeof(struct Set));
    ret->head = NULL;
    ret->len = 0;
    return ret;
}

struct Node *mkNode() {
    struct Node *ret = malloc(sizeof(struct Node));
    ret->data = -1;
    ret->next = NULL;
    return ret;
}

struct Node *checkInSet(struct Set *cur_set, int targ) {
    struct Node *prev_node = cur_set->head;
    struct Node *cur_node = cur_set->head;
    while (cur_node != NULL) {
        if (cur_node->data == targ) {
            return prev_node;
        }
        prev_node = cur_node;
        cur_node = cur_node->next;
    }
    return NULL;
}

void printSet(struct Set *cur_set) {
    struct Node *cur_node = cur_set->head;
    while (cur_node != NULL) {
        printf("%d", cur_node->data);
        if (cur_node->next == NULL) {
            printf("\n");
        } else {
            printf(" ");
        }
        cur_node = cur_node->next;
    }
}


void add(struct Set *cur_set, int elem) {
    struct Node *cur_node = cur_set->head;
    struct Node *new_elem = mkNode();
    new_elem->data = elem;    
    
    if (cur_set->len == 0) {
        cur_set->head = new_elem;
        ++cur_set->len;
    } else {
        if (!checkInSet(cur_set, elem)) {
            while (cur_node != NULL) {
                if (cur_node->data > elem) {
                    new_elem->next = cur_set->head;
                    cur_set->head = new_elem;
                    return;
                } else if (cur_node->next == NULL) {
                    cur_node->next = new_elem;
                    return;
                }
                else if (cur_node->next->data > elem) {
                    new_elem->next = cur_node->next;
                    cur_node->next = new_elem;
                    return;
                }

                cur_node = cur_node->next;
            }
            ++cur_set->len;
        }
    }
}

void delete(struct Set *cur_set, int elem) {
    struct Node *prev_node = checkInSet(cur_set, elem);
    if (prev_node) {
        if (elem == cur_set->head->data) {
            cur_set->head = cur_set->head->next;
        } else {
            prev_node->next = prev_node->next->next;
        }
        // if elem is head, bypass head

        // else, ckeck cur_node->next
    }
}

struct Set *setUnion(struct Set *set_1, struct Set *set_2) {
    struct Set *setUnion = mkset();

    struct Node *cur_node = set_1->head;
    while (cur_node != NULL) {
        add(setUnion, cur_node->data);  // Copy elements from set_1
        cur_node = cur_node->next;
    }

    cur_node = set_2->head;
    while (cur_node != NULL) {
        add(setUnion, cur_node->data);  // Copy elements from set_2
        cur_node = cur_node->next;
    }

    return setUnion;
}

struct Set *setIntersect(struct Set *set_1, struct Set *set_2) {
    struct Set *setIntersect = mkset(); // Create a new empty set

    struct Node *cur_node = set_1->head;
    while (cur_node != NULL) {
        if (checkInSet(set_2, cur_node->data)) {
            add(setIntersect, cur_node->data); // Add only if present in both sets
        }
        cur_node = cur_node->next;
    }

    return setIntersect;
}

void processCommands(struct Set *x, struct Set *y) {
    char command, target;
    int value;

    while (1) {
        // Read the first command
        int result = scanf(" %c", &command);

        // Exit on EOF
        if (result == EOF) {
            break;
        }

        if (command == 'q') {
            return; // Quit program
        } else if (command == 'u') {
            printSet(setUnion(x, y));
        } else if (command == 'i') {
            printSet(setIntersect(x, y));
        } else if (command == 'p') {
            if (scanf(" %c", &target) == 1) { // Read set name (x or y)
                if (target == 'x') {
                    printSet(x);
                } else if (target == 'y') {
                    printSet(y);
                }
            }
        } else if (command == 'a') {
            if (scanf(" %c %d", &target, &value) == 2) { // Read set and value
                if (target == 'x') {
                    add(x, value);
                } else if (target == 'y') {
                    add(y, value);
                }
            }
        } else if (command == 'r') {
            if (scanf(" %c %d", &target, &value) == 2) { // Read set and value
                if (target == 'x') {
                    delete(x, value);
                } else if (target == 'y') {
                    delete(y, value);
                }
            }
        } else {
            printf("Invalid command: %c\n", command);
        }
    }
}


int main() {
    struct Set *x = mkset();
    struct Set *y = mkset();

    processCommands(x, y);

}