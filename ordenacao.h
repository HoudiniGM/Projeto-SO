#ifndef ORDENACAO_H
#define ORDENACAO_H

#include <pthread.h>

// Estrutura para armazenar os argumentos passados para cada thread
typedef struct {
    int* dados;                // Ponteiro para o vetor de dados (numeros)
    int inicio;                // Índice de início da porção que a thread vai ordenar
    int fim;                   // Índice de fim da porção que a thread vai ordenar
    int thread_id;             // ID da thread (para fins de identificação)
    int num_threads;           // Número total de threads
    double tempo_ordenacao;    // Tempo de execução da ordenação para essa thread
} thread_args;

extern int* numeros;           // Vetor global para armazenar todos os números lidos dos arquivos
extern int total_numeros;      // Total de números lidos de todos os arquivos

// Declarações de funções
int ler_arquivos(int argc, char* argv[]);
void* ordenar_dados(void* args);
void criar_threads_para_ordenacao(int num_threads, pthread_t* threads, thread_args* args);
int gravar_saida(const char* arquivo_saida);

#endif
