#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

typedef struct {
	void *ptr;
	size_t size;
} FMapped;

int fmap(const char *filename, size_t force_size, FMapped *ret) {
	int fd = open(filename, O_RDWR | O_CREAT, 0666);
	if (fd < 0) {
		perror(filename);
		return fd;
	}
	size_t fsize = force_size;
	if (!fsize) {
		struct stat file_stat = {};
		if (fstat(fd, &file_stat)) {
			perror(filename);
			return -1;
		}
		fsize = file_stat.st_size;
	} else {
		ftruncate(fd, fsize);
	}

	char *buf = mmap(NULL, fsize, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	if (!buf) {
		perror("mmap");
		return -1;
	}

	ret->ptr = buf;
	ret->size = fsize;

	return 0;
}

int main() {
	FMapped *f1 = malloc(sizeof(FMapped));
	FMapped *f2 = malloc(sizeof(FMapped));

	int32_t err = fmap("./ex1.txt", 0, f1);

	if (err) {
		perror("fmap");
		return err;
	}

	err = fmap("./ex1.memcpy.txt", f1->size, f2);

	if (err) {
		perror("fmap");
		return err;
	}

	memcpy(f2->ptr, f1->ptr, f1->size);

	err = msync(f1->ptr, f1->size, MS_SYNC);

	if (err) {
		perror("memsync");
		return err;
	}

	err = msync(f2->ptr, f2->size, MS_SYNC);

	if (err) {
		perror("memsync");
		return err;
	}

	return 0;
}
