#include "kway.h"

bool retorna_menor(int qnt,ENTRADA* entradas[qnt],ITEM_VENDA* saida){
  int proxMenor=0;
  int menorId=INT_MAX;
  int id=-1;
  
  bool allEmpty = true;
  int i;
  for (i = 0; i < qnt; i++){
    if (entradas[i]->tamanho != 0){
      allEmpty = false;
      id = entrada_proximo(entradas[i]);
      if (id < menorId){
        menorId = id;
        proxMenor = i;
      }
    }
  }

  if (allEmpty) return false;
  
  return entrada_consumir(entradas[proxMenor],saida);
}

void kway(int qnt,ENTRADA* entradas[qnt], SAIDA* saida){
  ITEM_VENDA* aux = malloc(sizeof(ITEM_VENDA));

  while (retorna_menor(qnt,entradas,aux)){
    // printf("AUX ID: %d",aux->id);
    if (aux->id != INT_MAX) saida_inserir(aux,saida);
  }
  free(aux);
  printf("TODOS OS ARQUIVOS FORAM CONSUMIDOS!\n");
}