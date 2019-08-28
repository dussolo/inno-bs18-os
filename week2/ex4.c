#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

void swap(int32_t *a, int32_t *b) {
    int32_t buf = *a;
    *a = *b;
    *b = buf;
}

int main() {
    int32_t a = 0, b = 0;
    
    fprintf(stdout, "a = ");
    fscanf(stdin, "%d", &a);

    fprintf(stdout, "b = ");
    fscanf(stdin, "%d", &b);

    swap(&a, &b);

    printf("a = %d ; b = %d\n", a, b);
}