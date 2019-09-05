#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct $node {
	struct $node *next;
	int32_t value;
} node;

typedef struct {
	node *head;
	size_t size;
} list;

node *node_init(int32_t value) {
	node *this = malloc(sizeof(node));

	this->value = value;
	this->next = NULL;

	return this;
}

void node_print(node *this, FILE *fd) {
	if (this == NULL)
		return;

	node_print(this->next, fd);

	fprintf(fd, "%d ", this->value);
}

list *list_init() {
	list *this = malloc(sizeof(list));

	this->size = 0;
	this->head = NULL;

	return this;
}

void list_append(list *this, int32_t value) {
	this->size += 1;

	node *new = node_init(value);

	new->next = this->head;
	this->head = new;
}

void list_print(list *this, FILE *fd) {
	if (this->head != NULL)
		node_print(this->head, fd);
}

uint8_t list_drop(list *this, size_t index) {
	if (index > this->size || index < 0) {
		return 0;
	}

	if (index == (this->size - 1)) {
		this->head = this->head->next;
		this->size -= 1;

		return 1;
	} else {
		node *prev = this->head;

		for (size_t i = 0; i < (this->size - index - 2); i++) {
			prev = prev->next;
		}

		prev->next = prev->next->next;
		this->size -= 1;

		return 1;
	}
}

int main() {
	list *lst = list_init();

	list_append(lst, 4);
	list_append(lst, 1);
	list_append(lst, 3);
	list_append(lst, 102);

	list_print(lst, stdout);
	fprintf(stdout, "\n");

	list_drop(lst, 1);

	list_print(lst, stdout);
	fprintf(stdout, "\n");
}
