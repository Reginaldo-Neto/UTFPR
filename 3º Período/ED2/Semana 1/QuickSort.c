#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void printa_vetor(int* v, int comeco, int fim){
    for(comeco; comeco<fim; comeco++){
        printf("%d ", v[comeco]);
    }
    printf("\n-------------------------\n");
}

int* ord_vector(int n){
    int* v = malloc(sizeof(int)*n);
    int x;
    for (x=0; x < n; x++){
        v[x] = x;
    }
    return v;
}

int* random_vector(int n, int max, int seed){
    int* v = malloc(sizeof(int)*n);
    srand(seed);
    int x=0;
    for (x; x < n; x++){
        v[x] = rand()%max;
    }
    return v;
}

void troca(int* v, int i, int j){
    int aux;
    aux= v[i];
    v[i]= v[j];
    v[j]=aux;
}

int partitionA (int* v, int p, int r){
    int x, i, j;
    x=v[r];
    i=p-1;
    for(j=p; j<r; j++){
        if(v[j]<=x){
            i++;
            troca(v, i, j);
        }
    }
    troca(v, i+1, r);
    return i+1;
}

int partitionB (int* v, int p, int r){
    int aleatorio, x, i, j;
    aleatorio = p+rand()%r;
    x=v[r];
    i=p-1;
    for(j=p; j<r; j++){
        if(v[j]<=x){
            i++;
            troca(v, i, j);
        }
    }
    troca(v, i+1, r);
    return i+1;
}

int partitionC (int* v, int p, int r){
    int mediana, x, i, j;
    mediana= (p+r)/2;
    x=v[mediana];
    i=p-1;
    for(j=p; j<r; j++){
        if(v[j]<=x){
            i++;
            troca(v, i, j);
        }
    }
    troca(v, i+1, r);
    return i+1;
}

void quicksort(int *v, int e, int d){
    int q;
    if(e<d){
        q=partitionC(v,e,d);
        quicksort(v,e,q-1);
        quicksort(v,q+1,d);
    }
}

int main(){
    clock_t tempI, tempF;
    tempI = clock();
    int seed = 42, n=1000, max;
    max = 100*n;
    int* vetor;
    //vetor = ord_vector(n);
    vetor = random_vector(n, max, seed);
    //printa_vetor(vetor, 0, n);
    quicksort(vetor, 0, n);
    //printa_vetor(vetor, 0, n);
    free(vetor);
    tempF = clock();
    tempF=tempF-tempI;
    printf ("N: %d; DEMOROU: (%f seconds).\n",n,((float)tempF)/CLOCKS_PER_SEC);
    return 0;
}
