#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <signal.h>

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
        close(pipefd[0]);
        if (dup2(pipefd[1], STDOUT_FILENO) == -1) {
            perror("dup2 stdout");
            close(pipefd[1]);
            exit(EXIT_FAILURE);
        }
        if (close(pipefd[1]) == -1) {
            perror("close pipe write");
            exit(EXIT_FAILURE);
        }
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
        kill(pid1, SIGTERM);
        waitpid(pid1, NULL, 0);
        return 1;
    }

    if (pid2 == 0) {
        close(pipefd[1]);
        if (dup2(pipefd[0], STDIN_FILENO) == -1) {
            perror("dup2 stdin");
            close(pipefd[0]);
            exit(EXIT_FAILURE);
        }
        if (close(pipefd[0]) == -1) {
            perror("close pipe read");
            exit(EXIT_FAILURE);
        }
        execvp(argv[2], &argv[2]);
        perror("exec command2");
        exit(EXIT_FAILURE);
    }

    close(pipefd[0]);
    close(pipefd[1]);

    int status1, status2;
    int exit_code1 = 0, exit_code2 = 0;

    if (waitpid(pid1, &status1, 0) == -1) {
        perror("waitpid pid1");
        exit_code1 = -1;
    } else {
        if (WIFEXITED(status1)) {
            exit_code1 = WEXITSTATUS(status1);
        } else {
            exit_code1 = -1;
        }
    }

    if (waitpid(pid2, &status2, 0) == -1) {
        perror("waitpid pid2");
        exit_code2 = -1;
    } else {
        if (WIFEXITED(status2)) {
            exit_code2 = WEXITSTATUS(status2);
        } else {
            exit_code2 = -1;
        }
    }

    printf("child %d exited with %d\n", pid1, exit_code1);
    printf("child %d exited with %d\n", pid2, exit_code2);

    return 0;
}