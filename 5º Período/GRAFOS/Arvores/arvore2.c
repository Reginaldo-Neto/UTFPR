#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define true 1
#define false 0
#define MAXSIZE 100

typedef struct noArv{

	int valor;
	struct noArv *esquerda;
	struct noArv *direita;

} noArv;

void infixa(noArv *);
void prefixa(noArv *);
void posfixa(noArv *);
void printInfixa(int *);
void printPrefixa(int *);
void printPosfixa(int *);
noArv* push(noArv *, int );
_Bool busca(noArv *, int , noArv*);
noArv* tira();


int valoresInfixa[MAXSIZE] = { 0 };
int valoresPosfixa[MAXSIZE] = { 0 };
int valoresPrefixa[MAXSIZE] = { 0 };

int i = 0;
int j = 0;
int k = 0;
noArv* item;
void teste(noArv *no)
{

	if (no)
	{

		teste(no->esquerda);
		printf("%c ", no->valor);
		teste(no->direita);

	}

}

void main ()
{

	int comando[20], valor;

	noArv *no = NULL;
	while (scanf("%s%*c", comando) != EOF)
	{

		if (strcmp(comando, "I") == 0)
		{

			scanf("%c", &valor);
			no = push(no, valor);

		}
		else if (strcmp(comando, "R") == 0){
			scanf("%c", &valor);
			no=tira(no, valor);
		}
		else if (strcmp(comando, "INFIXA") == 0)
			infixa(no), printInfixa(valoresInfixa);
		else if (strcmp(comando, "PREFIXA") == 0)
			prefixa(no), printPrefixa(valoresPrefixa);
		else if (strcmp(comando, "P") == 0)
		{

			scanf("%c", &valor);
			if (busca(no, valor, item))
				printf("%c existe\n", valor);
			else
				printf("%c nao existe\n", valor);
		}
		else
			posfixa(no), printPosfixa(valoresPosfixa);

	}

}

noArv* push(noArv *no, int valor)
{

	if (!no)
	{

		no = (noArv *) malloc(sizeof(noArv));
		no->valor = valor;
		no->direita = no->esquerda = NULL;

	}
	else if (no->valor > valor)
		no->esquerda = push(no->esquerda, valor);
	else
		no->direita = push(no->direita, valor);

	return no;

}

_Bool busca(noArv *no, int valor, noArv* item)
{

	_Bool direita, esquerda;

	if (!no)
		return false;

	if (no->valor == valor)
		return true;

	if (no->valor > valor)
		esquerda = busca(no->esquerda, valor, item);
	else
		direita = busca(no->direita, valor, item);

}

void printInfixa(int *valors)
{

	int z;
	for (z = 0; z < i; ++z)
		if (!z)
			printf("%c", valoresInfixa[z]);
		else
			printf(" %c", valoresInfixa[z]);

	i = 0;
	printf("\n");

}

void printPrefixa(int *valors)
{

	int z;
	for (z = 0; z < k; ++z)
		if (!z)
			printf("%c", valoresPrefixa[z]);
		else
			printf(" %c", valoresPrefixa[z]);

	k = 0;
	printf("\n");

}

void printPosfixa(int *valors)
{

	int z;
	for (z = 0; z < j; ++z)
		if (!z)
			printf("%c", valoresPosfixa[z]);
		else
			printf(" %c", valoresPosfixa[z]);

	j = 0;
	printf("\n");

}

void infixa(noArv *no)
{

	if (no)
	{

		infixa(no->esquerda);
		valoresInfixa[i++] = no->valor;
		infixa(no->direita);

	}

}

void posfixa(noArv *no)
{

	if (no)
	{

		posfixa(no->esquerda);
		posfixa(no->direita);
		valoresPosfixa[j++] = no->valor;

	}

}

void prefixa(noArv *no)
{

	if (no)
	{

		valoresPrefixa[k++] = no->valor;
		prefixa(no->esquerda);
		prefixa(no->direita);

	}

}

noArv * findMax(noArv *root)
{

	if(!root)
		return NULL;
	else if (!root->direita)
		return root;
	else
		return findMax(root->direita);

}

noArv * tira(noArv *raiz, int x)
{

	noArv *tmp;
	if (!raiz)
		return NULL;
	else if (raiz->valor > x)
		raiz->esquerda = tira(raiz->esquerda, x);
	else if (raiz->valor < x)
		raiz->direita = tira(raiz->direita, x);
	else if (raiz->esquerda && raiz->direita)
	{

		tmp = findMax(raiz->esquerda);
		raiz->valor = tmp->valor;
		raiz->esquerda = tira(raiz->esquerda, raiz->valor);

	}
	else
	{

		tmp = raiz;
		if (!raiz->esquerda)
			raiz = raiz->direita;
		else if (!raiz->direita)
			raiz = raiz->esquerda;

		free(tmp);

	}

	return raiz;

}