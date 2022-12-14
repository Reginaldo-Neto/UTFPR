#ifndef __ARN_H__
#define __ARN_H__

typedef enum {
    C_VERMELHO,
    C_PRETO
} ARN_COR;

typedef struct ARN{
    struct ARN* esq;
    struct ARN* dir;
    ARN_COR cor;
    int valor;
    int chave;
} ARN;

ARN* ARN_Criar(int chave, int valor);
void ARN_Inserir(ARN **A, int chave, int valor);
void ARN_Inserir_R(ARN **A, int chave, int valor);
int ARN_Imprimir(ARN* A, int nivel, char lado, int retorno);

#endif
