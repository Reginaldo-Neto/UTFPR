#pragma once
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include "../gerador/big_file.h"

typedef struct BUFFER_SAIDA{
    ITEM_VENDA* vetor;
    int tamanho;
    int posicao;
    FILE* file;
}SAIDA;

SAIDA* saida_criar(char* nome_arquivo, int qnt_registros);

void saida_inserir(ITEM_VENDA* registro, SAIDA* buffer);

void saida_despejar(SAIDA* buffer);

void saida_destruir(SAIDA** buffer);

void saida_imprimir(SAIDA* buffer);