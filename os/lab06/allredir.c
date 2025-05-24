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
        fprintf(stderr, "Usage: %s command input output\n", argv[0]);
        return 1;
    }

    pid_t pid = fork();
    if (pid == -1) {
        perror("fork");
        return 1;
    }

    if (pid == 0) {
        int fd_in = open(argv[argc - 2], O_RDONLY);
        if (fd_in == -1) {
            perror("open input");
            exit(EXIT_FAILURE);
        }

        int fd_out = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (fd_out == -1) {
            perror("open output");
            close(fd_in);
            exit(EXIT_FAILURE);
        }

        if (dup2(fd_in, STDIN_FILENO) == -1 || dup2(fd_out, STDOUT_FILENO) == -1) {
            perror("dup2");
            close(fd_in);
            close(fd_out);
            exit(EXIT_FAILURE);
        }

        close(fd_in);
        close(fd_out);

        int num_args = argc - 3;
        char *args[num_args + 1];
        for (int i = 0; i < num_args; i++) {
            args[i] = argv[1 + i];
        }
        args[num_args] = NULL;

        execvp(args[0], args);
        perror("execvp");
        exit(EXIT_FAILURE);
    } else {
        int status;
        waitpid(pid, &status, 0);
        if (WIFEXITED(status)) {
            printf("received %d\n", WEXITSTATUS(status));
        } else {
            printf("received non-normal exit\n");
        }
        return 0;
    }
}