// Example program
#include <iostream>
#include <string>

class Fila{
    int *vetor;
    int tam;
    int quant;
	int fim=0;
    public:
        void criar(int valorMax);
        void add(int valor);
        void remove();
        int quantidade();
};

int main(){
    Fila *l1 = new Fila;
    
    l1->criar(10);
    l1->add(5);
	l1->add(15);
	l1->remove();
	l1->remove();
	
	delete (l1);
	return 0;
}

void Fila::criar(int valorMax){
      if(valorMax == 0){
          return;
      }
      for(int x=0; x<valorMax; x++){
	  	this->vetor[x] = 0;
	  }
      return;
}


int Fila::quantidade(){
	return this->quant;
}

void Fila::add(int valor){
	this->vetor[this->quant] = valor;
	this->quant ++;
}
void Fila::remove(){
	for(this->fim; this->fim<quant-1; this->fim++){
		this->vetor[this->fim] = this->vetor[this->fim+1];
	}
	return;
}
