#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <pthread.h>

#define QUANT_CADEIRAS 5
#define QUANT_MAX_CLIENTES 11

/* --- concurrency controls --- */
pthread_mutex_t mutex;
pthread_cond_t cond_barbeiro;
pthread_cond_t cond_cliente;

/* --- resource --- */
int cadeiras_ocupadas;
int cadeiras_vazias;
int clientes_atendidos;

/* --- monitor operations --- */
void initMonitor();
void destroyMonitor();
void *barbeiro(void *arg);
void *cliente(void *arg);

void initMonitor(){
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&cond_barbeiro, NULL);
    pthread_cond_init(&cond_cliente, NULL);

    cadeiras_ocupadas = 0;
    cadeiras_vazias = QUANT_CADEIRAS;
    clientes_atendidos = 0;
}

void destroyMonitor(){
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond_barbeiro);
    pthread_cond_destroy(&cond_cliente);
}

void *barbeiro(void *arg)
{
    while (true)
    {
        pthread_mutex_lock(&mutex);

        while (cadeiras_ocupadas == 0)
        {
            pthread_cond_wait(&cond_barbeiro, &mutex);
        }

        printf("Barbeiro cortando o cabelo de alguem...\n");
        sleep(1);
        cadeiras_ocupadas--;
        cadeiras_vazias++;

        pthread_mutex_unlock(&mutex);
        printf("Barbeiro terminou de cortar!\n");
    }
}

void *cliente(void *arg)
{
    pthread_mutex_lock(&mutex);
    sleep(1);

    while (cadeiras_vazias == 0)
    {
        printf("Cliente viu que a barbearia estava cheia e foi embora...\n");
        //sleep(1);
        pthread_mutex_unlock(&mutex);
        return NULL;
    }

    printf("Cliente entra na barbearia\n");
    //sleep(1);
    cadeiras_ocupadas++;
    cadeiras_vazias--;
    pthread_cond_signal(&cond_barbeiro);

    pthread_mutex_unlock(&mutex);

    return NULL;
}

int main(int argc, char const *argv[]){
    // Variaveis de inicialização
    pthread_t barbeiro_t;
    pthread_t clientes_t[QUANT_MAX_CLIENTES];

    // Inicialização do monitor
    initMonitor();

    // Criação das threads
    pthread_create(&barbeiro_t, NULL, barbeiro, NULL);
    int i;
    for (i = 0; i < QUANT_MAX_CLIENTES; i++)
    {
        pthread_create(&clientes_t[i], NULL, cliente, NULL);
    }

    // Espera das threads
    pthread_join(barbeiro_t, NULL);

    for (i = 0; i < QUANT_MAX_CLIENTES; i++)
    {
        pthread_join(clientes_t[i], NULL);
    }

    // Destruição das threads
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond_barbeiro);
    pthread_cond_destroy(&cond_cliente);

    return 0;
}