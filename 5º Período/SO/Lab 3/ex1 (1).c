/**
 * Faça um programa com N threads que localiza um valor em um vetor de inteiros. O espaço de busca no
vetor deve ser distribuído para as N threads. 
*/
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <ctype.h>

// Define a quantidade de threads e o tamanho do vetor
#define N 3
#define TV 20
#define BUSCAR_VALOR 26

// Estrutura para passar os parametrospara as threads
struct parametros_threads {
    int *vetor;
    int valor;
    int inicio;
    int fim;
    int id;
    int tam_vetor;
};

// Função para imprimir o vetor
void imprimir_vetor(int *vetor, int tam_vetor) {
    int i;
    printf("[ ");
    for (i = 0; i < tam_vetor; i++) {
        printf("%d ", vetor[i]);
    }
    printf("]\n");
}

// Função que busca um valor no vetor
void *busca(void *parametros_threads) {
    struct parametros_threads *p = (struct parametros_threads *) parametros_threads;
    int i;
    int *vetor = p->vetor;
    int valor = p->valor;
    int inicio = p->inicio;
    int fim = p->fim;
    int id = p->id;
    int tam_vetor = p->tam_vetor;

    printf("----- Thread %d -----\n", id);
    // Imprime o subvetor que a thread irá buscar
    imprimir_vetor(vetor + inicio, fim - inicio);

    for (i = inicio; i < fim; i++) {
        if (vetor[i] == valor) {
            printf("Thread %d: Encontrei o valor %d no vetor na posicao %d\n\n", id, valor, i);
            return NULL;
        }
    }
    printf("Thread %d: Nao encontrei o valor %d no vetor\n\n", id, valor);

    return NULL;
}

// Função para gerar um vetor com valores aleatórios
void gerar_vetor(int *vetor, int tam_vetor) {
    int i;
    for (i = 0; i < tam_vetor; i++) {
        vetor[i] = rand() % 100;
    }
}


// Função principal
int main(){

    int *vetor = (int *) malloc(TV * sizeof(int));

    gerar_vetor(vetor, TV);

    printf("Vetor: ");
    imprimir_vetor(vetor, TV);
    printf("\n");

    // Alocação do vetor das threads do sistema
    pthread_t threads[N];

    // Alocação do vetor de parametros_threads
    struct parametros_threads parametros_threads[N];

    //Calculo da divisão das threads
    int quant = TV / N;
    int qnt_aux = TV % N;

    // Alocação do vetor das threads
    int i;
    for (i = 0; i < N; i++) {
        parametros_threads[i].vetor = vetor;
        parametros_threads[i].valor = BUSCAR_VALOR;
        parametros_threads[i].inicio = i * (TV / N);


        if(i < qnt_aux){
            parametros_threads[i].tam_vetor = quant + 1;
        } else{
            parametros_threads[i].tam_vetor = quant;
        }


        parametros_threads[i].fim = parametros_threads[i].inicio + parametros_threads[i].tam_vetor;
        parametros_threads[i].id = i;
        parametros_threads[i].tam_vetor = TV;

        // Criando a thread
        pthread_create(&threads[i], NULL, busca, (void *) &parametros_threads[i]);
    }

    for (i = 0; i < N; i++) {
        pthread_join(threads[i], NULL);
    }

    // Liberação da memória
    free(vetor);

    return 0;

}
