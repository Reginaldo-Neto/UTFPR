#include <stdio.h>
#include "ab.h"

int main(int argc, char** argv){
    printf("\n--------------Exercicio A--------------\n");
    AB *a = AB_Criar(70, NULL, NULL);
    printf("--------------ARVORE COMPLETA--------------\n");
    AB_Inserir(&a, 39);
    AB_Inserir(&a, 88);
    AB_Imprimir(a, 0, 'r');
    printf("--------------ARVORE APOS REMOCAO--------------\n");
    AB_Remover(&a, 70);
    AB_Imprimir(a, 0, 'r');
    AB_Destruir(a);
    printf("\n--------------Exercicio B--------------\n");
    AB *b = AB_Criar(10, NULL, NULL);
    printf("--------------ARVORE COMPLETA--------------\n");
    AB_Inserir(&b, 4);
    AB_Inserir(&b, 20);
    AB_Inserir(&b, 6);
    AB_Inserir(&b, 2);
    AB_Inserir(&b, 3);
    AB_Inserir(&b, 5);
    AB_Inserir(&b, 7);
    AB_Imprimir(b, 0, 'r');   
    printf("--------------ARVORE APOS REMOCAO--------------\n");
    AB_Remover(&b, 10);
    AB_Remover(&b, 4);
    AB_Remover(&b, 5);
    AB_Imprimir(b, 0, 'r');
    AB_Destruir(b);
    printf("\n--------------Exercicio C--------------\n");
    AB *c = AB_Criar(30, NULL, NULL);
    printf("--------------ARVORE COMPLETA--------------\n");
    AB_Inserir(&c, 50);
    AB_Inserir(&c, 40);
    AB_Inserir(&c, 47);
    AB_Inserir(&c, 15);
    AB_Inserir(&c, 20);
    AB_Inserir(&c, 25);
    AB_Inserir(&c, 17);
    AB_Inserir(&c, 19);
    AB_Inserir(&c, 4);
    AB_Inserir(&c, 7);
    AB_Inserir(&c, 0);
    AB_Imprimir(c, 0, 'r');
    printf("--------------ARVORE APOS REMOCAO--------------\n");
    AB_Remover(&c, 0);
    AB_Remover(&c, 30);
    AB_Remover(&c, 15);
    AB_Remover(&c, 20);
    AB_Imprimir(c, 0, 'r');
    AB_Destruir(c);

}
