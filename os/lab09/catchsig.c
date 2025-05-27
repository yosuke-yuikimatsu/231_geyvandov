#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <errno.h>
#include <limits.h>
#include <unistd.h>

typedef struct { const char *name; int num; } SigMap;
static const SigMap sigs[] = {
    {"HUP", SIGHUP},   {"INT", SIGINT},   {"QUIT", SIGQUIT}, {"ILL", SIGILL},
    {"ABRT", SIGABRT}, {"FPE", SIGFPE},   {"SEGV", SIGSEGV},
    {"PIPE", SIGPIPE}, {"ALRM", SIGALRM}, {"TERM", SIGTERM}, {"USR1", SIGUSR1},
    {"USR2", SIGUSR2}, {"CHLD", SIGCHLD}, {"CONT", SIGCONT},
    {"TSTP", SIGTSTP}, {"TTIN", SIGTTIN}, {"TTOU", SIGTTOU}
};

static void handler(int sig) {
    const char *msg1 = "[Caught: ";
    const char *desc = strsignal(sig);
    const char *msg2 = "]";
    write(STDOUT_FILENO, msg1, strlen(msg1));
    write(STDOUT_FILENO, desc, strlen(desc));
    write(STDOUT_FILENO, msg2, strlen(msg2));
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Usage: %s <interval> <SIGNAL ...>\n", argv[0]);
        return 1;
    }

    char *end = NULL;
    errno = 0;
    long ival = strtol(argv[1], &end, 10);
    if (errno || end == argv[1] || *end != '\0' || ival <= 0 || ival > INT_MAX) {
        fprintf(stderr, "Invalid interval\n");
        return 1;
    }
    unsigned int interval = (unsigned int)ival;

    for (int i = 2; i < argc; ++i) {
        int sig = -1;
        for (size_t j = 0; j < sizeof(sigs)/sizeof(sigs[0]); ++j) {
            if (strcmp(argv[i], sigs[j].name) == 0) { sig = sigs[j].num; break; }
        }
        if (sig == -1) {
            fprintf(stderr, "No such signal\n");
            return 1;
        }
        if (sig == SIGKILL || sig == SIGSTOP) {
            fprintf(stderr, "Cannot catch signal\n");
            return 1;
        }
        if (signal(sig, handler) == SIG_ERR) {
            perror("signal");
            return 1;
        }
    }

    pid_t pid = getpid();
    int counter = 0;

    for (;;) {
        printf("%d: %d\n", pid, counter);
        fflush(stdout);
        ++counter;
        unsigned int rem = interval;
        while (rem) rem = sleep(rem);
    }
}