#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

void swap(int32_t *a, int32_t *b) {
	int32_t buf = *a;
	*a = *b;
	*b = buf;
}

size_t qsortl_part(int32_t *ary, size_t lower, size_t upper) {
	int32_t pivot = ary[upper];
	size_t idx = lower;

	for (size_t i = idx; i <= upper; i++) {
		if (ary[i] < pivot) {
			swap(ary + i, ary + idx);
			idx += 1;
		}
	}

	swap(ary + idx, ary + upper);

	return idx;
}

void qsortl_sort_range(int32_t *ary, size_t lower, size_t upper) {
	if (lower < upper) {
		size_t part = qsortl_part(ary, lower, upper);
		qsortl_sort_range(ary, lower, part - 1);
		qsortl_sort_range(ary, part + 1, upper);
	}
}

void qsortl(int32_t *ary, size_t size) { qsortl_sort_range(ary, 0, size - 1); }

int32_t main() {
	size_t size;
	fscanf(stdin, "%ld", &size);

	int32_t *ary = malloc((size + 1) * sizeof(int32_t));
	for (size_t i = 0; i < size; i++)
		fscanf(stdin, "%d", ary + i);

	for (size_t i = 0; i < size; i++)
		fprintf(stdout, "%d ", ary[i]);
	fprintf(stdout, "\n");

	qsortl(ary, size);

	for (size_t i = 0; i < size; i++)
		fprintf(stdout, "%d ", ary[i]);
	fprintf(stdout, "\n");
}
