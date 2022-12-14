#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "../list/ilist.h"
#include "THED.h"

THED* THED_criar(int m, int alloc_step){
  THED* nova;
  nova = malloc(sizeof(THED));
  nova->M = m;
  nova->th = malloc(sizeof(ILIST*) * m);
  int i;
  for ( i = 0; i < m; i++){
    nova->th[i] = ILIST_Criar(alloc_step);
  }
  return nova;
}

int THED_hash(THED* TH, int chave){
  return chave % TH->M;
}



INOH* THED_buscar(THED* TH, int chave){
  int h,pos;
  h = THED_hash(TH,chave);
  pos = ILIST_Buscar(TH->th[h],chave);
  return ILIST_Endereco(TH->th[h],pos);

}

int THED_inserir(THED* TH, int chave,int valor){
  int h;
  h = THED_hash(TH,chave);
  return ILIST_Inserir(TH->th[h],chave,valor);
}

THED* THED_inserir_n_aleatorios(int n, int m, int seed){
  srand(seed);
  int random;
  int i;
  THED* new = THED_criar(m,10);
  for ( i = 0; i < n; i++){
    random = rand() % (n*10);
    THED_inserir(new,random,random);
    
  }
  return new;
}

int THED_remover(THED* TH, int chave);

int THED_MaisLonga(THED* TH){
  int maior=0;
  int i;
  for ( i = 0; i < TH->M; i++){
    if(TH->th[i]->tam > maior)
      maior = TH->th[i]->tam;
  }
  return maior;
}

int THED_MaisCurta(THED* TH){
  int menor=INT_MAX;
  int i;
  for ( i = 0; i < TH->M; i++){
    if(TH->th[i]->tam < menor)
      menor = TH->th[i]->tam;
  }
  return menor;
}

float THED_TamMedio(THED* TH){
  float media =0;
  int i;
  for ( i = 0; i < TH->M; i++){
      media += (float)TH->th[i]->tam;
  }
  media = media/(float)TH->M;

  return media;
}
