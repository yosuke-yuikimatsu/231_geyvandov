#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

static long long sum = 0;
static pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;

typedef struct {
    int *arr;
    int start;
    int len;
} ThreadArg;

static void *worker(void *arg) {
    ThreadArg *p = (ThreadArg *)arg;
    long long local = 0;
    for (int i = 0; i < p->len; ++i) local += p->arr[p->start + i];
    pthread_mutex_lock(&mtx);
    sum += local;
    pthread_mutex_unlock(&mtx);
    return NULL;
}

int main(void) {
    int N;
    if (scanf("%d", &N) != 1 || N < 16) return 1;

    int *a = malloc((size_t)N * sizeof(int));
    if (!a) return 1;

    srand((unsigned)time(NULL));
    for (int i = 0; i < N; ++i) a[i] = rand() % 1000;

    printf("Array:");
    for (int i = 0; i < N; ++i) printf(" %d", a[i]);
    printf("\n");

    int base = N / 4;
    int rem = N % 4;

    pthread_t th[4];
    ThreadArg args[4];
    int idx = 0;
    for (int i = 0; i < 4; ++i) {
        int len = base + (i < rem);
        args[i].arr = a;
        args[i].start = idx;
        args[i].len = len;
        pthread_create(&th[i], NULL, worker, &args[i]);
        idx += len;
    }
    for (int i = 0; i < 4; ++i) pthread_join(th[i], NULL);

    printf("Total sum: %lld\n", sum);
    free(a);
    return 0;
}
