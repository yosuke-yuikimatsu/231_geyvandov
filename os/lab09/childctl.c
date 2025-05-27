#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <errno.h>
#include <limits.h>
#include <unistd.h>
#include <sys/wait.h>

typedef struct { const char *name; int num; } SigMap;
static const SigMap sigs[] = {
    {"HUP", SIGHUP},   {"INT", SIGINT},   {"QUIT", SIGQUIT}, {"ILL", SIGILL},
    {"ABRT", SIGABRT}, {"FPE", SIGFPE},   {"SEGV", SIGSEGV},
    {"PIPE", SIGPIPE}, {"ALRM", SIGALRM}, {"TERM", SIGTERM}, {"USR1", SIGUSR1},
    {"USR2", SIGUSR2}, {"CHLD", SIGCHLD}, {"CONT", SIGCONT},
    {"TSTP", SIGTSTP}, {"TTIN", SIGTTIN}, {"TTOU", SIGTTOU}
};

static volatile sig_atomic_t quit_flag = 0;
static int quit_sig_num = 0;
static const char *quit_sig_name = NULL;

static void handler(int sig) {
    const char *prefix = "[Caught: ";
    const char *desc = strsignal(sig);
    const char *suffix = "]";
    write(STDOUT_FILENO, prefix, strlen(prefix));
    write(STDOUT_FILENO, desc, strlen(desc));
    write(STDOUT_FILENO, suffix, strlen(suffix));
    if (sig == quit_sig_num) quit_flag = 1;
}

static int sig_from_name(const char *name) {
    for (size_t i = 0; i < sizeof(sigs)/sizeof(sigs[0]); ++i) {
        if (strcmp(name, sigs[i].name) == 0) return sigs[i].num;
    }
    return -1;
}

int main(int argc, char *argv[]) {
    if (argc < 4) {
        fprintf(stderr, "Usage: %s <timeout> <QUIT_SIGNAL> <SIGNAL1> [SIGNAL2 ...]\n", argv[0]);
        return 1;
    }

    char *end = NULL;
    errno = 0;
    long tval = strtol(argv[1], &end, 10);
    if (errno || end == argv[1] || *end != '\0' || tval <= 0 || tval > INT_MAX) {
        fprintf(stderr, "Invalid timeout\n");
        return 1;
    }
    unsigned int interval = (unsigned int)tval;

    quit_sig_name = argv[2];
    quit_sig_num = sig_from_name(quit_sig_name);
    if (quit_sig_num == -1 || quit_sig_num == SIGKILL || quit_sig_num == SIGSTOP) {
        fprintf(stderr, "No such signal\n");
        return 1;
    }

    pid_t child = fork();
    if (child < 0) { perror("fork"); return 1; }

    if (child == 0) {
        for (;;) pause();
    }

    if (signal(quit_sig_num, handler) == SIG_ERR) { perror("signal"); return 1; }

    for (int i = 3; i < argc; ++i) {
        int sig = sig_from_name(argv[i]);
        if (sig == -1 || sig == SIGKILL || sig == SIGSTOP) {
            fprintf(stderr, "No such signal\n");
            kill(child, SIGTERM);
            return 1;
        }
        if (signal(sig, handler) == SIG_ERR) { perror("signal"); kill(child, SIGTERM); return 1; }
    }

    int counter = 0;
    for (;;) {
        printf("Parent heartbeat: %d\n", counter);
        fflush(stdout);
        ++counter;
        unsigned int rem = interval;
        while (rem) rem = sleep(rem);
        if (quit_flag) {
            printf("Exiting gracefully on signal %s\n", quit_sig_name);
            fflush(stdout);
            kill(child, SIGTERM);
            waitpid(child, NULL, 0);
            return 0;
        }
    }
}
