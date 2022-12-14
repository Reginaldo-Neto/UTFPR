#include "bufferSaida.h"

SAIDA* saida_criar(char* nome_arquivo, int qnt_registros){
    FILE* file;
    file = fopen(nome_arquivo,"ab");
    
    SAIDA* buffer = malloc(sizeof(SAIDA));
    buffer->posicao = 0;
    buffer->tamanho = qnt_registros;
    buffer->file = file;
    buffer->vetor = malloc(qnt_registros*sizeof(ITEM_VENDA));
    return buffer;
};

void saida_inserir(ITEM_VENDA* registro, SAIDA* buffer){
    if(buffer->posicao == buffer->tamanho){
        saida_despejar(buffer);
    }
    buffer->vetor[buffer->posicao] = *registro;
    buffer->posicao++;
}

void saida_despejar(SAIDA *buffer){
    fwrite(buffer->vetor,sizeof(ITEM_VENDA),buffer->posicao,buffer->file);
    buffer->posicao = 0;
}

void saida_destruir(SAIDA** buffer){
  SAIDA* trash = *buffer;
  fclose(trash->file);
  free(trash->vetor);
  free(trash);
  *buffer = NULL;
}

void saida_imprimir(SAIDA* buffer){
  int max=buffer->posicao;
  printf("posicao: %d\n",buffer->posicao);
  printf("tamanho: %d\n",buffer->tamanho);

  if (buffer->posicao==-1){
    max = buffer->tamanho;
    
  }

  printf("{");
  int i;
  for (i = 0; i < max; i++){
    printf("[id:%d], ",buffer->vetor[i].id);
  }
  printf("}\n");
}