#include <stdio.h>
#include <stdlib.h>
#include "arn.h"

ARN* ARN_Criar(int chave, int valor){
    ARN* novo;

    novo = malloc(sizeof(struct ARN));
    novo->cor = C_VERMELHO;
    novo->valor = valor;
    novo->chave = chave;
    novo->esq = NULL;
    novo->dir = NULL;

    return novo;
}

static void rot_esq(ARN **A){
    ARN* h;
    ARN* x;
    h = *A;
    x = h->dir;
    h->dir = x->esq;
    x->esq = h;
    x->cor = h->cor;
    h->cor = C_VERMELHO;
    *A = x;
}

static void rot_dir(ARN **A){
    ARN* h;
    ARN* x;
    h = *A;
    x = h->esq;
    h->esq = x->dir;
    x->dir = h;
    x->cor = h->cor;
    h->cor = C_VERMELHO;
    *A = x;
}

int eh_vermelho(ARN* A){
    if(A == NULL)
        return 0;

    return A->cor == C_VERMELHO ? 1 : 0;
}

static void inverter_cores(ARN* h){
    h->cor = C_VERMELHO;
    h->esq->cor = C_PRETO;
    h->dir->cor = C_PRETO;
}


void ARN_Inserir_R(ARN **A, int chave, int valor){
    if((*A) == NULL){
        *A = ARN_Criar(chave, valor);
        return;
    }

    if(chave < (*A)->chave){
        ARN_Inserir(&(*A)->esq, chave, valor);
    }
    if(chave > (*A)->chave){
        ARN_Inserir(&(*A)->dir, chave, valor);
    }
    if(eh_vermelho((*A)->dir) && !eh_vermelho((*A)->esq)){
        rot_esq(A);
    }
    if(eh_vermelho((*A)->esq) && eh_vermelho((*A)->esq->esq)){
        rot_dir(A);
    }
    if(eh_vermelho((*A)->esq) && eh_vermelho((*A)->dir)){
        inverter_cores(*A);
    }
};

void ARN_Inserir(ARN** A, int chave, int valor){
    ARN_Inserir_R(A, chave, valor);
    (*A)->cor = C_PRETO;
}


void ARN_Destruir(ARN* A){
    if(A == NULL)
        return;
    ARN_Destruir(A->esq);
    ARN_Destruir(A->dir);
    free(A);
}

int ARN_Imprimir(ARN* A, int nivel, char lado, int retorno){
    int i;
    for(i = 0; i < nivel; i++){
        //printf("--> ");
    }
    if(A == NULL){
        //printf("(%c) NONE\n", lado);
    }
    else{
        if(nivel>retorno)retorno=nivel;
        //printf("(%c) %d [%s]\n", lado, A->valor, A->cor == C_VERMELHO ? "V" : "P");
        retorno = ARN_Imprimir(A->esq, nivel+1, 'e', retorno);
        retorno = ARN_Imprimir(A->dir, nivel+1, 'd', retorno);
    }
    return retorno;
}


int ARN_Sort(int *v, int n){
    ARN* A = ARN_Criar(v[0], 0);
    int x;
    for(x=1; x<n; x++){
        ARN_Inserir(&A, v[x], 0);
    }
    ARN_Sort_R(v, n, A, 0);
    int profundidade;
    profundidade = ARN_Imprimir(A, 0, 'r', 0);
    ARN_Destruir(A);
    return profundidade;
};

int ARN_Sort_R(int* v, int n, ARN* A, int x){
    if(A->esq!=NULL){
        x = ARN_Sort_R(v, n, A->esq, x);
    }
    v[x]=A->chave;
    x++;
    if(A->dir!=NULL){
        x = ARN_Sort_R(v, n, A->dir, x);
    }
    return x;
};







