#include <signal.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

static void hdl(int sig) {
	fprintf(stderr, "Interrupted\n");
	exit(2);
}

int main(int argc, char *argv[]) {
	struct sigaction sact;
	memset(&sact, 0, sizeof(sact));

	sact.sa_handler = hdl;

	sigaction(SIGINT, &sact, NULL);

	while (true) {
	}
}
