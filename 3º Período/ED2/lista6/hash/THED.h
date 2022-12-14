#pragma once
#include "../list/ilist.h"

typedef struct THED{
  int M;
  ILIST** th;
} THED;

THED* THED_criar(int m, int alloc_step);
int THED_hash(THED* TH, int chave);
int THED_inserir(THED* TH, int chave,int valor);
INOH* THED_buscar(THED* TH, int chave);
int THED_remover(THED* TH, int chave);

THED* THED_inserir_n_aleatorios(int n, int m, int seed);

int THED_MaisLonga(THED* TH);
int THED_MaisCurta(THED* TH);
float THED_TamMedio(THED* TH);