#include <stdio.h>
#include "big_file.h"

int main(int argc, char** argv){
    printf("sizeof(ITEM_VENDA) = %ld\n", sizeof(ITEM_VENDA));
    gerar_array_iv("teste.dat", 1572864, 42);
}
