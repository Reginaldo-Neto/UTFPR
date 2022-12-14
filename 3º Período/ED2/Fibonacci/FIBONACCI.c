#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int64_t fib_r(int n, int64_t* mem){
    int64_t resq;
    int64_t rdir;

    if(mem[n] != -1)
        return mem[n];

    resq = fib_r(n-1, mem);
    rdir = fib_r(n-2, mem);
    mem[n] = resq + rdir;
};


int64_t fib(int n){
    int64_t* mem;
    int64_t r;
    int i;

    mem = malloc(sizeof(int64_t) * (n+1));
    mem[0]=0;
    mem[1]=1;

    for(i=2; i<=n; i++){
        mem[i] =-1;
    }
    r = fib_r(n, mem);

    free(mem);
    return r;
}
int64_t fib_lenta(int n){
    if(n<=1)
        return n;
    return fib_lenta(n-1) + fib_lenta(n-2);
}

int main(int argc, char** argv){
    int n = atoi(arqv[1]);
    //printf("fib(%d) = %ld\n", n, fib_lenta(n));
    printf("fib(%d) = %ld\n", n, fib(n));
    return 0;
};
