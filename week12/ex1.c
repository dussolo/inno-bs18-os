#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

const size_t AMOUNT = 20;

int main() {
	FILE *fdin = fopen("/dev/random", "rb");
	if(fdin == NULL) perror("/dev/random: ");
	
	FILE *fdout = fopen("./ex1.txt", "wb");
	if(fdout == NULL) perror("./ex1.txt: ");

	for(size_t i = 0; i < AMOUNT; i++) {
		int32_t byte = fgetc(fdin);
		fputc(byte, fdout);
	}

	fclose(fdin);
	fclose(fdout);
}
