#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <errno.h>
#include <limits.h>
#include <sys/types.h>

typedef struct { const char *name; int num; } SigMap;
static const SigMap sigs[] = {
    {"HUP", SIGHUP},   {"INT", SIGINT},   {"QUIT", SIGQUIT}, {"ILL", SIGILL},
    {"ABRT", SIGABRT}, {"FPE", SIGFPE},   {"KILL", SIGKILL}, {"SEGV", SIGSEGV},
    {"PIPE", SIGPIPE}, {"ALRM", SIGALRM}, {"TERM", SIGTERM}, {"USR1", SIGUSR1},
    {"USR2", SIGUSR2}, {"CHLD", SIGCHLD}, {"CONT", SIGCONT}, {"STOP", SIGSTOP},
    {"TSTP", SIGTSTP}, {"TTIN", SIGTTIN}, {"TTOU", SIGTTOU}
};

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <PID> <SIGNAL_NAME>\n", argv[0]);
        return 1;
    }

    char *end = NULL;
    errno = 0;
    long pid_val = strtol(argv[1], &end, 10);
    if (errno || end == argv[1] || *end != '\0' || pid_val <= 0 || pid_val > INT_MAX) {
        fprintf(stderr, "Invalid PID\n");
        return 1;
    }

    int sig = -1;
    for (size_t i = 0; i < sizeof(sigs)/sizeof(sigs[0]); ++i) {
        if (strcmp(argv[2], sigs[i].name) == 0) { sig = sigs[i].num; break; }
    }
    if (sig == -1) {
        fprintf(stderr, "No such signal\n");
        return 1;
    }

    if (kill((pid_t)pid_val, sig) == -1) {
        perror("kill");
        return 1;
    }
    return 0;
}