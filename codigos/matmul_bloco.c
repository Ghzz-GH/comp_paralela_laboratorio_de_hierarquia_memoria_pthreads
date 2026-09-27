#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MIN(a, b) ((a) < (b) ? (a) : (b))

int main(int argc, char* argv[]) {
    if (argc != 3) {
        printf("Uso: %s <N> <Tamanho_do_Bloco>\n", argv[0]);
        return 1;
    }
    long N = atol(argv[1]);
    long B_size = atol(argv[2]);

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

    for (long ii = 0; ii < N; ii += B_size) {
        for (long jj = 0; jj < N; jj += B_size) {
            for (long kk = 0; kk < N; kk += B_size) {
                
                // Multiplicação do sub-bloco
                for (long i = ii; i < MIN(ii + B_size, N); i++) {
                    for (long k = kk; k < MIN(kk + B_size, N); k++) {
                        double a_ik = A[i * N + k];
                        for (long j = jj; j < MIN(jj + B_size, N); j++) {
                            C[i * N + j] += a_ik * B[k * N + j];
                        }
                    }
                }

            }
        }
    }

    clock_gettime(CLOCK_MONOTONIC, &fim);
    double tempo = (fim.tv_sec - inicio.tv_sec) + (fim.tv_nsec - inicio.tv_nsec) / 1e9;
    
    printf("\n[Matmul Blocado] N: %ld | Bloco: %ld | Tempo: %.4f s\n\n", N, B_size, tempo);

    free(A); free(B); free(C);
    return 0;
}