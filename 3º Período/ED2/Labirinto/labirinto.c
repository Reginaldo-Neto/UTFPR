//CÓDIGO FEITO POR REGINALDO GREGÓRIO DE SOUZA NETO		RA: 2252813
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define A 10
#define B 10

void labirinto(int lab[A][B], int lin, int col, char cam[A][B]){
	if(lin == 9 && col == 9){
	int i, j;
	for(i=0; i<A; i++){
		for(j=0; j<B; j++){
			printf("%c ", cam[i][j]);
		}
		printf("\n");
	}
		return;
	}else if(lab[lin+1][col]==0 && lin+1<10){//BAIXO
		lin++;
		cam[lin][col]=".";
		//printf("Baixo %d %d\n", lin, col);
		labirinto(lab, lin, col, cam);
				
	}else if(lab[lin][col+1]==0 && col+1<10){//DIREITA
		col++;
		cam[lin][col]=".";
		//printf("Direita %d %d\n", lin, col);
		labirinto(lab, lin, col, cam);
	}else if(lab[lin-1][col]==0 && lin-1>=0){//CIMA
		lin--;
		cam[lin][col]=".";
		//printf("Cima %d %d\n", lin, col);
		labirinto(lab, lin, col, cam);
	}else if(lab[lin][col-1]==0 && col-1>=0){//ESQUERDA
		col--;
		cam[lin][col]=".";
		//printf("Esquerda %d %d\n", lin, col);
		labirinto(lab, lin, col, cam);
	}
}

int main(){
	 FILE* arq;

    arq = fopen("entrada.txt", "r");

    if(arq == NULL){
        printf("erro ao acessar o arquivo %s\n", "entrada.txt");
        exit(EXIT_FAILURE);
    }

    int x[A][B];
	char cam[A][B];

    fscanf(arq, "%d %d %d %d %d %d %d %d %d %d\n", &x[0][0], &x[0][1], &x[0][2], &x[0][3], &x[0][4], &x[0][5], &x[0][6], &x[0][7], &x[0][8], &x[0][9]);
    fscanf(arq, "%d %d %d %d %d %d %d %d %d %d\n", &x[1][0], &x[1][1], &x[1][2], &x[1][3], &x[1][4], &x[1][5], &x[1][6], &x[1][7], &x[1][8], &x[1][9]);
    fscanf(arq, "%d %d %d %d %d %d %d %d %d %d\n", &x[2][0], &x[2][1], &x[2][2], &x[2][3], &x[2][4], &x[2][5], &x[2][6], &x[2][7], &x[2][8], &x[2][9]);
    fscanf(arq, "%d %d %d %d %d %d %d %d %d %d\n", &x[3][0], &x[3][1], &x[3][2], &x[3][3], &x[3][4], &x[3][5], &x[3][6], &x[3][7], &x[3][8], &x[3][9]);
    fscanf(arq, "%d %d %d %d %d %d %d %d %d %d\n", &x[4][0], &x[4][1], &x[4][2], &x[4][3], &x[4][4], &x[4][5], &x[4][6], &x[4][7], &x[4][8], &x[4][9]);
    fscanf(arq, "%d %d %d %d %d %d %d %d %d %d\n", &x[5][0], &x[5][1], &x[5][2], &x[5][3], &x[5][4], &x[5][5], &x[5][6], &x[5][7], &x[5][8], &x[5][9]);
    fscanf(arq, "%d %d %d %d %d %d %d %d %d %d\n", &x[6][0], &x[6][1], &x[6][2], &x[6][3], &x[6][4], &x[6][5], &x[6][6], &x[6][7], &x[6][8], &x[6][9]);
    fscanf(arq, "%d %d %d %d %d %d %d %d %d %d\n", &x[7][0], &x[7][1], &x[7][2], &x[7][3], &x[7][4], &x[7][5], &x[7][6], &x[7][7], &x[7][8], &x[7][9]);
    fscanf(arq, "%d %d %d %d %d %d %d %d %d %d\n", &x[8][0], &x[8][1], &x[8][2], &x[8][3], &x[8][4], &x[8][5], &x[8][6], &x[8][7], &x[8][8], &x[8][9]);
    fscanf(arq, "%d %d %d %d %d %d %d %d %d %d\n", &x[9][0], &x[9][1], &x[9][2], &x[9][3], &x[9][4], &x[9][5], &x[9][6], &x[9][7], &x[9][8], &x[9][9]);
	
	int i, j;
	for(i=0; i<A; i++){
		for(j=0; j<B; j++){
			cam[i][j] = "X";
		}
	}
    cam[0][0] = ".";
    cam[9][9] = ".";
	labirinto(x, 0, 0, cam);
    
	fclose(arq);    
	return 0;
}
