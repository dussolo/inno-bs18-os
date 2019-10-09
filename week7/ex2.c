#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>

int main() {
	char *ptrs[10];
	for(uint16_t i = 0u; i < 10u; i++) {
		ptrs[i] = malloc(1024 * 1024 * 10);
		memset(ptrs[i], 0, 1024 * 1024 * 10);
		sleep(1);
	}

}
