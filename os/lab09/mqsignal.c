#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>
#include <errno.h>
#include <signal.h>
#include <unistd.h>

static volatile sig_atomic_t stop_flag = 0;

static void sig_handler(int sig) { (void)sig; stop_flag = 1; }

int main(void) {
    const char *qname = "/mqsignal";
    mq_unlink(qname);

    struct mq_attr attr = {0};
    attr.mq_maxmsg = 10;
    attr.mq_msgsize = 1024;

    mqd_t mq = mq_open(qname, O_CREAT | O_RDONLY, 0600, &attr);
    if (mq == (mqd_t)-1) { perror("mq_open"); return 1; }

    if (mq_getattr(mq, &attr) == -1) { perror("mq_getattr"); mq_close(mq); mq_unlink(qname); return 1; }

    size_t bufsize = (size_t)attr.mq_msgsize;
    char *buf = malloc(bufsize + 1);
    if (!buf) { perror("malloc"); mq_close(mq); mq_unlink(qname); return 1; }

    struct sigaction sa; sa.sa_handler = sig_handler; sigemptyset(&sa.sa_mask); sa.sa_flags = 0;
    if (sigaction(SIGINT, &sa, NULL) == -1) { perror("sigaction"); free(buf); mq_close(mq); mq_unlink(qname); return 1; }

    for (;;) {
        ssize_t n = mq_receive(mq, buf, bufsize, NULL);
        if (n == -1) {
            if (errno == EINTR) { if (stop_flag) break; else continue; }
            perror("mq_receive"); free(buf); mq_close(mq); mq_unlink(qname); return 1; }
        buf[n] = '\0';
        if (strcmp(buf, "QUIT") == 0) { stop_flag = 1; break; }
        printf("Received: %s\n", buf);
        fflush(stdout);
    }

    printf("Server stopped\n");
    fflush(stdout);

    free(buf);
    mq_close(mq);
    mq_unlink(qname);
    return 0;
}
