#include <signal.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
	int32_t pipid[2];
	int32_t ex = 0;

	if (ex = pipe(pipid)) {
		fprintf(stderr, "Pipe failed: %d\n", ex);
		exit(ex);
	}

	pid_t pid1 = fork();

	if (pid1 > 0) {
		pid_t pid2 = fork();
		if (pid2 > 0) {
			close(pipid[0]);
			FILE *fs = fdopen(pipid[1], "w");
			fprintf(stdout, "P0 send pid(P2)\n");
			fprintf(fs, "%d", pid2);
			fclose(fs);
			int32_t procst = 0;
			fprintf(stdout, "P0 listen P2\n");
			waitpid(pid2, &procst, 0);
			fprintf(stdout, "P0 status(P2) = %d\n", procst);
		}
		if (pid2 == 0) {
			close(pipid[0]);
			close(pipid[1]);
			fprintf(stdout, "P2 started\n");
			while(true) {
				fprintf(stdout, "P2 running\n");
			}
		}
	}
	if (pid1 == 0) {
		pid_t pid2;
		fprintf(stdout, "P1 started\n");
		close(pipid[1]);
		FILE *fs = fdopen(pipid[0], "r");
		fscanf(fs, "%d", &pid2);
		fclose(fs);
		fprintf(stdout, "P1 recv pid(P2) = %d\n", pid2);
		sleep(5);
		fprintf(stdout, "P1 send kill(%d, SIGSTOP)\n", pid2);
		kill(pid2, SIGSTOP);
	}
}
