#include <pthread.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

void thread(const pthread_t *id) {
	fprintf(stdout, "thread %lu entered\n", *id);
}

int main() {
	uint32_t n;
	fscanf(stdin, "%u", &n); // NOLINT(cert-err34-c)

	while (n > 0) {
		pthread_t id;

		pthread_create(&id, NULL, (void *(*)(void *))thread, &id);

		fprintf(stdout, "thread %lu started\n", id);

		n--;
	}
}
