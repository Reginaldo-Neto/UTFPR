#pragma once
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "../gerador/big_file.h"

typedef struct BUFFER_ENTRADA{
    ITEM_VENDA* vetor;
    int tamanho;
    int posicao;
    FILE* file;
}ENTRADA;

ENTRADA* entrada_criar(char* nome_arquivo, int qnt_registros);

int entrada_proximo(ENTRADA* buffer);
    
bool entrada_consumir(ENTRADA*  buffer,ITEM_VENDA* saida);

int entrada_vazio(ENTRADA* buffer);

void entrada_destruir(ENTRADA** buffer);

void entrada_imprimir(ENTRADA* buffer);

bool getFromFile(ENTRADA* buffer);