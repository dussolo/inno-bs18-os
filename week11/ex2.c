#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

const char *TSTRING = "Hello";

int main() {
	int i;

	if (setvbuf(stdout, 0, _IOLBF, 0)) {
		perror("setvbuf");
		return -1;
	}

	for (i = 0; TSTRING[i]; i++) {
		printf("%c", TSTRING[i]);
		sleep(1);
	}
}
