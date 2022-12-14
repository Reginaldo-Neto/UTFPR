#include "split.h"

int partition(int left, int right, ITEM_VENDA* array){
  int lp= left-1;

  ITEM_VENDA aux;

  for (int rp = left; rp < right; rp++){
    if(array[rp].id <= array[right].id){
      lp++; 
      aux = array[lp];
      array[lp] = array[rp];
      array[rp]= aux;
    }
  }
  
  int pivo = lp+1;

  aux =array[pivo];
  array[pivo] = array[right];
  array[right] = aux;

  return pivo;
}

void quicksort(int left, int right, ITEM_VENDA* array){

  if (left < right){
    int pivo = partition(left,right, array);
    quicksort(left,pivo-1,array);
    quicksort(pivo+1,right,array);
  }
  
}

void printItems(ITEM_VENDA* array,int size){
  printf("[");
  for (int i = 0; i < size; i++){
    printf("[ID: %d], ",array[i].id);
  }
  printf("]\n");
  
}

int splitFile(char* fileName, int outSize){
  FILE* file;
  file = fopen(fileName,"rb");
  if (!file){
    printf("[ERRO]: Arquivo \"%s\" nao existe",fileName);
   return 0; 
  }

  char outputName[100];
  int i=0, filei=0;
  ITEM_VENDA* items = malloc(outSize*sizeof(ITEM_VENDA));

  FILE* output;
  while (!feof(file)){
    fread(&items[i],sizeof(ITEM_VENDA),1,file);
    i++;
    if (i==outSize){
      quicksort(0,outSize-1,items);
      //cria um arquivo menor
      sprintf(outputName,"out%d.bin",filei);
      output = fopen(outputName,"wb");
      fwrite(items,i,sizeof(ITEM_VENDA),output);
      filei++;
      i=0;
    }
  }
  if (i>0){
    quicksort(0,i-1,items);
    sprintf(outputName,"out%d.bin",filei);
    output = fopen(outputName,"wb");
    fwrite(items,i,sizeof(ITEM_VENDA),output);
    filei++;
  }
  
  return filei;
}