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

    for (long i = 0; i < N; i++) {
        for (long j = 0; j < N; j++) {
            A[i * N + j] = (double)(i + j);
        }
    }

    long pares = 0;
    struct timespec inicio, fim;

    clock_gettime(CLOCK_MONOTONIC, &inicio);

    // Varredura por Coluna (Pobre localidade espacial - Destrói o Cache)
    for (long j = 0; j < N; j++) {
        for (long i = 0; i < N; i++) {
            if ((int)A[i * N + j] % 2 == 0) {
                pares++;
            }
        }
    }

    clock_gettime(CLOCK_MONOTONIC, &fim);
    double tempo = (fim.tv_sec - inicio.tv_sec) + (fim.tv_nsec - inicio.tv_nsec) / 1e9;

    printf("[Column-Major] N=%ld | Pares: %ld | Tempo: %.6f s\n\n", N, pares, tempo);

    free(A);
    return 0;
}