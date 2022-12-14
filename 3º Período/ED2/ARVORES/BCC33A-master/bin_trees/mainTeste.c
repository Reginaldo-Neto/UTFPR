#include "ab.h"
#include "arn.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

void testeExC(int n){
    int *v = malloc(n*sizeof(unsigned int));
    int aux = n;
    time_t time;
    unsigned int  i;
    for(i = 0; i < n; i++){
        v[i] = aux;
        aux--;
    }
    time = clock();
    printf("Teste AB");
    AB_Sort(v, n);
    time = clock() - time;
    printf("tempo para n = %d: %fs\n", n, ((float)time)/CLOCKS_PER_SEC);

    for(i = 0; i < n; i++){
        v[i] = aux;
        aux--;
    }
    time = clock();
    printf("Teste ARN");
    ARN_Sort(v, n);
    time = clock() - time;
    printf("tempo para n = %d: %fs\n", n, ((float)time)/CLOCKS_PER_SEC);
    free(v);
}

int random_32bits(){
    unsigned int x;
    x = rand() & 0xff;
    x |= (rand() & 0xff) << 8;
    x |= (rand() & 0xff) << 16;
    x |= (rand() & 0xff) << 24;

    return x;
}

void random_vector(int* v, int n){
    int max = 10*n;
    int i;
    for(i = 0; i < n; i++){
        v[i] = random_32bits() % max;
    }
}

void testeExD(int n){
    int i, j;
    double somaAB = 0;
    double somaARN = 0;
    double vetAB[10];
    double vetARN[10];
    double desvioPadraoAB,desvioPadraoARN;
    printf("Teste com n=%d\n",n);
    for(j = 1; j<11;j++){
        srand(10*j);
        for(i = 1;i<11;i++){
            //printf("Teste %d, seed %d\n",i,i*10);
            int *v = malloc(n*sizeof(unsigned int));
            random_vector(v,n);
            time_t time;
            time = clock();
            AB_Sort(v, n);
            time = clock() - time;
            somaAB+=time;
            vetAB[i] = time;
            //printf("tempo para n = %d: %fs\n", n, ((float)time)/CLOCKS_PER_SEC);

            random_vector(v,n);
            time = clock();
            AB_Sort(v,n);
            time = clock() - time;
            //printf("tempo para n = %d: %fs\n", n, ((float)time)/CLOCKS_PER_SEC);
            //printf("\n");
            somaARN+=time;
            vetARN[i]=time;
        }
        //printf("\n");
    }
    float mediaAB = somaAB/10;
    float mediaARN = somaARN/10;
    
    for(i = 0; i < 10; i++){
        desvioPadraoAB += (vetAB[i] - mediaAB)*(vetAB[i] - mediaAB);
        desvioPadraoARN += (vetARN[i] - mediaARN)*(vetARN[i] - mediaARN);
    }
    desvioPadraoAB = sqrt(desvioPadraoAB);
    desvioPadraoARN = sqrt(desvioPadraoARN);
    printf("Media AB: %f\nMedia ARN: %f\nDesvioPadrao AB: %f\nDesvioPadrao ARN: %f\n",mediaAB,mediaARN,desvioPadraoAB,desvioPadraoARN);
}

int main(){
    //printf("Exercicio C\n");
    //testeExC(1000);
    //testeExC(10000);
    //testeExC(100000);
    //testeExC(500000);

    printf("Exercicio D\n");
    testeExD(1000);
    testeExD(10000);
    testeExD(100000);
    testeExD(500000);

    return 0;
}