#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>


void *nrealloc(void *ptr, size_t size_n) {
	if (size_n <= 0) {
		free(ptr);
		return NULL;
	}

	void *new_ptr = malloc(size_n);
	if (ptr == NULL) {
		return new_ptr;
	}

	memcpy(new_ptr, ptr, size_n);

	return new_ptr;
}

int main() {
	int *ary = calloc(10, sizeof(int));

	for (int i = 0; i < 10; i++) {
		fprintf(stdout, "%d ", ary[i]);
	}

	fprintf(stdout, "\n");

	nrealloc(ary, 12 * sizeof(int));

	for (int i = 0; i < 12; i++) {
		printf(stdout, "%d ", ary[i]);
	}

	fprintf(stdout, "\n");
}