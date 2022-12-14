#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "arn.h"

int main(int argc, char **argv, char**envp){
	clock_t time;
	time = clock();
	ARN* A = NULL;
	int n=10000, x, profundidade, fim;
	int v[n];
	fim=n;
    for(x=0; x<n; x++){
       v[x]=x;
	}
    profundidade = ARN_Sort(v, n);
	printf("PROFUNDIDADE: %d", profundidade);
	time = clock() - time;
    printf("\nTEMPO GASTO ORDEM CRESCENTE: %d SEGUNDOS", time);
//-------------------------------------------------------------------------------------------
	time = clock();
	fim=n;
	for(x=0; x<n; x++){
       v[x]=fim;
	   fim--;
    }
	profundidade = ARN_Sort(v, n);
	time = clock() - time;
    printf("\nTEMPO GASTO ORDEM DECRESCENTE: %d SEGUNDOS", time);
}
