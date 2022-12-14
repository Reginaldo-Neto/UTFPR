
#include "bufferEntrada.h"


// TERMINADO
bool getFromFile(ENTRADA* buffer){
  if (feof(buffer->file)) {
    buffer->posicao = -1;
    buffer->tamanho = 0;
    return false;
  };
  
  
  int i=0;
  while (i<buffer->tamanho){
    if (feof(buffer->file)){
      buffer->tamanho = i-1;
      break;
    }
    fread(&buffer->vetor[i],sizeof(ITEM_VENDA),1,buffer->file);
    i++;
  }

  buffer->posicao = 0;
  return true;
}

// EXCLUIR DEPOIS
void aloca_espaco(char* nome_arquivo){
  FILE* file;
  ITEM_VENDA item;

  file = fopen(nome_arquivo,"rb");
  if (!file)return;

  for (int i=1; i <= 10; i++){
			fread(&item,sizeof(ITEM_VENDA),1,file);
			printf("ID:%d\n",item.id);
			printf("ID_VENDA:%d\n",item.id_venda);
			printf("DATA:%d\n",item.data);
		}
		fclose(file);
  
}


// TERMINADO
ENTRADA* entrada_criar(char* nome_arquivo, int qnt_registros){
  FILE* file;
  file = fopen(nome_arquivo,"rb");
  if (!file){
    printf("[ERRO]: Arquivo \"%s\" nao existe",nome_arquivo);
   return NULL; 
  }
  
  ENTRADA* buffer = malloc(sizeof(ENTRADA));
  buffer->posicao = 0;
  buffer->tamanho = qnt_registros;
  buffer->file = file;
  buffer->vetor = malloc(sizeof(ITEM_VENDA)*qnt_registros);
  getFromFile(buffer);

  return buffer;
}


// TERMINADO
int entrada_proximo(ENTRADA* buffer){
    return buffer->vetor[buffer->posicao].id;
}

// TERMINADO
bool entrada_consumir(ENTRADA*  buffer,ITEM_VENDA* saida){
  if (entrada_vazio(buffer)) return false;
  
    
    *saida = buffer->vetor[buffer->posicao];

    buffer->posicao++;
    if (buffer->posicao == buffer->tamanho){
      if(!getFromFile(buffer)) return false;
    }
    return true;
}

// TERMINADO
int entrada_vazio(ENTRADA* buffer){
  if (buffer->posicao == -1){
    return 1;
  }
  return 0;
}

// TERMINADO
void entrada_imprimir(ENTRADA* buffer){
  
  printf("posicao: %d\n",buffer->posicao);
  printf("tamanho: %d\n",buffer->tamanho);

  if (buffer->posicao==-1){
    printf("{ - }\n");
    return;
  }

  printf("{");
  for (int i = buffer->posicao; i < buffer->tamanho; i++){
    printf("[id:%d], ",buffer->vetor[i].id);
  }
  printf("}\n");
}


void entrada_destruir(ENTRADA** buffer){
  ENTRADA* trash = *buffer;
  fclose(trash->file);
  free(trash->vetor);
  free(trash);
  *buffer = NULL;
}