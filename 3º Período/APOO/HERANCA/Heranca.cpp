#include <iostream>
#include <string>
#include <stdlib.h>
#include "Heranca.h"

class List{ //CLASSE PAI
    public:
        int vetor[100];
        int quant=0;
        int pos=-1;
        void add(int ele){
            pos++;
            vetor[pos]=ele;
            quant++;
        };
        void remove(int ele){
            if(pos<0){
                return;
            }
            quant--;
            int x=0, y;
            for(x; x<pos; x++){
                if(vetor[x]==ele){
                    y=x;
                    for(y; y<pos-1; y++){
                        vetor[y]=vetor[y+1];
                    }
                }
            }
            pos--;
        }
        void printa(){
            int x=0;
            for(x; x<quant; x++){
                std::cout<< "["<<vetor[x]<<"]";
            }
            std::cout<<"\n";
        }
};

class Fila : public List{
    public:
    int primeiro=-1;
    void add(int ele){
        if(primeiro==-1){
            primeiro++;
        }
            quant++;
            pos++;
            vetor[pos]=ele;
        };
    void remove(){
        if(primeiro==-1){
            return;
        }
        quant--;
        int x=primeiro;
        for(x; x<pos; x++){
            vetor[x]=vetor[x+1];
        }
        pos--;
    }
};

class Pilha : public List{
    public:
    void add(int ele){
            quant++;
            pos++;
            vetor[pos]=ele;
    };
    void remove(){
        if(pos==-1){
            return;
        }
        quant--;
        pos--;
    }
};