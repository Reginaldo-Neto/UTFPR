// Example program
#include <iostream>
#include <string>

class List{
    int *vetor;
    int tam;
    int quant;
    public:
        void criar(int valorMax);
        void add(int valor);
        void remove();
        int quantidade();
};

int main(){
    List *l1 = new List;
    
    l1->criar(10);
    l1->add(5);
	l1->add(15);
	l1->remove();
	l1->remove();
	
	delete (l1);
	return 0;
}

void List::criar(int valorMax){
      if(valorMax == 0){
          return;
      }
      for(int x=0; x<valorMax; x++){
	  	this->vetor[x] = 0;
	  }
      return;
}


int List::quantidade(){
	return this->quant;
}

void List::add(int valor){
	this->vetor[this->quant] = valor;
	this->quant ++;
}
void List::remove(){
	quant--;
	return;
}
