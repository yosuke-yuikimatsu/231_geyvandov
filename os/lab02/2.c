#include <stdio.h>
#include <stdlib.h>

int main() {
    int n;
    if (scanf("%d", &n) != 1) {
        return 1;
    }

    if (n <= 0) {
        return 0;
    }

    int *arr = malloc(n * sizeof(int));
    if (!arr) {
        return 1;
    }

    for (int i = 0; i < n; ++i) {
        if (scanf("%d", &arr[i]) != 1) {
            free(arr);
            return 1;
        }
    }

    for (int i = 0; i < n / 2; ++i) {
        int temp = arr[i];
        arr[i] = arr[n - 1 - i];
        arr[n - 1 - i] = temp;
    }

    printf("%d", arr[0]);
    for (int i = 1; i < n; ++i) {
        printf(" %d", arr[i]);
    }
    printf("\n");

    free(arr);
    return 0;
}