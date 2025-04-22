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

void freeSet(struct Set *set) {
    if (!set) return;
    
    struct Node *current = set->head;
    while (current != NULL) {
        struct Node *next = current->next;
        free(current);
        current = next;
    }
    free(set);
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
                    ++cur_set->len;
                    return;
                } else if (cur_node->next == NULL) {
                    cur_node->next = new_elem;
                    ++cur_set->len;
                    return;
                }
                else if (cur_node->next->data > elem) {
                    new_elem->next = cur_node->next;
                    cur_node->next = new_elem;
                    ++cur_set->len;
                    return;
                }

                cur_node = cur_node->next;
            }
        } else {
            free(new_elem);  // Free the node if element already exists
        }
    }
}

void delete(struct Set *cur_set, int elem) {
    struct Node *prev_node = checkInSet(cur_set, elem);
    if (prev_node) {
        struct Node *to_delete;
        if (elem == cur_set->head->data) {
            to_delete = cur_set->head;
            cur_set->head = cur_set->head->next;
        } else {
            to_delete = prev_node->next;
            prev_node->next = prev_node->next->next;
        }
        free(to_delete);
        --cur_set->len;
    }
}

struct Set *setUnion(struct Set *set_1, struct Set *set_2) {
    struct Set *setUnion = mkset();

    struct Node *cur_node = set_1->head;
    while (cur_node != NULL) {
        add(setUnion, cur_node->data);
        cur_node = cur_node->next;
    }

    cur_node = set_2->head;
    while (cur_node != NULL) {
        add(setUnion, cur_node->data);
        cur_node = cur_node->next;
    }

    return setUnion;
}

struct Set *setIntersect(struct Set *set_1, struct Set *set_2) {
    struct Set *setIntersect = mkset();

    struct Node *cur_node = set_1->head;
    while (cur_node != NULL) {
        if (checkInSet(set_2, cur_node->data)) {
            add(setIntersect, cur_node->data);
        }
        cur_node = cur_node->next;
    }

    return setIntersect;
}

void processCommands(struct Set *x, struct Set *y) {
    char command, target;
    int value;

    while (1) {
        int result = scanf(" %c", &command);

        if (result == EOF) {
            break;
        }

        if (command == 'q') {
            return;
        } else if (command == 'u') {
            struct Set *union_set = setUnion(x, y);
            printSet(union_set);
            freeSet(union_set);
        } else if (command == 'i') {
            struct Set *intersect_set = setIntersect(x, y);
            printSet(intersect_set);
            freeSet(intersect_set);
        } else if (command == 'p') {
            if (scanf(" %c", &target) == 1) {
                if (target == 'x') {
                    printSet(x);
                } else if (target == 'y') {
                    printSet(y);
                }
            }
        } else if (command == 'a') {
            if (scanf(" %c %d", &target, &value) == 2) {
                if (target == 'x') {
                    add(x, value);
                } else if (target == 'y') {
                    add(y, value);
                }
            }
        } else if (command == 'r') {
            if (scanf(" %c %d", &target, &value) == 2) {
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

    // Free memory before exiting
    freeSet(x);
    freeSet(y);

    return 0;
}