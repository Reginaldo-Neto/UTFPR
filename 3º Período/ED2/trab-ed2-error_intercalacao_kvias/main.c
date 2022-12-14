#include <stdio.h>
#include <stdlib.h>
#include "buffers/bufferEntrada.h"
#include "buffers/bufferSaida.h"
#include "splitFile/split.h"
#include "merge/kway.h"

int tamanho_arquivo(char* nome_arquivo){
  int size=0;
  FILE* file;

  ITEM_VENDA* x = malloc(sizeof(ITEM_VENDA));
  file = fopen(nome_arquivo,"rb");
  while (!feof(file)){
    fread(x,sizeof(ITEM_VENDA),1,file);
    size++;
  }
  fclose(file);
  return size;
}

void intercalacao_kvias(char* nome_entrada, char* nome_saida, int B, int S){
  int E = tamanho_arquivo(nome_entrada); // tamanho do arquivo de entrada
  int K = (int)((float)E) / ((float)B); // qnt de arquivos temporarios = (int)(E/B)
  printf("AQUIIIIIIIIII %d\n",K);
  int Tentrada = (int)(((B-S)/K)/1024); // (int)(((B-S)/K)/1024)
  int qntFiles = splitFile(nome_entrada,Tentrada);
  printf("E=%d K=%d Tentrada=%d qntFiles=%d\n",E,K,Tentrada,qntFiles);
}

int main(){
  remove("saida.bin");
  int B = 8388608;
  int S = (int)(B/8);
  intercalacao_kvias("entrada.dat","saida.bin",B,S);
  // int TAMANHO = 50000;
  // int entradaQnt = splitFile("entrada.dat",TAMANHO);
  // printf("ARQUIVOS TEMPORARIOS CRIADOS\n");  

  // int TAMANHOBuffer = (int)TAMANHO/entradaQnt;
  // SAIDA* saida = saida_criar("saida.bin",TAMANHOBuffer);
  // printf("BUFFER DE SAIDA CRIADO\n");

  
  // ENTRADA* entradas[entradaQnt];
  // char nomeEntrada[100];
  // for (int i = 0; i < entradaQnt; i++){
  //   sprintf(nomeEntrada,"out%d.bin",i);
  //   entradas[i] = entrada_criar(nomeEntrada,TAMANHOBuffer);
  // }
  // printf("BUFFERS DE ENTRADA CRIADOS\n");

  // kway(entradaQnt,entradas,saida);
  // saida_despejar(saida);
  // printf("ARQUIVO FINAL COMPLETO\n");  
  
  // saida_destruir(&saida);
  // for (int i = 0; i < entradaQnt; i++){
  //   entrada_destruir(&entradas[i]);
  //   sprintf(nomeEntrada,"out%d.bin",i);
  //   remove(nomeEntrada);
  // }
  // printf("BUFFERS E ARQUIVOS TEMPORARIOS DELETADOS\n");

  // ENTRADA* teste = entrada_criar("saida.bin",50);
  // entrada_imprimir(teste);
  // entrada_destruir(&teste);
  return 0;
}