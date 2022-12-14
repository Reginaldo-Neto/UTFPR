#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>

#include "ilist.h"
#include "hashtable_ed.h"

int main(){
    int  seed=42, n, m;
    int curta, longa, media;

    n=1000, m=10;
    printf("----------------- TESTE 01 - N=1000 -----------------\n");
    THED* tabela = inserir_n_aleatorios(n, m, seed); 
    printf("M=10 \n");
    curta = THED_MaisCurta(tabela);
    printf("TAMANHO MAIS CURTO: %d\n", curta);
    longa = THED_MaisLonga(tabela);
    printf("TAMANHO MAIS LONGO: %d\n", longa);
    media = THED_TamMedio(tabela);
    printf("TAMANHO MEDIO: %d\n", media);
    
    printf("----------------- TESTE 01 - N=1000 -----------------\n");
    m=7;
    tabela = inserir_n_aleatorios(n, m, seed); 
    printf("M=7 \n");
    curta = THED_MaisCurta(tabela);
    printf("TAMANHO MAIS CURTO: %d\n", curta);
    longa = THED_MaisLonga(tabela);
    printf("TAMANHO MAIS LONGO: %d\n", longa);
    media = THED_TamMedio(tabela);
    printf("TAMANHO MEDIO: %d\n", media);

    printf("\n\n\n");
    //-----------------------------------------------------------------------------------------------------------------------------

    n=10000, m=10;
    printf("----------------- TESTE 02 - N=10000 -----------------\n");
    tabela = inserir_n_aleatorios(n, m, seed); 
    printf("M=10 \n");
    curta = THED_MaisCurta(tabela);
    printf("TAMANHO MAIS CURTO: %d\n", curta);
    longa = THED_MaisLonga(tabela);
    printf("TAMANHO MAIS LONGO: %d\n", longa);
    media = THED_TamMedio(tabela);
    printf("TAMANHO MEDIO: %d\n", media);
    
    printf("----------------- TESTE 02 - N=10000 -----------------\n");
    m=100;
    tabela = inserir_n_aleatorios(n, m, seed); 
    printf("M=100 \n");
    curta = THED_MaisCurta(tabela);
    printf("TAMANHO MAIS CURTO: %d\n", curta);
    longa = THED_MaisLonga(tabela);
    printf("TAMANHO MAIS LONGO: %d\n", longa);
    media = THED_TamMedio(tabela);
    printf("TAMANHO MEDIO: %d\n", media);

    m=7;
    printf("----------------- TESTE 02 - N=10000 -----------------\n");
    tabela = inserir_n_aleatorios(n, m, seed); 
    printf("M=7 \n");
    curta = THED_MaisCurta(tabela);
    printf("TAMANHO MAIS CURTO: %d\n", curta);
    longa = THED_MaisLonga(tabela);
    printf("TAMANHO MAIS LONGO: %d\n", longa);
    media = THED_TamMedio(tabela);
    printf("TAMANHO MEDIO: %d\n", media);
    
    printf("----------------- TESTE 02 - N=10000 -----------------\n");
    m=97;
    tabela = inserir_n_aleatorios(n, m, seed); 
    printf("M=97 \n");
    curta = THED_MaisCurta(tabela);
    printf("TAMANHO MAIS CURTO: %d\n", curta);
    longa = THED_MaisLonga(tabela);
    printf("TAMANHO MAIS LONGO: %d\n", longa);
    media = THED_TamMedio(tabela);
    printf("TAMANHO MEDIO: %d\n", media);

    printf("\n\n\n");
    //---------------------------------------------------------------------------------------------------------------

    n=50000, m=10;
    printf("----------------- TESTE 03 - N=50000 -----------------\n");
    tabela = inserir_n_aleatorios(n, m, seed); 
    printf("M=10 \n");
    curta = THED_MaisCurta(tabela);
    printf("TAMANHO MAIS CURTO: %d\n", curta);
    longa = THED_MaisLonga(tabela);
    printf("TAMANHO MAIS LONGO: %d\n", longa);
    media = THED_TamMedio(tabela);
    printf("TAMANHO MEDIO: %d\n", media);
    
    printf("----------------- TESTE 03 - N=50000 -----------------\n");
    m=100;
    tabela = inserir_n_aleatorios(n, m, seed); 
    printf("M=100 \n");
    curta = THED_MaisCurta(tabela);
    printf("TAMANHO MAIS CURTO: %d\n", curta);
    longa = THED_MaisLonga(tabela);
    printf("TAMANHO MAIS LONGO: %d\n", longa);
    media = THED_TamMedio(tabela);
    printf("TAMANHO MEDIO: %d\n", media);

    printf("----------------- TESTE 03 - N=50000 -----------------\n");
    m=500;
    tabela = inserir_n_aleatorios(n, m, seed); 
    printf("M=500 \n");
    curta = THED_MaisCurta(tabela);
    printf("TAMANHO MAIS CURTO: %d\n", curta);
    longa = THED_MaisLonga(tabela);
    printf("TAMANHO MAIS LONGO: %d\n", longa);
    media = THED_TamMedio(tabela);
    printf("TAMANHO MEDIO: %d\n", media);

    printf("----------------- TESTE 03 - N=50000 -----------------\n");
    m=7;
    tabela = inserir_n_aleatorios(n, m, seed); 
    printf("M=7 \n");
    curta = THED_MaisCurta(tabela);
    printf("TAMANHO MAIS CURTO: %d\n", curta);
    longa = THED_MaisLonga(tabela);
    printf("TAMANHO MAIS LONGO: %d\n", longa);
    media = THED_TamMedio(tabela);
    printf("TAMANHO MEDIO: %d\n", media);
    
    printf("----------------- TESTE 03 - N=50000 -----------------\n");
    m=97;
    tabela = inserir_n_aleatorios(n, m, seed); 
    printf("M=97 \n");
    curta = THED_MaisCurta(tabela);
    printf("TAMANHO MAIS CURTO: %d\n", curta);
    longa = THED_MaisLonga(tabela);
    printf("TAMANHO MAIS LONGO: %d\n", longa);
    media = THED_TamMedio(tabela);
    printf("TAMANHO MEDIO: %d\n", media);

    printf("----------------- TESTE 03 - N=50000 -----------------\n");
    m=499;
    tabela = inserir_n_aleatorios(n, m, seed); 
    printf("M=499 \n");
    curta = THED_MaisCurta(tabela);
    printf("TAMANHO MAIS CURTO: %d\n", curta);
    longa = THED_MaisLonga(tabela);
    printf("TAMANHO MAIS LONGO: %d\n", longa);
    media = THED_TamMedio(tabela);
    printf("TAMANHO MEDIO: %d\n", media);

    printf("\n\n\n");
    //---------------------------------------------------------------------------------------------------------------------------

    n=100000, m=10;
    printf("----------------- TESTE 04 - N=100000 -----------------\n");
    tabela = inserir_n_aleatorios(n, m, seed); 
    printf("M=10 \n");
    curta = THED_MaisCurta(tabela);
    printf("TAMANHO MAIS CURTO: %d\n", curta);
    longa = THED_MaisLonga(tabela);
    printf("TAMANHO MAIS LONGO: %d\n", longa);
    media = THED_TamMedio(tabela);
    printf("TAMANHO MEDIO: %d\n", media);
    
    printf("----------------- TESTE 04 - N=100000 -----------------\n");
    m=100;
    tabela = inserir_n_aleatorios(n, m, seed); 
    printf("M=100 \n");
    curta = THED_MaisCurta(tabela);
    printf("TAMANHO MAIS CURTO: %d\n", curta);
    longa = THED_MaisLonga(tabela);
    printf("TAMANHO MAIS LONGO: %d\n", longa);
    media = THED_TamMedio(tabela);
    printf("TAMANHO MEDIO: %d\n", media);

    printf("----------------- TESTE 04 - N=100000 -----------------\n");
    m=500;
    tabela = inserir_n_aleatorios(n, m, seed); 
    printf("M=500 \n");
    curta = THED_MaisCurta(tabela);
    printf("TAMANHO MAIS CURTO: %d\n", curta);
    longa = THED_MaisLonga(tabela);
    printf("TAMANHO MAIS LONGO: %d\n", longa);
    media = THED_TamMedio(tabela);
    printf("TAMANHO MEDIO: %d\n", media);
    
    printf("----------------- TESTE 04 - N=100000 -----------------\n");
    m=1000;
    tabela = inserir_n_aleatorios(n, m, seed); 
    printf("M=1000 \n");
    curta = THED_MaisCurta(tabela);
    printf("TAMANHO MAIS CURTO: %d\n", curta);
    longa = THED_MaisLonga(tabela);
    printf("TAMANHO MAIS LONGO: %d\n", longa);
    media = THED_TamMedio(tabela);
    printf("TAMANHO MEDIO: %d\n", media);
    
    printf("----------------- TESTE 04 - N=100000 -----------------\n");
    m=7;
    tabela = inserir_n_aleatorios(n, m, seed); 
    printf("M=7 \n");
    curta = THED_MaisCurta(tabela);
    printf("TAMANHO MAIS CURTO: %d\n", curta);
    longa = THED_MaisLonga(tabela);
    printf("TAMANHO MAIS LONGO: %d\n", longa);
    media = THED_TamMedio(tabela);
    printf("TAMANHO MEDIO: %d\n", media);
    
    printf("----------------- TESTE 04 - N=100000 -----------------\n");
    m=97;
    tabela = inserir_n_aleatorios(n, m, seed); 
    printf("M=97 \n");
    curta = THED_MaisCurta(tabela);
    printf("TAMANHO MAIS CURTO: %d\n", curta);
    longa = THED_MaisLonga(tabela);
    printf("TAMANHO MAIS LONGO: %d\n", longa);
    media = THED_TamMedio(tabela);
    printf("TAMANHO MEDIO: %d\n", media);

    printf("----------------- TESTE 04 - N=100000 -----------------\n");
    m=499;
    tabela = inserir_n_aleatorios(n, m, seed); 
    printf("M=499 \n");
    curta = THED_MaisCurta(tabela);
    printf("TAMANHO MAIS CURTO: %d\n", curta);
    longa = THED_MaisLonga(tabela);
    printf("TAMANHO MAIS LONGO: %d\n", longa);
    media = THED_TamMedio(tabela);
    printf("TAMANHO MEDIO: %d\n", media);
    
    printf("----------------- TESTE 04 - N=100000 -----------------\n");
    m=997;
    tabela = inserir_n_aleatorios(n, m, seed); 
    printf("M=997 \n");
    curta = THED_MaisCurta(tabela);
    printf("TAMANHO MAIS CURTO: %d\n", curta);
    longa = THED_MaisLonga(tabela);
    printf("TAMANHO MAIS LONGO: %d\n", longa);
    media = THED_TamMedio(tabela);
    printf("TAMANHO MEDIO: %d\n", media);
}
