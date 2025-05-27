#include <stdio.h>
#include <string.h>
#include <mqueue.h>
#include <fcntl.h>
#include <errno.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <queue> <message>\n", argv[0]);
        return 1;
    }

    mqd_t q = mq_open(argv[1], O_WRONLY);
    if (q == (mqd_t)-1) {
        perror("mq_open");
        return 1;
    }

    if (mq_send(q, argv[2], strlen(argv[2]), 1) == -1) {
        perror("mq_send");
        mq_close(q);
        return 1;
    }

    mq_close(q);
    return 0;
}
