#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <timeout>\n", argv[0]);
        return 1;
    }

    char *end = NULL;
    errno = 0;
    long val = strtol(argv[1], &end, 10);
    if (errno || end == argv[1] || *end != '\0' || val <= 0 || val > INT_MAX) {
        fprintf(stderr, "Invalid timeout value\n");
        return 1;
    }

    unsigned int timeout = (unsigned int)val;
    pid_t pid = getpid();
    int counter = 0;

    for (;;) {
        if (printf("%d: %d\n", pid, counter) < 0) {
            perror("printf");
            return 1;
        }
        fflush(stdout);
        ++counter;

        unsigned int remaining = timeout;
        while (remaining) remaining = sleep(remaining);
    }
}
