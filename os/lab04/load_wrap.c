#include <stdio.h>
#include <math.h>

void bill(char *arg) {
    printf("bill: you passed %s\n", arg);
}

void sam(double x) {
    printf("sam: cos(%f) = %f\n", x, cos(x));
}