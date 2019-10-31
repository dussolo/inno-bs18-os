#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>

const char *FNAME = "./ex1.txt";
const char *TSTRING = "This is a nice day";

typedef struct stat FStat;

int main() {
	int32_t err;
	int32_t fd = open(FNAME, O_RDWR);

	if (fd < 0) {
		perror(FNAME);
		return fd;
	}

	FStat stat = {};

	err = fstat(fd, &stat);

	if (err) {
		char buf[255];

		sprintf(buf, "fstat %s", FNAME);

		perror(buf);

		return err;
	}

	size_t fsize = stat.st_size;

	char *buf = (char *)malloc(fsize);

	buf = mmap(buf, fsize, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

	if (!buf) {
		perror("memmap");
		return -1;
	}

	strcpy(buf, TSTRING);

	for (int32_t i = strlen(TSTRING); i < fsize; i++) {
		buf[i] = ' ';
	}

	err = msync(buf, fsize, MS_SYNC);

	if (err) {
		perror("memsync");
		return err;
	}

	err = munmap(buf, fsize);

	if (err) {
		perror("memunmap");
		return err;
	}

	return 0;
}
