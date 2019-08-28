#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <float.h>

#define PRINT_VAR(fmt, a) printf("%lu : "fmt"\n", sizeof(a), (a))

int main() {
    int32_t intmax = INT32_MAX;
    int32_t intmin = INT32_MIN;
    float sfpmin = FLT_MIN;
    float sfpmax = FLT_MAX;
    double dfpmin = DBL_MIN;
    double dfpmax = DBL_MAX;

    PRINT_VAR("%d", intmax);
    PRINT_VAR("%d", intmin);
    PRINT_VAR("%f", sfpmax);
    PRINT_VAR("%f", sfpmin);
    PRINT_VAR("%f", dfpmax);
    PRINT_VAR("%f", dfpmin);
}