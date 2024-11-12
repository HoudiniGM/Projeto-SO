#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <time.h>
#include "ordenacao.h"

int* numeros = NULL;           // Definindo a variável global "numeros"
int total_numeros = 0;         // Definindo a variável global "total_numeros"

// Função de comparação para qsort
int comparar(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

// Função para ler os arquivos de entrada e armazenar os dados no vetor global "numeros"
int ler_arquivos(int argc, char* argv[]) {
    int capacidade = 1000;     // Capacidade inicial do vetor "numeros"
    numeros = (int*) malloc(capacidade * sizeof(int));
    if (!numeros) {
        perror("Erro ao alocar memória para o vetor global");
        return -1;
    }

    // Percorre os argumentos a partir do índice 2 (os primeiros são o programa e o número de threads)
    for (int i = 2; i < argc - 1; i++) {
        if (strcmp(argv[i], "-o") == 0) break;  // Parar quando encontrar '-o' (indicador do arquivo de saída)

        // Abre o arquivo de entrada para leitura
        FILE* f = fopen(argv[i], "r");
        if (!f) {
            perror("Erro ao abrir o arquivo");
            free(numeros);
            return -1;
        }

        int num;
        // Lê os números do arquivo e os armazena no vetor "numeros"
        while (fscanf(f, "%d", &num) != EOF) {
            // Realoca o vetor se necessário, dobrando sua capacidade
            if (total_numeros >= capacidade) {
                capacidade *= 2;
                numeros = realloc(numeros, capacidade * sizeof(int));
                if (!numeros) {
                    perror("Erro ao realocar memória");
                    fclose(f);
                    return -1;
                }
            }
            numeros[total_numeros++] = num;  // Armazena o número no vetor
        }
        fclose(f);  // Fecha o arquivo
    }
    return 0;  // Retorna 0 em caso de sucesso
}

// Função executada por cada thread para ordenar uma parte do vetor "numeros"
void* ordenar_dados(void* args) {
    thread_args* dados = (thread_args*) args;
    struct timespec inicio, fim;

    // Início da medição do tempo de ordenação para a thread
    clock_gettime(CLOCK_MONOTONIC, &inicio);
    // Ordena a porção do vetor atribuída a esta thread usando "qsort"
    qsort(dados->dados + dados->inicio, dados->fim - dados->inicio + 1, sizeof(int), comparar);

    // Se for a última thread, realiza a ordenação final em "numeros"
    if (dados->thread_id == dados->num_threads - 1) {
        qsort(numeros, total_numeros, sizeof(int), comparar);
    }

    // Fim da medição de tempo para a ordenação local
    clock_gettime(CLOCK_MONOTONIC, &fim);
    // Calcula o tempo de ordenação e armazena em "dados->tempo_ordenacao"
    dados->tempo_ordenacao = (fim.tv_sec - inicio.tv_sec) + (fim.tv_nsec - inicio.tv_nsec) / 1e9;

    pthread_exit(NULL);  // Finaliza a thread
}

// Função para criar as threads e dividir o trabalho de ordenação
void criar_threads_para_ordenacao(int num_threads, pthread_t* threads, thread_args* args) {
    int base_segment_size = total_numeros / num_threads;  // Tamanho básico do segmento para cada thread
    int extra_elements = total_numeros % num_threads;     // Elementos extras para distribuir entre as primeiras threads
    int current_start = 0;  // Ponto inicial da primeira thread

    for (int i = 0; i < num_threads; i++) {
        args[i].dados = numeros;
        args[i].inicio = current_start;                   // Define o início do segmento para a thread
        args[i].fim = current_start + base_segment_size - 1; // Define o fim do segmento
        if (i < extra_elements) args[i].fim++;            // Distribui um elemento extra para as primeiras threads
        args[i].thread_id = i;                            // Define o ID da thread
        args[i].num_threads = num_threads;                // Define o número total de threads
        args[i].tempo_ordenacao = 0.0;                    // Inicializa o tempo de ordenação com zero
        current_start = args[i].fim + 1;                  // Atualiza o ponto de início para a próxima thread
        // Cria a thread que executará a função "ordenar_dados" com os argumentos "args[i]"
        pthread_create(&threads[i], NULL, ordenar_dados, (void*) &args[i]);
    }
}

// Função para gravar o vetor "numeros" ordenado no arquivo de saída
int gravar_saida(const char* arquivo_saida) {
    FILE* saida = fopen(arquivo_saida, "w");              // Abre o arquivo de saída para escrita
    if (!saida) {
        perror("Erro ao abrir o arquivo de saída");
        return -1;
    }
    // Grava cada número do vetor "numeros" no arquivo de saída
    for (int i = 0; i < total_numeros; i++) {
        fprintf(saida, "%d\n", numeros[i]);
    }
    fclose(saida);  // Fecha o arquivo de saída
    return 0;       // Retorna 0 em caso de sucesso
}
