#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include "ordenacao.h"

int main(int argc, char* argv[]) {
    // Verifica se o número de argumentos é suficiente
    if (argc < 4) {
        printf("Uso: %s <num_threads> <arquivo1> <arquivo2> ... -o <saida>\n", argv[0]);
        return 1;
    }

    int num_threads = atoi(argv[1]);                     // Número de threads definido pelo usuário
    char* arquivo_saida = argv[argc - 1];                // Último argumento é o nome do arquivo de saída

    // Lê os arquivos de entrada e armazena os dados no vetor `numeros`
    if (ler_arquivos(argc, argv) != 0) return 1;

    struct timespec inicio_total, fim_total;             // Para medir o tempo total de execução
    clock_gettime(CLOCK_MONOTONIC, &inicio_total);

    pthread_t threads[num_threads];                      // Array de threads
    thread_args args[num_threads];                       // Array de argumentos para cada thread
    criar_threads_para_ordenacao(num_threads, threads, args);

    // Aguarda todas as threads terminarem e exibe o tempo de cada uma
    for (int i = 0; i < num_threads; i++) {
        pthread_join(threads[i], NULL);
        printf("Tempo de execução do thread %d: %f segundos.\n", args[i].thread_id, args[i].tempo_ordenacao);
    }

    clock_gettime(CLOCK_MONOTONIC, &fim_total);
    double tempo_total_execucao = (fim_total.tv_sec - inicio_total.tv_sec) + (fim_total.tv_nsec - inicio_total.tv_nsec) / 1e9;
    printf("Tempo total de execução: %f segundos.\n", tempo_total_execucao);

    // Grava o vetor ordenado no arquivo de saída
    if (gravar_saida(arquivo_saida) != 0) {
        free(numeros);
        return 1;
    }

    free(numeros);  // Libera a memória alocada para `numeros`
    return 0;
}
