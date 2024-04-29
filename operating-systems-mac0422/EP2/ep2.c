#define _GNU_SOURCE 

#include <stdio.h>
#include <stdlib.h> /* malloc(), itoa(), rand() */
#include <pthread.h>
#include <semaphore.h>
#include <string.h> /* strtok() */
//#include <time.h> /* clock() */
//#include <sched.h> /* CPU */
//#include <unistd.h> /* sleep() */
#include "ep2.h"

/* VARIÁVEIS GLOBAIS */
/* Espaço na hora de printar*/
int espaco;

/* Velódromo compartilhado */
Velodromo velodromo;

/* Semáforo binário para colocar os ciclistas na pista no ínicio da simulação*/
pthread_mutex_t pos_ini_mutex;
/* Posição para o ciclista no ínicio da simulação */
Coordenadas pos_ini;

/* Ciclistas que ainda estão na pista */
int c_na_pista;

/* Semáforo para ver se pode começar a próxima volta */
sem_t *continuar_corrida;


void pegar_espaco(int k){
    espaco=0;

    while(k>0){
        k/=10;
        espaco++;
    }
    espaco+=2;
}

void init_velodromo(int d){
    velodromo = (int**)malloc(sizeof(int*)*10);

    int i;
    for(i=0; i<10; i++){
        velodromo[i]=(int*)malloc(sizeof(int)*d);

        int j;
        for(j=0; j<d; j++)
            velodromo[i][j]=0;
    }

    pos_ini.x = d-1;
    pos_ini.y = 9;
}

void print_velodromo(int d){
    int i, j;
    for(i=0; i<10; i++){
        for(j=0; j<d; j++)
            if(velodromo[i][j] == 0)
                printf("%*c",espaco, '.');
            else
                printf("%*d",espaco, velodromo[i][j]);
        printf("\n");
    }
}

void free_coisas(int k){
    int i;

    // Libera o velódromo
    for(i=0; i<10; i++)
        free(velodromo[i]);

    free(velodromo);

    // Libera o semáforo de colocar os corredores na posição inicial
    for (i=0; i<k; i++) {
        sem_destroy(&continuar_corrida[i]);
    }

    // Libera mutex da posição inicial
    pthread_mutex_destroy(&pos_ini_mutex);

}

void* pedalando(void* args){
    Ciclista *ciclista_t = (Ciclista*)args;
    
    init_ciclista(ciclista_t);

    sem_post(&continuar_corrida[ciclista_t->id-1]);

    pthread_exit(NULL);
}

// Coloca o ciclista na pista
void init_ciclista(Ciclista *ciclista){

    pthread_mutex_lock(&pos_ini_mutex);
    if(pos_ini.y<5){
        pos_ini.y=9;
        pos_ini.x = (pos_ini.x+1)%ciclista->d;
    }

    // LIDAR COM NÚMEROS MAIORES DO QUE 9 NA MATRIZ
    velodromo[pos_ini.y][pos_ini.x] = ciclista->id;
    ciclista->posicao.x = pos_ini.x;
    ciclista->posicao.y = pos_ini.y;

    pos_ini.y=(pos_ini.y-1)%10;

    pthread_mutex_unlock(&pos_ini_mutex); 

    ciclista->velocidade=30;
    ciclista->quebrou=0;
    
    if(ciclista->posicao.x<ciclista->d)
        ciclista->volta=-1;
    else
        ciclista->volta=0;
}

void rand_velocidade(Ciclista *ciclista){
    srand(time(0));

    double f = (double)rand()/RAND_MAX;

    if(ciclista->velocidade==30){
        if(f<=0.7)
            ciclista->velocidade = 60;
        else
            ciclista->velocidade = 30;
    }
    else{
        if(f<=0.5)
            ciclista->velocidade = 60;
        else
            ciclista->velocidade = 30;
    }
}

int rand_quebrar(){
    srand(time(0));

    double f = (double)rand()/RAND_MAX;

    
    if(f<=0.15)
        return 1; // quebrou
    else 
        return 0;
}

int rand_ganhador(int i){
    srand(time(0));

    int f = (rand()%i)+1;

    return f;
}

int main(int argc, char **argv){

    /* Mensagem de erro caso os argumentos não tenham sido dados da maneira correta*/
    if (argc < 3) {
        fprintf(stderr,"Uso: ./ep2 <d metros> <k ciclistas> <-debug>\n");
        fprintf(stderr,"Vai rodar um simulador de corrida por eliminação em um velódromo de <d> metros com <k> ciclistas\n");
        exit(1);
    }

    // d metros
    int d=atoi(argv[1]);
    // k ciclistas
    int k=atoi(argv[2]);

    c_na_pista=k;

    pegar_espaco(k);
    init_velodromo(d);

    continuar_corrida = (sem_t*)malloc(sizeof(sem_t)*k);

    long int t;
    for(t=0; t<k; t++){
        if (sem_init(&continuar_corrida[t], 0, 1) != 0) {
            fprintf(stderr,"sem_init :(\n");
            exit(EXIT_FAILURE);
        }        
    }

    pthread_t ciclistas[k];
    pid_t childpid;

    pthread_mutex_init(&pos_ini_mutex, NULL);

    // Cria a thread de cada ciclista
    for(t=0; t<k; t++){

        Ciclista *args = (Ciclista*)malloc(sizeof(Ciclista));

        args->id = t+1;
        args->d = d;

        if ((childpid = pthread_create(&ciclistas[t], NULL, pedalando, (void*)args)) == 0) {
        }
        else{
            fprintf(stderr,"pthread_create :(\n");
            exit(EXIT_FAILURE);
        }

    }

    for (t = 0; t < k; t++) {
        pthread_join(ciclistas[t], NULL);
    }

    for (t = 0; t < k; t++) {
        sem_wait(&continuar_corrida[t]);
        
    }
    print_velodromo(d);

    //while(c_na_pista >=2){
//
    //}




    free_coisas(k);
    

    exit(0);
}