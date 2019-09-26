#include <signal.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
	pid_t pid = fork();
	if(pid == 0) {
		while(true) {
			fprintf(stdout, "%s\n", "I'm alive!");
			sleep(1);
		}
	} else {
		sleep(10);
		kill(pid, SIGTERM);
	}
}
