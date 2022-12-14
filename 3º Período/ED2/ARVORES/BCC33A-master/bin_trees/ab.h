#ifndef __AB_H__
#define __AB_H__

typedef struct AB{
    struct AB *esq;
    struct AB *dir;
    int dado;
} AB;

AB* AB_Buscar_Ant(AB* A, int dado, char* pos, char* e, char* d);
AB* AB_Buscar(AB *A, int dado);
AB* AB_Criar(int dado, AB* e, AB* d);
void AB_Inserir(AB **A, int dado);

void AB_Remover(AB **A, int chave);
void AB_Imprimir(AB* A, int num, char pos);
void AB_Destruir(AB* A);
void AB_Sort(int *v, int n);
int AB_Sort_R(int *v, int n, AB *A, int x);
#endif