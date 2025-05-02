#include <stdio.h>


extern void __real_fred(int);
extern void __real_john(double);

void __wrap_fred(int arg) {
    __real_fred(arg);
}

void __wrap_john(double x) {
    __real_john(x);
}