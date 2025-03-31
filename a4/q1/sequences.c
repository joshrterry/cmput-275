#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INITIAL_CAPACITY 10

typedef struct {
    char *op;  // Operator ("add", "sub", "mul", "div")
    int value; // Operand
} Operation;

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <initial_value>\n", argv[0]);
        return 1;
    }

    int current = atoi(argv[1]);
    int capacity = INITIAL_CAPACITY;
    Operation *operations = malloc(capacity * sizeof(Operation));
    if (!operations) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }
    int op_count = 0;

    char *input = NULL;
    size_t len = 0;
    while (getline(&input, &len, stdin) != -1) {
        char *token = strtok(input, " \t\n");
        while (token) {
            if (strcmp(token, "n") == 0) {
                int next = current;
                for (int i = 0; i < op_count; i++) {
                    if (strcmp(operations[i].op, "add") == 0) {
                        next += operations[i].value;
                    } else if (strcmp(operations[i].op, "sub") == 0) {
                        next -= operations[i].value;
                    } else if (strcmp(operations[i].op, "mul") == 0) {
                        next *= operations[i].value;
                    } else if (strcmp(operations[i].op, "div") == 0) {
                        if (operations[i].value != 0) {
                            next /= operations[i].value;
                        } else {
                            fprintf(stderr, "Error: Division by zero\n");
                            free(input);
                            for (int j = 0; j < op_count; j++) free(operations[j].op);
                            free(operations);
                            return 1;
                        }
                    }
                }
                printf("%d\n", next);
                current = next;
            } else {
                char *num_str = strtok(NULL, " \t\n");
                if (!num_str) {
                    fprintf(stderr, "Invalid input\n");
                    break;
                }
                int num = atoi(num_str);
                
                if (op_count >= capacity) {
                    capacity *= 2;
                    Operation *new_operations = realloc(operations, capacity * sizeof(Operation));
                    if (!new_operations) {
                        fprintf(stderr, "Memory reallocation failed\n");
                        break;
                    }
                    operations = new_operations;
                }
                
                operations[op_count].op = strdup(token);
                operations[op_count].value = num;
                op_count++;
            }
            token = strtok(NULL, " \t\n");
        }
    }
    
    free(input);
    for (int i = 0; i < op_count; i++) free(operations[i].op);
    free(operations);
    return 0;
}