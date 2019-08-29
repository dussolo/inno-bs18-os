#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <float.h>

#define PRINT_VAR(fmt, a) printf("%lu : "fmt"\n", sizeof(a), (a))

int main() {
    int32_t intmax = INT32_MAX;
    int32_t intmin = INT32_MIN;
    float sfpmin = -FLT_MAX;
    float sfpmax = FLT_MAX;
    double dfpmin = -DBL_MAX;
    double dfpmax = DBL_MAX;

    PRINT_VAR("MAX %d", intmax);
    PRINT_VAR("MIN %d", intmin);
    PRINT_VAR("MAX %F", sfpmax);
    PRINT_VAR("MIN %F", sfpmin);
    PRINT_VAR("MAX %F", dfpmax);
    PRINT_VAR("MIN %F", dfpmin);
}