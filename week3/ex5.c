#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct $node {
	struct $node *next;
	struct $node *prev;

	int32_t value;
} node;

typedef struct {
	node *head;
	node *tail;

	size_t size;
} list;

node *node_init(int32_t value) {
	node *this = malloc(sizeof(node));

	this->value = value;
	this->next = NULL;
	this->prev = NULL;

	return this;
}

list *list_init() {
	list *this = malloc(sizeof(list));

	this->size = 0;
	this->head = NULL;
	this->tail = NULL;

	return this;
}

void list_append(list *this, int32_t value) {
	this->size += 1;

	node *new = node_init(value);

	if (this->head == NULL) {
		this->tail = this->head = new;
	} else {
		this->tail->next = new;
		new->prev = this->tail;
		this->tail = new;
	}
}

void list_print(list *this, FILE *fd) {
	node *current = this->tail;

	while (current != NULL) {
		fprintf(fd, "%d ", current->value);
		current = current->prev;
	}
}

node *list_get_node(list *this, size_t index) {
	node *current = this->tail;

	if (index < 0)
		return NULL;

	while (current != NULL) {
		if (index == 0)
			return current;
		current = current->prev;
		index -= 1;
	}

	return NULL;
}

uint8_t list_drop(list *this, size_t index) {
	node *current = list_get_node(this, index);

	if(current == NULL) return 0;

	if(this->size == 1) {
		this->head = this->tail = NULL;
		this->size = 0;
	}

	if(index == 0) {
		current->prev->next = NULL;
		this->tail = current->prev;
	} else if (index == (this->size - 1)) {
		current->next->prev = NULL;
		this->head = current->next;
	} else {
		current->prev->next = current->next;
		current->next->prev = current->prev;
	}

	free(current);
	
	return 1;
}

int main() {
	list *lst = list_init();

	list_append(lst, 4);
	list_append(lst, 1);
	list_append(lst, 3);
	list_append(lst, 102);

	list_print(lst, stdout);
	fprintf(stdout, "\n");

	list_drop(lst, 3);

	list_print(lst, stdout);
	fprintf(stdout, "\n");
}
