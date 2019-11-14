#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define NPROC 5
#define NRES 3

typedef struct {
	int exist[NRES];
	int available[NRES];
	int alloc[NPROC][NRES];
	int req[NPROC][NRES];
} InputData;

InputData parseInput(FILE *fin) {
	InputData data;

	for (size_t i = 0; i < NRES; i++) {
		fscanf(fin, "%d", data.exist + i);
	}
	for (size_t i = 0; i < NRES; i++) {
		fscanf(fin, "%d", data.available + i);
	}
	for (size_t i = 0; i < NPROC; i++) {
		for (size_t j = 0; j < NRES; j++) {
			fscanf(fin, "%d", data.alloc[i] + j);
		}
	}
	for (size_t i = 0; i < NPROC; i++) {
		for (size_t j = 0; j < NRES; j++) {
			fscanf(fin, "%d", data.req[i] + j);
		}
	}
}

uint8_t canFinalize(int process, InputData data) {
	for (size_t i = 0; i < NRES; i++) {
		if (data.req[process][i] > data.available[i]) {
			return 0;
		}
	}

	return 1;
}

void finalize(int process, InputData data) {
	for (size_t i = 0; i < NRES; i++) {
		data.available[i] += data.alloc[process][i];
	}
}

uint8_t detect(InputData data, uint8_t *deadlocked) {
	int finalized = 0;
	int finish_algorithm = 0;
	for (size_t i = 0; i < NPROC; i++) {
		deadlocked[i] = 1;
	}
	while (!finish_algorithm) {
		finish_algorithm = 1;
		for (size_t i = 0; i < NPROC; i++) {
			if (canFinalize(i, data) && deadlocked[i]) {
				finalize(i, data);
				deadlocked[i] = 0;
				finalized += 1;
				finish_algorithm = 0;
			}
		}
	}
	return finalized != NPROC;
}

int main() {
	FILE *fin = fopen("input.txt", "r");

	InputData data = parseInput(fin);

	uint8_t deadlocked[NPROC];
	uint8_t detected = detect(data, deadlocked);

	if (!detected) {
		printf("No deadlocks detected.\n");
	} else {
		printf("Deadlocks detected in: \n");
		for (size_t i = 0; i < NPROC; i++) {
			if (deadlocked[i]) {
				printf("  proc #%d\n", i);
			}
		}
	}
}
