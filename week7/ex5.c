#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
	char **s = malloc(sizeof(char*));
	
    char foo[] = "Hello World";
	
    *s = calloc(sizeof(char), strlen(foo));
    strcpy(*s, foo);
	
    printf("s is %s\n", *s);
	
    s[0] = calloc(sizeof(char), strlen(foo));
    strcpy(s[0], foo);
	
    printf("s[0] is %s\n", s[0]);
	
    return 0;
}