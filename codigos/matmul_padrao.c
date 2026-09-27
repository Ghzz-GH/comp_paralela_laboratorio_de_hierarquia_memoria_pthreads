#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Uso: %s <N>\n", argv[0]);
        return 1;
    }
    long N = atol(argv[1]);

    double *A = (double*)malloc(N * N * sizeof(double));
    double *B = (double*)malloc(N * N * sizeof(double));
    double *C = (double*)malloc(N * N * sizeof(double));

    if (!A || !B || !C) {
        fprintf(stderr, "Erro: Falha na alocacao de memoria\n");
        return 1;
    }
    
    for (long i = 0; i < N; i++) {
        for (long j = 0; j < N; j++) {
            A[i * N + j] = (double)(i + j);
            B[i * N + j] = (double)(i * j);
            C[i * N + j] = 0.0;
        }
    }

    struct timespec inicio, fim;
    clock_gettime(CLOCK_MONOTONIC, &inicio);

    for (long i = 0; i < N; i++) {
        for (long j = 0; j < N; j++) {
            for (long k = 0; k < N; k++) {
                C[i * N + j] += A[i * N + k] * B[k * N + j];
            }
        }
    }

    clock_gettime(CLOCK_MONOTONIC, &fim);
    double tempo = (fim.tv_sec - inicio.tv_sec) + (fim.tv_nsec - inicio.tv_nsec) / 1e9;
    
    printf("\n[Matmul Padrão] N: %ld | Tempo: %.4f s\n\n", N, tempo);

    free(A); free(B); free(C);
    return 0;
}