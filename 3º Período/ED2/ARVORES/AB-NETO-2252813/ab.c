#include "ab.h"
#include<stdio.h>
#include <stdlib.h>

AB* AB_Buscar(AB* A, int dado){
    if(A == NULL)
        return NULL;
    if(A->dado == dado)
        return A;
        if(dado< A->dado)
            return AB_Buscar(A->esq, dado);
        return AB_Buscar(A->dir, dado);
}

AB* AB_Criar(int dado, AB* e, AB* d){
    AB* n;
    
    n = malloc(sizeof(struct AB));
    n->dado = dado;
    n->esq = e;
    n->dir = d;

    return n;
}

void AB_Inserir(AB **A, int dado){
    if((*A) == NULL){
        *A = AB_Criar(dado, NULL, NULL);
        return;
    }else{
        if(dado< (*A)->dado){
            AB_Inserir(&(*A)->esq, dado);
        }else{
            AB_Inserir(&(*A)->dir, dado);
        }
    }
};

void AB_Imprimir(AB* A, int num, char pos){        //num é referente ao numero de TAB que precisa ser impressos para das o aspecto de "galhos"
    if(A==NULL) return;
    int x, aux = 0;
    for(x=0; x<num; x++){
        printf("       ");  //impressão das tabulações
    }
    if(A!=NULL){
        printf("(%c) %d\n", pos, A->dado); //impressao do dado
    }
    if(A->esq != NULL){                 //se houver filho à esquerda
        AB_Imprimir(A->esq, num+=1, 'e');//imprime ele com uma tabulação a mais
        aux = 1;                           //define 1 pro auxiliar pra saber q o proximo nó é um filho esquerdo
    }
    if(A->dir != NULL){             //se houver filho à direita
        if (!aux) num+=1;           //diminui 1 na tabulação se o nó atual for um filho à direira de um nó anterior, ou seja, maior valor doq o anterior 
        AB_Imprimir(A->dir, num, 'd');//imprime ele com uma tabulação a mais SE ele for filho à direita, se nao imprime com a mesma tabulação anterior
        aux = 0;                    //define 1 pro auxiliar pra saber q o proximo nó é um filho direito
    }
    
};

void AB_Destruir(AB* A){
    if(A == NULL)
        return;
    AB_Destruir(A->esq);
    AB_Destruir(A->dir);
    free(A);
}

AB* filho(AB** A){ //SUBSTITUI PELO MENOR VALOR
    if((*A)->esq != NULL){//se tiver filho à esquerda
        return filho(&(*A)->esq);//retorna a chamada recursiva da propria função passando o endereço de memória do nó filho esquerdo (menor valor)
    }else{
        AB *tmp = *A;
        if((*A)->dir != NULL){ // Se houver filho à direita, ou seja, com um valor MAIOR que o nó, 
             *A = (*A)->dir;//ele "puxa" esse valor pra cima e substitui o nó
        } else{
            *A = NULL;// Se não houver filhos, o nó simplesmente recebe nulo
        }
        return tmp;
    }
}

void AB_Remover(AB **A, int dado){
    if (*A == NULL){
        return;
    }
    if((*A)->dado == dado){ //verificando se chegou no nó desejado
        if((*A)->dir == NULL && (*A)->esq == NULL){ //SE O NÓ FOR A FOLHA
            *A=NULL;
            return;
        }
        if((*A)->dir != NULL && (*A)->esq == NULL){ //SE O NÓ TIVER FILHO MAIOR Q ELE
            *A = (*A)->dir;
            (*A)->dir = NULL;
            return;
        }
        if((*A)->dir == NULL && (*A)->esq != NULL){ //SE O NÓ TIVER FILHO MENOR Q ELE
            *A = (*A)->esq;
            (*A)->esq = NULL;
            return;
        }
        AB* tmp = filho(&(*A)->dir); 
        tmp->esq = (*A)->esq;
        tmp->dir = (*A)->dir;
        *A = tmp;           //SUBSTITUINDO O NÓ A, PELO SEU SUCESSOR
        tmp = NULL;
        return;
    }else if((*A)->dado > dado){    //se ainda nao chegou no nó desejado, e o valor do nó atual ainda for MAIOR que o desejado, desce para a ESQUERDA
        AB_Remover(&(*A)->esq, dado);
    }else{
        AB_Remover(&(*A)->dir, dado); //se ainda nao chegou no nó desejado, e o valor do nó atual ainda for MENOR que o desejado, desce para a DIREITA
    } 
};
