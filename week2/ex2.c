#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>

const char *strrev(char *input) {
    size_t inplen = strlen(input);

    char *result = malloc((inplen + 1) * sizeof(char));
    
    size_t pos = 0;
    for(int i = inplen - 1; i >= 0; i--) {
        result[pos++] = input[i];
    }
    result[pos] = '\0';

    return result;
}

int main() {
    char buf[255];
    fscanf(stdin, "%s", buf);
    const char *result = strrev(buf);
    fprintf(stdout, "%s\n", result);
}