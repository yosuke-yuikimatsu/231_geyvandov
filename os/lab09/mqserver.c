#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>
#include <errno.h>
#include <unistd.h>

int main(void) {
    const char *qname = "/mqserver";

    mq_unlink(qname);

    struct mq_attr attr;
    attr.mq_flags   = 0;
    attr.mq_maxmsg  = 10;
    attr.mq_msgsize = 1024;
    attr.mq_curmsgs = 0;

    mqd_t mq = mq_open(qname, O_CREAT | O_RDONLY, 0600, &attr);
    if (mq == (mqd_t)-1) {
        perror("mq_open");
        return 1;
    }

    if (mq_getattr(mq, &attr) == -1) {
        perror("mq_getattr");
        mq_close(mq);
        mq_unlink(qname);
        return 1;
    }

    size_t bufsize = (size_t)attr.mq_msgsize;
    char *buf = malloc(bufsize + 1);
    if (!buf) {
        perror("malloc");
        mq_close(mq);
        mq_unlink(qname);
        return 1;
    }

    for (;;) {
        ssize_t n = mq_receive(mq, buf, bufsize, NULL);
        if (n == -1) {
            if (errno == EINTR) continue;
            perror("mq_receive");
            free(buf);
            mq_close(mq);
            mq_unlink(qname);
            return 1;
        }
        buf[n] = '\0';
        if (strcmp(buf, "QUIT") == 0) break;
        printf("Received: %s\n", buf);
        fflush(stdout);
    }

    free(buf);
    mq_close(mq);
    mq_unlink(qname);
    return 0;
}
