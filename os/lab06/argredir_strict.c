#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

int main(int argc, char *argv[]) {
    if (argc < 4) {
        fprintf(stderr, "Usage: %s input output command [args...]\n", argv[0]);
        return 1;
    }

    const char *input_file = argv[1];
    const char *output_file = argv[2];
    char **args = &argv[3];

    pid_t pid = fork();
    if (pid == -1) {
        perror("fork");
        return 1;
    }

    if (pid == 0) {
        int fd_in = open(input_file, O_RDONLY);
        if (fd_in == -1) {
            perror("open input");
            exit(EXIT_FAILURE);
        }

        int fd_out = open(output_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (fd_out == -1) {
            perror("open output");
            close(fd_in);
            exit(EXIT_FAILURE);
        }

        if (dup2(fd_in, STDIN_FILENO) == -1) {
            perror("dup2 stdin");
            close(fd_in);
            close(fd_out);
            exit(EXIT_FAILURE);
        }

        if (dup2(fd_out, STDOUT_FILENO) == -1) {
            perror("dup2 stdout");
            close(fd_in);
            close(fd_out);
            exit(EXIT_FAILURE);
        }

        if (close(fd_in) == -1) {
            perror("close input");
            close(fd_out);
            exit(EXIT_FAILURE);
        }

        if (close(fd_out) == -1) {
            perror("close output");
            exit(EXIT_FAILURE);
        }

        execvp(args[0], args);
        perror("execvp");
        exit(EXIT_FAILURE);
    } else {
        int status;
        if (waitpid(pid, &status, 0) == -1) {
            perror("waitpid");
            return 1;
        }

        int exit_code;
        if (WIFEXITED(status)) {
            exit_code = WEXITSTATUS(status);
        } else {
            exit_code = 1;
        }
        printf("received %d\n", exit_code);
        return exit_code;
    }
}