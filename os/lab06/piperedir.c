#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>

int main(int argc, char *argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Usage: %s command1 command2 [args...]\n", argv[0]);
        return 1;
    }

    int pipefd[2];
    if (pipe(pipefd) == -1) {
        perror("pipe");
        return 1;
    }

    pid_t pid1 = fork();
    if (pid1 == -1) {
        perror("fork");
        close(pipefd[0]);
        close(pipefd[1]);
        return 1;
    }

    if (pid1 == 0) {
        // First child: execute command1
        close(pipefd[0]);
        if (dup2(pipefd[1], STDOUT_FILENO) == -1) {
            perror("dup2");
            close(pipefd[1]);
            exit(EXIT_FAILURE);
        }
        close(pipefd[1]);

        char *args1[] = { argv[1], NULL };
        execvp(argv[1], args1);
        perror("exec command1");
        exit(EXIT_FAILURE);
    }

    pid_t pid2 = fork();
    if (pid2 == -1) {
        perror("fork");
        close(pipefd[0]);
        close(pipefd[1]);
        return 1;
    }

    if (pid2 == 0) {
        // Second child: execute command2
        close(pipefd[1]);
        if (dup2(pipefd[0], STDIN_FILENO) == -1) {
            perror("dup2");
            close(pipefd[0]);
            exit(EXIT_FAILURE);
        }
        close(pipefd[0]);

        char **args2 = &argv[2];
        execvp(argv[2], args2);
        perror("exec command2");
        exit(EXIT_FAILURE);
    }

    // Parent process
    close(pipefd[0]);
    close(pipefd[1]);

    int status1, status2;
    if (waitpid(pid1, &status1, 0) == -1 || waitpid(pid2, &status2, 0) == -1) {
        perror("waitpid");
        return 1;
    }

    if (WIFEXITED(status2)) {
        printf("received %d\n", WEXITSTATUS(status2));
    } else {
        printf("received non-normal exit\n");
    }

    return 0;
}