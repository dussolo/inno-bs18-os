#include <dirent.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>

#define PATH "tmp/"

int main() {
	DIR *dir = opendir(PATH);

	if (dir == NULL) {
		perror("Cannot open '"PATH"'");
		exit(errno);
	}

	__ino_t *inodes = malloc(sizeof(__ino_t) * 10);
	uint32_t *file_count = malloc(sizeof(uint32_t) * 10);

	char ***names = malloc(sizeof(char **) * 10);
	for (uint32_t i = 0; i < 10; i++) {
		names[i] = malloc(sizeof(char *) * 10);
		file_count[i] = 0;
	}

	struct dirent *dent;
	uint32_t i = 0;

	while ((dent = readdir(dir)) != NULL) {
		uint32_t found = 0;
		for (uint32_t j = 0; j < 10 && found == 0; j++) {
			if (inodes[j] == dent->d_ino) {
				found = 1;
				names[j][file_count[j]] = dent->d_name;
				file_count[j]++;
			}
		}

		if (found == 0) {
			inodes[i] = dent->d_ino;
			names[i][file_count[i]] = dent->d_name;
			file_count[i]++;
			i++;
		}
	}

	for (uint32_t i = 0; i < 10; i++) {
		if (file_count[i] > 1) {
			fprintf(stdout, "%lu\n", inodes[i]);
			for (uint32_t j = 0; j < file_count[i]; j++) {
				fprintf(stdout, " |- %s\n", names[i][j]);
			}
			fprintf(stdout, "\n");
		}
	}
}
