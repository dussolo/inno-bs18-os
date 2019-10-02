#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stddef.h>


int main() {
    uint32_t *ary;
    size_t n;

    fprintf(stdout, "N: ");
    fscanf(stdin, "%llu", &n);

    ary = calloc(sizeof(uint32_t), n + 1);

    for(int i = 0; i < n; i++) {
        ary[i] = i;
    }

    for(int i = 0; i < n; i++) {
        fprintf(stdout, "%d ", ary[i]);
    }

    fprintf("\n");

    free(ary);
}