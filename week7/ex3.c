#include <stdio.h>
#include <stdlib.h>

int main() {
	srand(time(NULL));

	printf("Enter original array size: ");
	int n1 = 0;
	scanf("%d", &n1);

	int *a1 = calloc(sizeof(int), n1 + 1);
	int i;
	for (i = 0; i < n1; i++) {
		a1[i] = 100;

		printf("%d ", a1[i]);
	}

	// User specifies the new array size, stored in variable n2.
	printf("\nEnter new array size: ");
	int n2 = 0;
	scanf("%d", &n2);

	// Dynamically change the array to size n2
	a1 = realloc(a1, sizeof(int) * (n2 + 1));

    if (n2 > n1) {
        for(int i = n1; i < n2; i++) {
            a1[i] = 0;
        }
    }

	for (i = 0; i < n2; i++) {
		printf("%d ", a1[i]);
	}
	printf("\n");

	// Done with array now, done with program :D

	return 0;
}
