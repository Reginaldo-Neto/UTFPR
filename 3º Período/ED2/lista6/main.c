#include <stdio.h>
#include <stdlib.h>
#include "list/ilist.h"
#include "hash/THED.h"

void valuesForTable(int n,int m,int seed){
  THED* hash = THED_inserir_n_aleatorios(n,m,seed);

  int max = THED_MaisLonga(hash);
  int min = THED_MaisCurta(hash);
  float media = THED_TamMedio(hash);

  printf("MIN: %d, MAX: %d, Media:%f\n",min,max,media);
}

int main(){
  // int n=100,m=10,seed=42;
  printf("$$$$$$$$$$$$$$$$/ M COMPOSTO /$$$$$$$$$$$$$$$$\n");
  printf("========/ M == 10 /========\n");
  printf("N == 1000   | ");
  valuesForTable(1000,10,42);
  printf("N == 10000  | ");
  valuesForTable(10000,10,42);
  printf("N == 50000  | ");
  valuesForTable(50000,10,42);
  printf("N == 100000 |");
  valuesForTable(100000,10,42);
  printf("========/ M == 100 /========\n");
  printf("N == 10000  | ");
  valuesForTable(10000,100,42);
  printf("N == 50000  | ");
  valuesForTable(50000,100,42);
  printf("N == 100000 |");
  valuesForTable(100000,100,42);
  
  printf("========/ M == 500 /========\n");
  printf("N == 50000  | ");
  valuesForTable(50000,500,42);
  printf("N == 100000 |");
  valuesForTable(100000,500,42);
  
  printf("========/ M == 1000 /========\n");
  printf("N == 100000 |");
  valuesForTable(100000,1000,42);

  printf("$$$$$$$$$$$$$$$$/ M PRIMO /$$$$$$$$$$$$$$$$\n");
  printf("========/ M == 7 /========\n");
  printf("N == 1000   | ");
  valuesForTable(1000,7,42);
  printf("N == 10000  | ");
  valuesForTable(10000,7,42);
  printf("N == 50000  | ");
  valuesForTable(50000,7,42);
  printf("N == 100000 |");
  valuesForTable(100000,7,42);
  printf("========/ M == 97 /========\n");
  printf("N == 10000  | ");
  valuesForTable(10000,97,42);
  printf("N == 50000  | ");
  valuesForTable(50000,97,42);
  printf("N == 100000 |");
  valuesForTable(100000,97,42);
  
  printf("========/ M == 499 /========\n");
  printf("N == 50000  | ");
  valuesForTable(50000,499,42);
  printf("N == 100000 |");
  valuesForTable(100000,499,42);
  
  printf("========/ M == 997 /========\n");
  printf("N == 100000 |");
  valuesForTable(100000,997,42);

  printf("\n\n\n@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ ESPERADO @@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n\n\n");
  
  printf("$$$$$$$$$$$$$$$$/ M COMPOSTO /$$$$$$$$$$$$$$$$\n");
  printf("========/ M == 10 /========\n");
  printf("N == 1000    [%d] || ",(1000/10));
  printf("N == 10000   [%d] || ",(10000/10));
  printf("N == 50000   [%d] || ",(5000/10));
  printf("N == 100000  [%d] ||\n",(100000/10));
  printf("========/ M == 100 /========\n");
  printf("N == 10000   [%d] || ",(10000/100));
  printf("N == 50000   [%d] || ",(50000/100));
  printf("N == 100000  [%d] ||\n",(100000/100));
  
  printf("========/ M == 500 /========\n");
  printf("N == 50000   [%d] || ",(50000/500));
  printf("N == 100000  [%d] ||\n",(100000/500));
  
  printf("========/ M == 1000 /========\n");
  printf("N == 100000  [%d] ||\n",(100000/1000));

  printf("$$$$$$$$$$$$$$$$/ M PRIMO /$$$$$$$$$$$$$$$$\n");
  printf("========/ M == 7 /========\n");
  printf("N == 1000    [%d] || ",(1000/7));
  printf("N == 10000   [%d] || ",(10000/7));
  printf("N == 50000   [%d] || ",(50000/7));
  printf("N == 100000  [%d] ||\n",(100000/7));
  printf("========/ M == 97 /========\n");
  printf("N == 10000   [%d] || ",(10000/97));
  printf("N == 50000   [%d] || ",(50000/97));
  printf("N == 100000  [%d] ||\n",(100000/97));
  
  printf("========/ M == 499 /========\n");
  printf("N == 50000   [%d] || ",(50000/499));
  printf("N == 100000  [%d] ||\n",(100000/499));
  
  printf("========/ M == 997 /========\n");
  printf("N == 100000  [%d] ||\n",(100000/997));
  
  return 0;
}