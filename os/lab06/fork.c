#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>

int main() {
    pid_t child1 = fork();

    if (child1 == 0) {
        pid_t child2 = fork();
        if (child2 == 0) {
            printf("Hello from Child2\n");
            return 0;
        } else {
            waitpid(child2, NULL, 0);
            printf("Hello from Child1\n");
            return 0;
        }
    } else {
        waitpid(child1, NULL, 0);
        printf("Hello from Parent\n");
        return 0;
    }
}