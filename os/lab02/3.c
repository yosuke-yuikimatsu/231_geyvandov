#include <stdio.h>
#include <stdlib.h>

int main() {
    int N, M;
    if (scanf("%d %d", &N, &M) != 2 || N <= 0 || M <= 0) {
        return 0;
    }

    
    int **matrix = malloc(N * sizeof(int *));
    if (!matrix) return 1;
    
    for (int i = 0; i < N; i++) {
        matrix[i] = malloc(M * sizeof(int));
        if (!matrix[i]) {
            // Cleanup on failure
            for (int k = 0; k < i; k++) free(matrix[k]);
            free(matrix);
            return 1;
        }
    }

    
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (scanf("%d", &matrix[i][j]) != 1) {
                
                for (int k = 0; k < N; k++) free(matrix[k]);
                free(matrix);
                return 1;
            }
        }
    }

    
    int **transposed = malloc(M * sizeof(int *));
    if (!transposed) {
        for (int i = 0; i < N; i++) free(matrix[i]);
        free(matrix);
        return 1;
    }
    
    for (int i = 0; i < M; i++) {
        transposed[i] = malloc(N * sizeof(int));
        if (!transposed[i]) {
            
            for (int k = 0; k < i; k++) free(transposed[k]);
            free(transposed);
            for (int k = 0; k < N; k++) free(matrix[k]);
            free(matrix);
            return 1;
        }
    }

    
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            transposed[j][i] = matrix[i][j];
        }
    }

    
    for (int i = 0; i < M; i++) {
        printf("%d", transposed[i][0]);
        for (int j = 1; j < N; j++) {
            printf(" %d", transposed[i][j]);
        }
        printf("\n");
    }

    for (int i = 0; i < N; i++) free(matrix[i]);
    free(matrix);
    
    for (int i = 0; i < M; i++) free(transposed[i]);
    free(transposed);

    return 0;
}