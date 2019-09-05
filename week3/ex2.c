#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

void swap(int32_t *a, int32_t *b) {
	int32_t buf = *a;
	*a = *b;
	*b = buf;
}

void bubble_sort(int32_t *ary, size_t size) {
	for (size_t i = 0; i < size; i++) {
		for (size_t j = i + 1; j < size; j++) {
			if (ary[i] > ary[j]) {
				swap(ary + i, ary + j);
			}
		}
	}
}

int32_t main() {
	size_t size;
	fscanf(stdin, "%ld", &size);

	int32_t *ary = malloc((size + 1) * sizeof(int32_t));
	for (size_t i = 0; i < size; i++)
		fscanf(stdin, "%d", ary + i);

	for (size_t i = 0; i < size; i++)
		fprintf(stdout, "%d ", ary[i]);
	fprintf(stdout, "\n");

	bubble_sort(ary, size);

	for (size_t i = 0; i < size; i++)
		fprintf(stdout, "%d ", ary[i]);
	fprintf(stdout, "\n");
}
