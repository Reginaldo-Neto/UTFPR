#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
typedef struct no
{
    struct no *esq;
    struct no *dir;
    char valor;
} no;

no *insere(no *raiz, char letra)
{
    if (!raiz)
    {
        raiz = (no *) malloc(sizeof(no));
        raiz->valor = letra;
        raiz->dir = NULL;
        raiz->esq = NULL;
    }
    else if (raiz->valor < letra)
    {
        raiz->dir = insere(raiz->dir, letra);
    }
    else
    {
        raiz->esq = insere(raiz->esq, letra);
    }
}

_Bool procura(struct no *raiz, char letra)
{
    _Bool fdir, fesq;
    if (!raiz)
    {
        return false;
    }
    if (raiz->valor == letra)
    {
        return true;
    }
    if (raiz->valor < letra)
    {
        fdir = procura(raiz->dir, letra);
    }
    else
    {
        fesq = procura(raiz->esq, letra);
    }
}

void prefixa(no *raiz)
{
    printf("%c ", raiz->valor);
    prefixa(raiz->esq);
    prefixa(raiz->dir);
};

void infixa(no *raiz)
{
    infixa(raiz->esq);
    printf("%c ", raiz->valor);
    infixa(raiz->dir);
};

void posfixa(no *raiz)
{
    posfixa(raiz->esq);
    posfixa(raiz->dir);
    printf("%c ", raiz->valor);
};
int main()
{
    /**PRÉ-ORDEM (PREFIXA)
     * RAIZ - ESQ - DIR
     *
     * EM ORDEM (INFIXA)
     * ESQ - RAIZ - DIR
     *
     * PÓS ORDEM (POSFIXA)
     * ESQ - DIR - RAIZ
     */
    no *raiz;
    char *op;
    char letra;
    while (scanf("%s%*c", op) != EOF)
    {
        if (strcmp(op, "I") == 0)
        {
            raiz = insere(raiz, letra);
        }
        else if (strcmp(op, "P") == 0)
        {
            procura(raiz, letra);
        }
        else if (strcmp(op, "INFIXA") == 0)
        {
            infixa(raiz);
        }
        else if (strcmp(op, "PREFIXA") == 0)
        {
            prefixa(raiz);
        }
        else if (strcmp(op, "POSFIXA") == 0)
        {
            posfixa(raiz);
        }
    }
    return 0;
}