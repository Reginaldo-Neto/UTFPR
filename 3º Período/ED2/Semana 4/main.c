#include <stdio.h>
#include "semana4.h"
#include <time.h>
#include <stdlib.h>

int main(){

    int x, chave, valor, seed=42, n;
    n=1000;
    chave = n/2;
    printf("TESTE 01 - K=%d e N=%d\n", chave, n);
    clock_t inicio;
    clock_t fim; 
    int* vet = random_vector_unique_elems(n, seed);
    inicio = clock();
    printf("SelectionMinK: %d\n", (int) SelectionMinK(vet, n, chave));
    fim = clock();
    printf("TEMPO = %f\n", (double) ((fim-inicio)/CLOCKS_PER_SEC));
    free(vet);
   
    vet = random_vector_unique_elems(n, seed);
    inicio = clock();
    printf("QuickMinK: %d\n", (int) QuickMinK(vet, 0, n-1, chave-1));
    fim = clock();
    printf("TEMPO = %f\n", (double) ((fim-inicio)/CLOCKS_PER_SEC));
    free(vet);
    //___________________________________________________________
    n=10000;
    chave = n/2;
    printf("TESTE 01 - K=%d e N=%d\n", chave, n);
    
    vet = random_vector_unique_elems(n, seed);
    inicio = clock();
    printf("SelectionMinK: %d\n", (int) SelectionMinK(vet, n, chave));
    fim = clock();
    printf("TEMPO = %f\n", (double) ((fim-inicio)/CLOCKS_PER_SEC));
    free(vet);
   
    vet = random_vector_unique_elems(n, seed);
    inicio = clock();
    printf("QuickMinK: %d\n", (int) QuickMinK(vet, 0, n-1, chave-1));
    fim = clock();
    printf("TEMPO = %f\n", (double) ((fim-inicio)/CLOCKS_PER_SEC));
    free(vet);
//___________________________________________________________
    n=100000;
    chave = n/2;
    printf("TESTE 01 - K=%d e N=%d\n", chave, n);
    
    vet = random_vector_unique_elems(n, seed);
    inicio = clock();
    printf("QuickMinK: %d\n", (int) QuickMinK(vet, 0, n-1, chave-1));
    fim = clock();
    printf("TEMPO = %f\n", (double) ((fim-inicio)/CLOCKS_PER_SEC));
    free(vet);
    //___________________________________________________________
    n=500000;
    chave = n/2;
    printf("TESTE 01 - K=%d e N=%d\n", chave, n);
    
    vet = random_vector_unique_elems(n, seed);
    inicio = clock();
    printf("QuickMinK: %d\n", (int) QuickMinK(vet, 0, n-1, chave-1));
    fim = clock();
    printf("TEMPO = %f\n", (double) ((fim-inicio)/CLOCKS_PER_SEC));
    free(vet);
    //___________________________________________________________
    n=1000000;
    chave = n/2;
    printf("TESTE 01 - K=%d e N=%d\n", chave, n);
       
    vet = random_vector_unique_elems(n, seed);
    inicio = clock();

    
    printf("QuickMinK: %d\n", (int) QuickMinK(vet, 0, n-1, chave-1));
    fim = clock();
    printf("TEMPO = %f\n", (double) ((fim-inicio)/CLOCKS_PER_SEC));
    free(vet);
}