#include <iostream>
#include <string>
#include <stdlib.h>
#include "Heranca.cpp"

int main(){
    List *l1 = new List;
    Fila *f1 = new Fila;
    Pilha *p1 = new Pilha;
   
    l1->add(5);
	l1->add(10);
    f1->add(15);
	f1->add(20);
    p1->add(25);
	p1->add(30);


	//l1->remove(5);
	//f1->remove();
    //p1->remove();
	
    l1->printa();
    f1->printa();
    p1->printa();

	delete (l1);
    delete (f1);
    delete (p1);
	return 0;
};