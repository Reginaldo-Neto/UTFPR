#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <time.h>
#include <stdbool.h>

// Defines
#define N_ALUNOS_SO 20
#define N_ALUNOS_DUVIDA 5
#define N_GRUPOS_DUVIDA 3

// Semaforos
sem_t sem_preparar_aula;
sem_t sem_dar_aula;
sem_t sem_atender_aluno;
sem_t sem_duvida_espera;
sem_t sem_entrar_sala;
sem_t sem_sala_espera;
sem_t sem_sair_sala;
sem_t sem_sala_vazia;
sem_t sem_sala_lotada;
sem_t sem_grupo_duvida;
sem_t sem_alunos_duvida;
sem_t sem_dispensar_aluno;
sem_t sem_dispensar_aluno_duvida;
sem_t sem_corredor_vazio;
sem_t sem_prof_livre;
// Variaveis globais
int quant_alunos_sala = 0;
int quant_alunos_duvida = 0;
int quant_grupo_duvida = 0;
int quant_alunos_atendidos = 0;
int quant_alunos_esperando_sala = 0;
int quant_oba = 0;
int cont=0;
int quant_alunos_esperando_corredor = 0;

// Instancias de funcoes
void *professor(void *arg);
void *aluno_so(void *arg);
void *aluno_duvida(void *arg);

// Funcoes
void *professor(void *arg){
    
    //Preparar Aula
    sem_post(&sem_preparar_aula);
        printf("O professor Campiolo esta preparando atividades em sua sala. \nEm breve, %d pessoas terao aula de SO com o professor Campiolo.\nAlguns alunos entram na sala e outros o esperam para tirar duvidas do lado de fora.\n\n", N_ALUNOS_SO); 
    if(cont==0){
        cont++;
    sem_post(&sem_prof_livre);
    }
    sem_wait(&sem_sala_lotada);
        printf("O professor saiu para dar aula.\n\n");
        sleep(1);

    sem_post(&sem_dar_aula);
        printf("O professor esta dando aula!\n\n"); 
        sleep(2);

    sem_post(&sem_dispensar_aluno);
        printf("\nA aula acabou!\n\n");
        sleep(1);

        // Atende alunos no patio
    sem_post(&sem_atender_aluno);
        //printf("O professor esta atendendo os alunos!\n\n"); 
        sleep(2);
    /*sem_post(&sem_dispensar_aluno_duvida);
        printf("\nA aula acabou!\n\n");
        sleep(1);    */
        
        sem_wait(&sem_corredor_vazio);

        //printf("O professor atendeu o grupo!\n\n");
        

        // Dispensar alunos
        sem_wait(&sem_sala_vazia);
        printf("O professor vai embora para casa!\n\n");
        return 0;
}

void *aluno_so(void *arg){
    int id = *(int*)arg;
    // Aluno de SO entra na sala
    sem_post(&sem_entrar_sala);
    printf("Aluno_SO_%d entrou na sala\n", id);
    quant_alunos_sala++;
    // Aluno de SO aguarda o inicio da aula
    sem_post(&sem_sala_espera);
    printf("Aluno_SO_%d esta aguardando a aula\n", id);
    quant_alunos_esperando_sala++;

    if(quant_alunos_esperando_sala == N_ALUNOS_SO){
        printf("\nA SALA ESTA CHEIA!\n\n");     
        sem_wait(&sem_prof_livre);
        sem_post(&sem_sala_lotada);
        printf("O Aluno_SO_%d foi chamar o professor.\n\n", id);
        sem_post(&sem_prof_livre);
    }
    sem_wait(&sem_dar_aula);
        printf("Oba aula de SO! %d\n", id);
        quant_oba++;
    if(quant_oba<=N_ALUNOS_SO){
        sem_post(&sem_dar_aula);
    }
    sem_wait(&sem_dispensar_aluno);
        printf("Aluno %d saiu da sala!\n", id);
        quant_alunos_sala--;
    if(quant_alunos_sala == 0){
        printf("\nSALA VAZIA!!!\n\n");
        sem_post(&sem_sala_vazia);
    } else{
        sem_post(&sem_dispensar_aluno);
    }
    //sleep(1);
    return NULL;
}

void *aluno_duvida(void *arg){
    int id = *(int*)arg;

     // Aluno com duvida chega para falar com o professor
    sem_post(&sem_alunos_duvida);
    printf("\n>>> Aluno_DUVIDA_%d chegou no corredor\n", id);
    quant_alunos_duvida++;

    sem_post(&sem_duvida_espera);
    printf("Aluno_DUVIDA_%d esta aguardando o professor\n\n", id);
    quant_alunos_esperando_corredor++;

    
    if(quant_alunos_duvida == N_ALUNOS_DUVIDA){
        printf("O grupo de duvidas lotou!\n");
        sem_wait(&sem_prof_livre);
        if(quant_alunos_esperando_sala<N_ALUNOS_SO)
        printf("O professor esta atendendo as duvidas no corredor\n\n");
        sem_post(&sem_atender_aluno);
    };
    sem_wait(&sem_atender_aluno);
        printf("Aluno_DUVIDA %d foi atendido!\n", id);
            quant_alunos_duvida--;
        if(quant_alunos_duvida == 0){
            printf("\nGRUPO ATENDIDO!!!\n\n");
            sem_post(&sem_corredor_vazio);
            sem_post(&sem_prof_livre);
            printf("\nO professor volta a preparar aulas em sua sala.\n");
        } else{
            sem_post(&sem_atender_aluno);
        }    
}

int main(){
    
    // Inicialização dos semaforos
    sem_init(&sem_preparar_aula, 0, 0);
    sem_init(&sem_atender_aluno, 0, 0);
    sem_init(&sem_duvida_espera, 0, 0);
    sem_init(&sem_entrar_sala, 0, 0);
    sem_init(&sem_sala_espera, 0, 0);
    sem_init(&sem_sair_sala, 0, 0);
    sem_init(&sem_sala_vazia, 0, 0);
    sem_init(&sem_sala_lotada, 0, 0);
    sem_init(&sem_grupo_duvida, 0, 0);
    sem_init(&sem_alunos_duvida, 0, 0);
    sem_init(&sem_corredor_vazio, 0, 0);
    sem_init(&sem_dispensar_aluno, 0, 0);
    sem_init(&sem_dispensar_aluno_duvida, 0, 0);
    sem_init(&sem_prof_livre, 0, 0);
    // Criação das threads
    pthread_t professor_thread;
    pthread_t aluno_so_thread[N_ALUNOS_SO];
    pthread_t aluno_duvida_thread[N_ALUNOS_DUVIDA];


    // Cria argumentos para as threads
    int i;
    int *id_aluno_so;
    int *id_aluno_duvida;

    //Cria as threads
    pthread_create(&professor_thread, NULL, professor, NULL);

    for(i = 1; i <= N_ALUNOS_DUVIDA; i++){
            id_aluno_duvida = malloc(sizeof(int));
            *id_aluno_duvida = i;
            pthread_create(&aluno_duvida_thread[i], NULL, aluno_duvida, (void*) id_aluno_duvida);
        }

    for(i = 1; i <= N_ALUNOS_SO; i++){
        id_aluno_so = malloc(sizeof(int));
        *id_aluno_so = i;
        pthread_create(&aluno_so_thread[i], NULL, aluno_so, (void*) id_aluno_so);
    }
    

    // Espera pelas threads
    pthread_join(professor_thread, NULL);

    for(i = 0; i < N_ALUNOS_SO; i++){
        pthread_join(aluno_so_thread[i], NULL);
    }

    for(i = 0; i < N_ALUNOS_DUVIDA; i++){
        pthread_join(aluno_duvida_thread[i], NULL);
    }

    return 0;
}