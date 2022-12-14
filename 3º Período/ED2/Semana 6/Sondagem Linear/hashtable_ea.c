#include <stdlib.h>
#include "hashtable_ea.h"
#include <stdio.h>

int THEA_Hash(THEA* TH, int chave, int k){
    return ((chave % TH->m) + k) % TH->m;
}

THEA* THEA_Criar(int m){
    THEA* novo;
    novo = malloc(sizeof(THEA));
    novo->TH = malloc(sizeof(ELEM)*m);
    novo->m = m;
    novo->ocupado=0;
    int i;
    for (i = 0; i < m; i++){
        novo->TH[i].estado = E_LIVRE;
    }
    return novo;
}

int THEA_Inserir(THEA *TH, int chave, int valor){
    int h, k, h_inicial;
    k=0;
    h = THEA_Hash(TH, chave, k);
    h_inicial = h;

    while (TH->TH[h].estado == E_OCUPADO){
        if(TH->TH[h].chave == chave){
            TH->ocupado--;
            break;
        }
        k++;
        h=THEA_Hash(TH, chave, k);
        if(h==h_inicial){
            return -1;
        }
    }
    TH->ocupado++;
    TH->TH[h].chave = chave;
    TH->TH[h].valor = valor;
    TH->TH[h].estado = E_OCUPADO;
    return h;
}

int THEA_Buscar(THEA *TH, int chave){
    int h, k, h_inicial;
    k=0;
    h = THEA_Hash(TH, chave, k);
    h_inicial = h;

    while (TH->TH[h].estado != E_LIVRE){
        if((TH->TH[h].estado != E_OCUPADO) && TH->TH[h].chave == chave){
            return h;
        }

        k++;
        h = THEA_Hash(TH, chave, k);

        if(h_inicial == h){
            return -1;
        }
    }
    return -1;
}

void THEA_Remover(THEA* TH, int chave){
    int pos = THEA_Buscar(TH, chave);
    if(pos != -1){
        TH->TH[pos].estado = E_APAGADO;
        TH->ocupado--;
    }
}

int THEA_ClusterMaximo(THEA* TH){
    int x, maior=-1, tam=0, cont=0;
    for(x=0; x<TH->m; x++){
        if(TH->TH[x].estado == E_LIVRE && tam>maior){
            maior=tam;
            tam=0;
        }else{
            tam++;
        }
    }
    return maior;
}

float THEA_TamMedioClusters(THEA *TH){
    int x, soma=0, tam=0, cont=0;
    for(x=0; x<TH->m; x++){
        if(TH->TH[x].estado == E_LIVRE && tam>0){
            soma+=tam;
            cont++;
            tam=0;
        }else{
            tam++;
        }
    }
    return soma/cont;
}

int* THEA_TamClusters(THEA *TH, int cont){
    int x, tam=0;
    int* vet = malloc(sizeof(int)*TH->m);
    for(x=0; x<TH->m; x++){
        if(TH->TH[x].estado == E_LIVRE && tam>0){
            vet[cont]=tam;
            cont++;
            tam=0;
        }else if(TH->TH[x].estado != E_LIVRE){
            tam++;
        }
    }
    return vet;
}

float THEA_CustoBemSucedida(THEA *TH){

    float resul;
    int x, cont=0, tam=0, soma=0;
    int vet[TH->m];

    for(x=0; x<TH->m; x++){
        if(TH->TH[x].estado == E_LIVRE && tam>0){
            vet[cont]=tam;
            cont++;
            tam=0;
        }else if(TH->TH[x].estado != E_LIVRE){
            tam++;
        }
    }
    for(x=0; x<cont; x++){
        if(vet[x]/2 > 1){
            soma+=vet[x]/2;
        }else{
            soma++;
        }
    }
    return (soma*(1/TH->ocupado));
}

