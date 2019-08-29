#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILLER_CHAR '*'

const char *fill(size_t req_size, char filler) {
	char *result = malloc((req_size + 1) * sizeof(char));

	for (int i = 0; i < req_size; i++) {
		result[i] = filler;
	}

	result[req_size] = '\0';

	return result;
}

const char *pad_center(const char *input, size_t req_size) {
	size_t has_size = strlen(input);
	if (has_size >= req_size)
		return input;
	size_t pad_size = (req_size - has_size) / 2;

	char *result = malloc((req_size + 1) * sizeof(char));
	char *pad = malloc((pad_size + 1) * sizeof(char));

	for (int i = 0; i < pad_size; i++) {
		pad[i] = ' ';
	}
	pad[pad_size] = '\0';

	strcpy(result, pad);
	strcat(result, input);
	strcat(result, pad);

	return result;
}

int main(int argc, char **argv) {
	size_t size = 0;
	if (argc > 1)
		sscanf(argv[1], "%lu", &size);

	for (int i = 1; i < (2 * size); i += 2) {
		const char *line = pad_center(fill(i, FILLER_CHAR), (2 * size - 1));
		fprintf(stdout, "%s\n", line);
	}
}