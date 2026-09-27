#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

typedef struct {
    int id_thread;
    int num_threads;
    int N;
    int B;
    double *A;
    double *B_matriz;
    double *C;
} args_thread_bloco_t;

void* multiplicacao_matriz_bloco_thread(void* arg) {
    args_thread_bloco_t* args = (args_thread_bloco_t*) arg;
    
    int id_thread = args->id_thread;
    int num_threads = args->num_threads;
    int N = args->N;
    int B = args->B;
    double *A = args->A;
    double *B_matriz = args->B_matriz;
    double *C = args->C;
    
    int linhas_por_thread = N / num_threads;
    int linha_inicio = id_thread * linhas_por_thread;
    int linha_fim = (id_thread == num_threads - 1) ? N : (id_thread + 1) * linhas_por_thread;
    
    for (int ii = linha_inicio; ii < linha_fim; ii += B) {
        for (int jj = 0; jj < N; jj += B) {
            for (int kk = 0; kk < N; kk += B) {
                for (int i = ii; i < ii + B && i < linha_fim; i++) {
                    for (int k = kk; k < kk + B && k < N; k++) {
                        double r = A[i * N + k];
                        for (int j = jj; j < jj + B && j < N; j++) {
                            C[i * N + j] += r * B_matriz[k * N + j];
                        }
                    }
                }
            }
        }
    }
    
    pthread_exit(NULL);
}

int main(int argc, char* argv[]) {
    if (argc < 4) {
        fprintf(stderr, "Uso: %s <N> <num_threads> <tamanho_bloco>\n", argv[0]);
        return 1;
    }
    
    int N = atoi(argv[1]);
    int num_threads = atoi(argv[2]);
    int B = atoi(argv[3]);
    
    double *A = (double*) malloc(N * N * sizeof(double));
    double *B_matriz = (double*) malloc(N * N * sizeof(double));
    double *C = (double*) malloc(N * N * sizeof(double));
    
    if (!A || !B_matriz || !C) {
        fprintf(stderr, "Erro: Falha na alocacao\n");
        return 1;
    }
    
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            A[i * N + j] = (double)(i + j);
            B_matriz[i * N + j] = (double)(i * j);
            C[i * N + j] = 0.0;
        }
    }
    
    struct timespec inicio, fim;
    clock_gettime(CLOCK_MONOTONIC, &inicio);
    
    pthread_t threads[num_threads];
    args_thread_bloco_t args[num_threads];
    
    for (int i = 0; i < num_threads; i++) {
        args[i].id_thread = i;
        args[i].num_threads = num_threads;
        args[i].N = N;
        args[i].B = B;
        args[i].A = A;
        args[i].B_matriz = B_matriz;
        args[i].C = C;
        
        pthread_create(&threads[i], NULL, multiplicacao_matriz_bloco_thread, &args[i]);
    }
    
    for (int i = 0; i < num_threads; i++) {
        pthread_join(threads[i], NULL);
    }
    
    clock_gettime(CLOCK_MONOTONIC, &fim);
    
    double tempo_decorrido = (fim.tv_sec - inicio.tv_sec) + 
                             (fim.tv_nsec - inicio.tv_nsec) / 1e9;
    
    double gflops = (2.0 * N * N * N) / (tempo_decorrido * 1e9);
    
    printf("[Matmul Pthreads Bloco] N: %d | Threads: %d | Bloco: %d | Tempo: %.4f s | GFLOPS: %.2f\n\n",
           N, num_threads, B, tempo_decorrido, gflops);
    
    
    free(A);
    free(B_matriz);
    free(C);
    
    return 0;
}