#include <stdio.h> 
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include "matriz.h"

// Defines
#define NUMERO_DE_THREADS 5

// Variaveis Globais
int** matriz; //matriz global

int rows = 6;       //linhas
int cols = 8;       //colunas

float* medias;
int* medianas;

// Estrutura
typedef struct {
    int id;
    int qtd;
} Dados;

// Declaração das funções
void* media_thread(void* parametro);
void selectionSort(int* vetor, int tamanho);
void* mediana_thread(void* parametro);

int main(){

    int op;

    pthread_t threads[NUMERO_DE_THREADS];
    Dados dados[NUMERO_DE_THREADS];

    do{
        printf("Escolha o que você quer fazer!:\n[1] - Gerar Matriz\n[2] - Carregar Matriz\n");
        scanf("%d", &op);
    } while(op != 1 && op != 2);


    // Gerar ou cvetoregar a matriz
    if (op == 1){

        printf("Qual o numero de linhas?\n> ");
        scanf("%d", &rows);
        printf("Qual o numero de colunas?\n> ");
        scanf("%d", &cols);

        matriz = create_matrix(rows, cols);
        srand(time(NULL));  //Time para criar numeros aleatorios sempre
        generate_elements(matriz, rows, cols, 99);

    } else{
        matriz = read_matrix_from_file("data_matrix.in", &rows, &cols);
    }

    // Inicio da contagem de clock
    clock_t start = clock();

    printf("\nNumero de Threads: %d\n", NUMERO_DE_THREADS);
    printf("\nMatriz [%d x %d]\n\n", rows, cols);



    printf("        Media:      \n");

    float resultados_obtidos_media[cols];
    for(int i = 0; i < cols; i++){
        resultados_obtidos_media[i] = 0;
    }
    medias = resultados_obtidos_media;

    //Divisão das colunas para o exercío 2
    int quant = cols / NUMERO_DE_THREADS;
    int qnt_aux = cols % NUMERO_DE_THREADS;
    int aux = 0;

    for(int i = 0; i < NUMERO_DE_THREADS; i++){
        if(i < qnt_aux){
            dados[i].qtd = quant + 1;
        } else{
            dados[i].qtd = quant;
        }
        dados[i].id = i;

        printf("Thread de numero %d: %d colunas\n", i, dados[i].qtd);
    }
    printf("\n");

    print_matrix(matriz, rows, cols);

    for(int i = 0; i < NUMERO_DE_THREADS; i++){
        pthread_create(&threads[i], NULL, media_thread, (void*) &dados[i]);
    }
    
    for(int i = 0; i < NUMERO_DE_THREADS; i++){
        pthread_join(threads[i], NULL);
    }

    printf("Mediana:\n");
    quant = rows / NUMERO_DE_THREADS;
    qnt_aux = rows % NUMERO_DE_THREADS;
    aux = 0;

    for(int i = 0; i < NUMERO_DE_THREADS; i++){
        if(i < qnt_aux){
            dados[i].qtd = quant + 1;
        } else{
            dados[i].qtd = quant;
        }
        dados[i].id = i;

        printf("Thread %d: %d linhas\n", i, dados[i].qtd);
    }

    int matriz_copia[rows][cols];
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            matriz_copia[i][j] = matriz[i][j];
        }
    }
    //Ordenação através do algoritmo do Selection Sort (ed1)
    for(int i = 0; i < rows; i++){
        selectionSort(matriz[i], cols);
    }
    print_matrix(matriz, rows, cols);

    // Inicializando o vetor
    int resultado_medianas[rows];
    for(int i = 0; i < rows; i++){
        resultado_medianas[i] = 0;
    }
    medianas = resultado_medianas;

    for(int i = 0; i < NUMERO_DE_THREADS; i++){
        pthread_create(&threads[i], NULL, mediana_thread, (void*) &dados[i]);
    }

    
    for(int i = 0; i < NUMERO_DE_THREADS; i++){
        pthread_join(threads[i], NULL);
    }

    
    
    printf("\nA Mediana calculada é: ");
    for(int i=0; i<rows;i++){
        printf(" [%d]", resultado_medianas[i]);
    }
    printf("\n");

    printf("\nMedia: ");
    for(int i=0; i<cols;i++){
        printf(" [%.2f]", medias[i]);
    }
    printf("\n");

    //Salvando num arquivo de saída
    FILE* arq_result = fopen("results.txt", "w");

    fprintf(arq_result, "Mediana: ");
    for(int i=0; i<rows;i++){
        fprintf(arq_result, " [%d]", resultado_medianas[i]);
    }
    fprintf(arq_result, "\n");

    fprintf(arq_result, "Media: ");
    for(int i=0; i<cols;i++){
        fprintf(arq_result, " [%.2f]", medias[i]);
    }
    fprintf(arq_result, "\n");

    printf("\nResultados salvos com sucesso!\n");

    fclose(arq_result);

    // Fim da contagem de tempo
    clock_t end = clock();
    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;

    printf("\nTempo gasto: %f segundos\n", time_spent);

    return 0;
}



void *media_thread(void *parametro){
    Dados *dados = (Dados*) parametro;

    int inicio = dados->id * dados->qtd;
    int fim = inicio + dados->qtd;

    for(int i = inicio; i < fim; i++){
        for(int j = 0; j < rows; j++){
            medias[i] += (float)matriz[j][i]/ (float)rows;
        }
        //printf("Coluna %d: %f\n", i, medias[i]);
    }
}


void selectionSort(int vetor[], int n){
    int i, j, min_idx;
    for (i = 0; i < n-1; i++){
        min_idx = i;
        for (j = i+1; j < n; j++)
          if (vetor[j] < vetor[min_idx]) min_idx = j;
        // Swap 
        vetor[min_idx] = vetor[min_idx] + vetor[i]-(vetor[i]=vetor[min_idx]);
    }
}

void *mediana_thread(void *parametro){
    Dados *dados = (Dados*)parametro;

    int inicio = dados->id * dados->qtd;
    int fim = inicio + dados->qtd;


    for(int i = inicio; i < fim; i++){
        medianas[i] = matriz[i][(int)ceil(cols/2)];
    }
    
}