#include <stdio.h>
#include <stdlib.h>

int main() {
    int S;
    int A;
    scanf("%d %d", &S, &A);

    // use malloc to store allocated region in memory and initialize values
    int *alloced_memory = (int *)malloc(A * sizeof(int));
    for (int i = 0; i < A; i++) {
        scanf("%d", &alloced_memory[i]);
    }

    int current_ptr = S;
    int offset_idx = 0; // new indexing value where 0 is the first value in allocated memory region
    int visited[A];

    for (int i = 0; i < A; i++) {
        visited[i] = 0;
    }

    while (1) {
        offset_idx = current_ptr - S;

        // if offset_idx outside expected region, break
        if (offset_idx < 0 || offset_idx >= A) {
            break;
        }

        if (visited[offset_idx]) {
            printf("There was a cycle\n");
            break;
        }

        visited[offset_idx] = 1; // keep track of addresses visited

        int value = alloced_memory[offset_idx];

        if (value < 0) {
            printf("%d\n", value);
            break;
        }

        current_ptr = value;

    }

    free(alloced_memory);
    return 0;

}