#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>

int32_t main(int32_t argc, char **argv) {
	char fopm[] = "w";

	size_t firstarg = 0;
	size_t filecount = argc;

	if(argc > 2 && strcmp(argv[1], "-a") == 0) {
		strcpy(fopm, "a");
		firstarg = 1;
		filecount -= 1;
	}

	FILE **outfiles = calloc(argc, sizeof(FILE*));

	for(size_t i = firstarg + 1; i < argc; i++) {
		outfiles[i - firstarg] = fopen(argv[i], fopm);
		if(outfiles[i - firstarg] == NULL) perror(argv[i]);
	}

	outfiles[0] = stdout;

	while(1) {
		int8_t bytein = fgetc(stdin);
		if(bytein == EOF) break;

		for(size_t i = 0; i < argc; i++) {
			fputc(bytein, outfiles[i]);
		}
	}


	for(size_t i = 1; i < argc; i++) {
		fclose(outfiles[i]);
	}
}
