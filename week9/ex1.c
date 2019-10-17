#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <limits.h>

typedef struct {
	uint8_t ts;
	int32_t link;
	int32_t free;
} Frame;

int32_t findFree(Frame *ary, size_t size) {
	for (size_t i = 0; i < size; i++) {
		if (ary[i].free == 1) {
			return i;
		}
	}
	return -1;
}

int32_t findSameLink(int32_t link, Frame *ary, size_t size) {
	for (size_t i = 0; i < size; i++) {
		if (ary[i].link == link) {
			return i;
		}
	}
	return -1;
}

int32_t minTS(Frame *ary, size_t size) {
	int32_t idx = 0;
	int32_t min = ary[0].ts;

	for (size_t i = 0; i < size; i++) {
		if (ary[i].ts < min) {
			idx = i;
			min = ary[i].ts;
		}
	}
	return idx;
}

int32_t setPage(int32_t idx, int32_t link, Frame *ary, size_t size) {
	ary[idx].ts = ary[idx].ts >> 1 | 128;
	ary[idx].link = link;

	for (size_t i = 0; i < size; i++) {
		if (i != idx) {
			ary[i].ts = ary[i].ts >> 1;
		}
	}
	return 0;
}

int32_t handleLink(int32_t link, Frame *ary, size_t size) {
	int32_t res = 1;
	int32_t idx;

	int32_t same = findSameLink(link, ary, size);
	if (same != -1) {
		idx = same;
		res = 0;
	} else {
		int32_t free = findFree(ary, size);
		if (free != -1) {
			idx = free;
			ary[free].free = 0;
		} else {
			idx = minTS(ary, size);
		}
	}

	setPage(idx, link, ary, size);
	return res;
}

int32_t main(int32_t argc, char **argv) {
	int32_t frameCount = atoi(argv[1]);
	Frame *pages = malloc(sizeof(Frame) * frameCount);
	int32_t misses = 0;

	FILE *file;
	file = fopen("input.txt", "r");

	for (int32_t i = 0; i < frameCount; i++) {
		pages[i].ts = (uint8_t)0;
		pages[i].link = -1;
		pages[i].free = 1;
	}

	int32_t buffer;
	int32_t len = 0;
	while (fscanf(file, "%d", &buffer) == 1) {
		len++;
		misses =
			misses + handleLink(buffer, pages, frameCount);
	}

	double missRatio = (int32_t)((1.e4 * misses) / len) / 100.;

	fprintf(stdout, "%d %d\n", misses, len);
	fprintf(stdout, "miss = %f%%\n", missRatio);
	fprintf(stdout, "hit = %f%%\n", 100. - missRatio);
	return 0;
}
