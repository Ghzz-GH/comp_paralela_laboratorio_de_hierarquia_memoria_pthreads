#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

typedef struct {
    int id_thread;
    int num_threads;
    int N;
    double *A;
    double *B;
    double *C;
} args_thread_t;

void* multiplicacao_matriz_thread(void* arg) {
    args_thread_t* args = (args_thread_t*) arg;
    
    int id_thread = args->id_thread;
    int num_threads = args->num_threads;
    int N = args->N;
    double *A = args->A;
    double *B = args->B;
    double *C = args->C;
    
    int linhas_por_thread = N / num_threads;
    int linha_inicio = id_thread * linhas_por_thread;
    int linha_fim = (id_thread == num_threads - 1) ? N : (id_thread + 1) * linhas_por_thread;
    
    for (int i = linha_inicio; i < linha_fim; i++) {
        for (int j = 0; j < N; j++) {
            double soma = 0.0;
            for (int k = 0; k < N; k++) {
                soma += A[i * N + k] * B[k * N + j];
            }
            C[i * N + j] = soma;
        }
    }
    
    pthread_exit(NULL);
}

int main(int argc, char* argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Uso: %s <N> <num_threads>\n", argv[0]);
        return 1;
    }
    
    int N = atoi(argv[1]);
    int num_threads = atoi(argv[2]);
    
    double *A = (double*) malloc(N * N * sizeof(double));
    double *B = (double*) malloc(N * N * sizeof(double));
    double *C = (double*) malloc(N * N * sizeof(double));
    
    if (!A || !B || !C) {
        fprintf(stderr, "Erro: Falha na alocacao de memoria\n");
        return 1;
    }
    
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            A[i * N + j] = (double)(i + j);
            B[i * N + j] = (double)(i * j);
            C[i * N + j] = 0.0;
        }
    }
    
    struct timespec inicio, fim;
    clock_gettime(CLOCK_MONOTONIC, &inicio);
    
    pthread_t threads[num_threads];
    args_thread_t args[num_threads];
    
    for (int i = 0; i < num_threads; i++) {
        args[i].id_thread = i;
        args[i].num_threads = num_threads;
        args[i].N = N;
        args[i].A = A;
        args[i].B = B;
        args[i].C = C;
        
        pthread_create(&threads[i], NULL, multiplicacao_matriz_thread, &args[i]);
    }
    
    for (int i = 0; i < num_threads; i++) {
        pthread_join(threads[i], NULL);
    }
    
    clock_gettime(CLOCK_MONOTONIC, &fim);
    
    double tempo_decorrido = (fim.tv_sec - inicio.tv_sec) + 
                             (fim.tv_nsec - inicio.tv_nsec) / 1e9;
    
    double gflops = (2.0 * N * N * N) / (tempo_decorrido * 1e9);
    
    printf("[Matmul Pthreads] N: %d | Threads: %d | Tempo: %.4f s | GFLOPS: %.2f\n",
           N, num_threads, tempo_decorrido, gflops);
    
    
    free(A);
    free(B);
    free(C);
    
    return 0;
}