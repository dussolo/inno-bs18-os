#include <pthread.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	int32_t *cont;
	size_t counter;
	size_t size;
} buffer_t;

buffer_t *buffer_init(size_t size) {
	buffer_t *this = malloc(sizeof(buffer_t));

	this->size = size;
	this->cont = malloc(sizeof(int32_t) * size);
	this->counter = 0;

	return this;
}

void buffer_push(buffer_t *this, int32_t val) {
	if (this->counter >= this->size)
		return;

	this->cont[this->counter] = val;
	this->counter += 1;
}

int32_t buffer_pop(buffer_t *this) {
	if (this->counter <= 0)
		return 0;

	this->counter -= 1;

	return this->cont[this->counter];
}

bool buffer_empty(buffer_t *this) { return (this->counter <= 0); }

bool buffer_full(buffer_t *this) { return (this->counter >= this->size); }

buffer_t *buf;

bool someCond = false;

bool *adderCond;
bool *removerCond;

void wait(bool *cond) {
	*cond = false;
	while (!(*cond))
		;
}

void unlock(bool *cond) { *cond = true; }

void adder(void *a) {
	while (true) {
		if (someCond)
			break;
		int32_t item = rand() % 1024; // NOLINT(cert-msc30-c,cert-msc50-cpp)

		if (buffer_full(buf)) {
			wait(adderCond);
		}

		fprintf(stdout, "buf << %d\n", item);
		buffer_push(buf, item);

		if (!buffer_empty(buf)) {
			unlock(removerCond);
		}
	}
}

void remover(void *a) {
	while (true) {
		if (someCond)
			break;

		if (buffer_empty(buf)) {
			wait(removerCond);
		}

		int32_t item = buffer_pop(buf);
		fprintf(stdout, "buf >> %d\n", item);

		if (!buffer_full(buf)) {
			unlock(adderCond);
		}
	}
}

int main() {
	buf = buffer_init(1024);

	adderCond = malloc(sizeof(bool));
	removerCond = malloc(sizeof(bool));

	pthread_t adderT, removerT;

	pthread_create(&adderT, NULL, (void *(*)(void *))adder, NULL);
	pthread_create(&removerT, NULL, (void *(*)(void *))remover, NULL);

	pthread_join(adderT, NULL);
	pthread_join(removerT, NULL);
}
