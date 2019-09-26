#include <sys/types.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

void pread(int file) {
	FILE *stream;
	int c;
	stream = fdopen(file, "r");
	while ((c = fgetc(stream)) != EOF)
		putchar(c);
	fclose(stream);
}

int main() {
	int32_t pipid[2];

	if(pipe (pipid)) {
		fprintf(stderr, "Pipe failed to open\n");
		return 1;
	}

	pid_t pid = fork();

	if(pid == 0) {
		close(pipid[1]);
		pread(pipid[0]);
		return 0;
	} 
	if(pid < 0) {
		fprintf(stderr, "Proc failed to fork\n");
		return 2;
	} 
	close(pipid[0]);
	FILE *fd = fdopen(pipid[1], "w");
	fprintf(fd, "%s", "Hello, fork!\n");
	fclose(fd);
	return 0;
}
