#include <stdlib.h>
#include <stdio.h>

void troca(int *v, int maior, int i){
    int aux;
    aux=v[i];
    v[i]=v[maior];
    v[maior]=aux;
}

unsigned int random_32bits(int seed){
    unsigned int x;
    srand(seed);
    x = rand() & 0xff;
    x |= (rand() & 0xff) << 8;
    x |= (rand() & 0xff) << 16;
    x |= (rand() & 0xff) << 24;

    return x;
}

void embaralhar(int *v, int ini, int fim, int seed){
    int i, j;
    for(i = fim-1; i > ini; i--){
        j = (random_32bits(seed) % (i + 1));
        j = j <= ini? ini+1 : j;
        troca(v, i, j);
    }
}
int* random_vector_unique_elems(int n, int seed){
    int* v = malloc(sizeof(int)*n);
    int x;
    for(x=0; x<n; x++){
        v[x]=x;
    }
    embaralhar(v, 0, n, seed);
    return v;
};

int max(int *v, int ini, int fim){
    int x, maior, posMaior;
    maior = v[ini]-1;
    for (x=ini; x<=fim; x++){
        if(v[x]>maior){
            maior = v[x];
            posMaior=x;
        }
    }
    return posMaior;
};

int SelectionMinK(int* v, int n, int k){
    int i, maior;
    for(i=n-1; i>=0; i--){
        maior = max(v, 0, i);
        troca(v, maior, i);
    }
    if(k>n){
        return v[0];
    }
    return v[k-1];
}
//------------------------------------------ QUICK SORT

int partition(int *v, int e, int d, int k){
    int x, i, j;
    x=v[d];
    i=e-1;
    for(j=e; j<d; j++){
        if(v[j]<=x){
            i++;
            troca(v,i,j);
        }
    }
    troca(v, i+1, d);
    return i+1;
}

int QuickMinK(int *v, int e, int d, int k){
    int q, x;
    if(e<d){
        q=partition(v, e, d, k);       
        QuickMinK(v, e, q-1, k);      
        QuickMinK(v, q+1, d, k);
    }
    return v[k];
};
