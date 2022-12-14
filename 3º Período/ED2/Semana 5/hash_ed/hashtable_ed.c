#include <stdlib.h>

#include "ilist.h"
#include "hashtable_ed.h"

int THED_Hash(THED* HT, int chave){
    return chave % HT->m;
}

THED* THED_Criar(int m, int alloc_step){
    THED *nova;
    int i;

    nova = malloc(sizeof(THED));
    nova->m = m;
    nova->t = malloc(sizeof(ILIST*) * m);
    for(i = 0; i < m; i++)
        nova->t[i] = ILIST_Criar(alloc_step);

    return nova;
}
THED* inserir_n_aleatorios(int n, int m, int seed){
    srand(seed);
    int i, ale;
    THED* nova = THED_Criar(m, 10);
    for( i = 0; i<n; i++){
        ale = rand()%(n*10);
        THED_Inserir(nova, ale, ale);
    }
    return nova;
};

void THED_Inserir(THED* HT, int chave, int valor){
    int a;
    a = THED_Hash(HT, chave);
    ILIST_Inserir(HT->t[a], chave, valor);
};


void THED_Remover(THED* HT, int chave){
    int h;
    h = THED_Hash(HT,chave);
    ILIST_Remover(HT->t[h], chave);
};


INOH* THED_Buscar(THED* HT, int chave){
    int h,pos;
    h = THED_Hash(HT,chave);
    pos = ILIST_Buscar(HT->t[h],chave);
    return ILIST_Endereco(HT->t[h],pos);
};

int THED_MaisLonga(THED* TH){
    int i, maior=0;
    for (i = 0; i <TH->m; i++){
        if(TH->t[i]->tam > maior){
            maior = TH->t[i]->tam;
        };
    }
    return maior;
};
int THED_MaisCurta(THED* TH){
    int i, menor = TH->t[0]->tam;

    for (i = 0; i <TH->m; i++){
        if(TH->t[i]->tam < menor){
            menor = TH->t[i]->tam;
        };
    }

    return menor;
};
float THED_TamMedio(THED* TH){
    int i, soma = 0;
    for (i = 0; i <TH->m; i++){
            soma += TH->t[i]->tam;
    }

    return soma/ TH->m;
};