#define _GNU_SOURCE 

#include <stdio.h>
#include <stdlib.h> /* malloc(), rand() */
#include <pthread.h>
#include <semaphore.h>
#include <string.h>
#include <unistd.h> /* time() */
#include "ep2.h"

/* VARIÁVEIS GLOBAIS */
/* Espaço na hora de printar*/
int espaco;

/* Velódromo compartilhado */
Velodromo velodromo;

/* Semáforo binário para quando for mexer nas posições*/
pthread_mutex_t mutex_pos;

/* Semáforo binário para verificar quem chegou na linha de chegada*/
pthread_mutex_t mutex_ganhador;

/* Semáforo binário para verificar a volta atual*/
pthread_mutex_t mutex_volta;

/* Posição para o ciclista no ínicio da simulação */
Coordenadas pos_ini;

/* Ciclistas que ainda estão na pista */
int c_na_pista;

/* Semáforo para a thread principal saber se os ciclistas estão prontos */
sem_t *arrive;

/* Semáforo para os ciclistas saberem se a thread principal deixou continuar */
sem_t *continue_s;

/* Volta atual */
long int volta_atual_geral=0;

/* Infos de placar etc */
Central *infos_centrais;

/* Flag de fim da corrida*/
int FIM=0;

/* Vetor de ciclistas */
pthread_t *ciclistas;

/* Vetor com as infos dos ciclistas */
Ciclista *infos_ciclistas;


void init_Central(int k){
    infos_centrais = (Central*)malloc(sizeof(Central));

    infos_centrais->placares = (placar*)malloc(sizeof(placar)*k);
    infos_centrais->quebrados = (quebrado*)malloc(sizeof(quebrado)*k);
    infos_centrais->q_quebrados=0;
    infos_centrais->q_placares=0;

}

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

    printf("\n\n");
}

void free_coisas(int k){
    int i;

    // Libera o velódromo
    for(i=0; i<10; i++)
        free(velodromo[i]);

    free(velodromo);

    free(infos_ciclistas);
    free(ciclistas);

    free(infos_centrais->placares);
    free(infos_centrais->quebrados);
    free(infos_centrais);

    // Libera o semáforo de colocar os corredores na posição inicial
    for (i=0; i<k; i++) {
        sem_destroy(&arrive[i]);
        sem_destroy(&continue_s[i]);
    }

    // Libera mutex
    pthread_mutex_destroy(&mutex_pos);
    pthread_mutex_destroy(&mutex_volta);
    pthread_mutex_destroy(&mutex_ganhador);

}

void* pedalando(void* args){
    Ciclista *ciclista_t = (Ciclista*)args;
    
    init_ciclista(ciclista_t);

    sem_post(&arrive[ciclista_t->id-1]);
    sem_wait(&continue_s[ciclista_t->id-1]);

    

    while(1){
        // corrida chegou ao fim, o ciclista está sozinho na pista
        if(FIM){
            infos_centrais->placares[infos_centrais->q_placares].id_ciclista = ciclista_t->id;
            infos_centrais->placares[infos_centrais->q_placares].instante = ciclista_t->iteracoes;
            infos_centrais->placares[infos_centrais->q_placares].posicao = infos_centrais->q_placares+1;

            infos_centrais->q_placares++;

            break;
        }

        // o ciclista passou pela linha de chegada
        int flag_volta=0;

        if((infos_centrais->q_placares>0 && infos_centrais->placares[infos_centrais->q_placares-1].volta < ciclista_t->volta) || infos_centrais->q_placares==0)
            flag_volta=1;

        if(volta_atual_geral>0 && flag_volta && ciclista_t->volta == volta_atual_geral && ciclista_t->volta%2==0 && ciclista_t->posicao.x==0){
            int aux_ganhadores = infos_centrais->q_placares;
            int ganhou=0;

            pthread_mutex_lock(&mutex_ganhador);

            if(infos_centrais->q_placares>aux_ganhadores)
                continue;
            else{
                infos_centrais->placares[infos_centrais->q_placares].id_ciclista = ciclista_t->id;
                infos_centrais->placares[infos_centrais->q_placares].posicao = infos_centrais->q_placares+1;
                infos_centrais->placares[infos_centrais->q_placares].instante = ciclista_t->iteracoes;
                infos_centrais->placares[infos_centrais->q_placares].volta = ciclista_t->volta;

                infos_centrais->q_placares++;

                velodromo[ciclista_t->posicao.y][ciclista_t->posicao.x]=0;

                ganhou=1;

                c_na_pista--;

                ciclista_t->on=0;


                // para testes
                //printf("O ciclista %d venceu!\n", ciclista_t->id);
                //printf("Volta: %d\n", ciclista_t->volta);
                //printf("No instante: %d\n", ciclista_t->iteracoes);
                //printf("%d CICLISTAS RESTANTES\n", c_na_pista);

            }

            pthread_mutex_unlock(&mutex_ganhador);           

            if(ganhou)
                break;
            
        }


        // rand pra ver se o ciclista vai quebrar
        if(ciclista_t->volta%6==0 && ciclista_t->volta>0){
            int quebrou = rand_quebrar();
            if(quebrou){
                printf(">> Ciclista %d quebrou\n", ciclista_t->id);
                //printf("ID: %d\n", ciclista_t->id);
                printf("    Volta: %d\n", ciclista_t->volta);

                pthread_mutex_lock(&mutex_pos);
                velodromo[ciclista_t->posicao.y][ciclista_t->posicao.x]=0;
                pthread_mutex_unlock(&mutex_pos);

                c_na_pista--;
                ciclista_t->on=0;

                /* Salva as informações para depois*/
                infos_centrais->quebrados[infos_centrais->q_quebrados].id_ciclista=ciclista_t->id;
                infos_centrais->quebrados[infos_centrais->q_quebrados].volta = ciclista_t->volta;
                infos_centrais->quebrados[infos_centrais->q_quebrados].instante = ciclista_t->iteracoes;

                infos_centrais->q_quebrados++;

                // para testes
                //printf("%d CICLISTAS RESTANTES\n", c_na_pista);

                break;
            }
        }

        // o ciclista ainda não fez o seu movimento
        ciclista_t->andou=0;

        // faz um rand pra ver a próxima velocidade do ciclista
        if(ciclista_t->iteracoes>0)
            rand_velocidade(ciclista_t);

        // para testes
        //printf("A velocidade do ciclista %d agora é %d\n", ciclista_t->id, ciclista_t->velocidade);


        // soma o quanto de espaço ele andou
        double aux_metros = ciclista_t->metros + (double)ciclista_t->velocidade/(double)60;


        // então o ciclista pode andar um metro
        if(aux_metros>=1){
            int pode_passar=0;
            int next_x = ciclista_t->posicao.x-1;
            if(next_x<0){
                next_x=ciclista_t->d-1;
                ciclista_t->volta++;

                // atualiza a volta atual geral
                pthread_mutex_unlock(&mutex_volta);

                if(ciclista_t->volta>volta_atual_geral){
                    volta_atual_geral=ciclista_t->volta;

                    // para testes
                    //printf("A VOLTA ATUAL É %ld setada pelo ciclista %d\n", volta_atual_geral, ciclista_t->id);
                }

                pthread_mutex_unlock(&mutex_volta);
            }

            pthread_mutex_lock(&mutex_pos);

            // vê se pode ir pra frente
            if(velodromo[ciclista_t->posicao.y][next_x]==0){

                velodromo[ciclista_t->posicao.y][ciclista_t->posicao.x]=0;
                velodromo[ciclista_t->posicao.y][next_x]=ciclista_t->id;

                ciclista_t->posicao.x = next_x;

                // para testes
                //printf("O ciclista %d conseguiu passar\n", ciclista_t->id);

                pode_passar=1;
            }

            // vê se pode ultrapassar
            else{
                for(int i=9; i>=0; i--){
                    if(velodromo[i][next_x]==0){
                        pode_passar=1;

                        velodromo[ciclista_t->posicao.y][ciclista_t->posicao.x]=0;
                        velodromo[i][next_x]=ciclista_t->id;

                        ciclista_t->posicao.x = next_x;
                        ciclista_t->posicao.y=i;

                        // para testes
                        //printf("O ciclista %d conseguiu ultrapassar\n", ciclista_t->id);

                        break;
                    }

                }
            }

            // não conseguiu ultrapassar, então fica com a velocidade da pessoa a frente dele
            if(!pode_passar){
                ciclista_t->velocidade=infos_ciclistas[velodromo[ciclista_t->posicao.y][(ciclista_t->posicao.x-1)%ciclista_t->d]].velocidade;
                
                // para testes
                //printf("O ciclista %d não conseguiu ultrapassar\n", ciclista_t->id);
            }
            else{
                // atualiza o quanto pode andar
                ciclista_t->metros=aux_metros-1;
            }
            
            pthread_mutex_unlock(&mutex_pos);

        }
        else{
            ciclista_t->metros=aux_metros;
        }
        // o ciclista já fez o seu movimento
        ciclista_t->andou=1;

        ciclista_t->iteracoes++;

        sem_post(&arrive[ciclista_t->id-1]);

        sem_wait(&continue_s[ciclista_t->id-1]);
    }

    // thread "fantasma"
    // se a corrida chegou ao fim, então a thread "fantasma" pode ser encerrada
    while(!FIM){
        sem_post(&arrive[ciclista_t->id-1]);
    }

    pthread_exit(NULL);
}

// Coloca o ciclista na pista
void init_ciclista(Ciclista *ciclista){

    pthread_mutex_lock(&mutex_pos);
    if(pos_ini.y<5){
        pos_ini.y=9;
        pos_ini.x = (pos_ini.x+1)%ciclista->d;
    }

    // LIDAR COM NÚMEROS MAIORES DO QUE 9 NA MATRIZ
    velodromo[pos_ini.y][pos_ini.x] = ciclista->id;
    ciclista->posicao.x = pos_ini.x;
    ciclista->posicao.y = pos_ini.y;

    pos_ini.y=(pos_ini.y-1)%10;

    pthread_mutex_unlock(&mutex_pos); 

    ciclista->velocidade=30;
    ciclista->quebrou=0;
    ciclista->andou=0;
    ciclista->iteracoes=0;
    ciclista->metros=0;
    ciclista->on=1;
    
    if(ciclista->posicao.x<ciclista->d-1)
        ciclista->volta=-1;
    else
        ciclista->volta=0;
}

void rand_velocidade(Ciclista *ciclista){
    srand(time(0)+ciclista->id);

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
    srand(time(0)+volta_atual_geral);

    double f = (double)rand()/RAND_MAX;

    
    if(f<=0.15)
        return 1; // quebrou
    else 
        return 0;
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
    init_Central(k);

    arrive = (sem_t*)malloc(sizeof(sem_t)*k);
    continue_s = (sem_t*)malloc(sizeof(sem_t)*k);
    infos_ciclistas = (Ciclista*)malloc(sizeof(Ciclista)*k);

    for(int t=0; t<k; t++){
        if (sem_init(&arrive[t], 0, 0) != 0) {
            fprintf(stderr,"sem_init :(\n");
            exit(EXIT_FAILURE);
        }
        if (sem_init(&continue_s[t], 0, 0) != 0) {
            fprintf(stderr,"sem_init :(\n");
            exit(EXIT_FAILURE);
        }          
    }

    ciclistas = (pthread_t*)malloc(sizeof(pthread_t)*k);
    pid_t childpid;

    pthread_mutex_init(&mutex_pos, NULL);
    pthread_mutex_init(&mutex_volta, NULL);
    pthread_mutex_init(&mutex_ganhador, NULL);


    // Cria a thread de cada ciclista
    for(int t=0; t<k; t++){

        //Ciclista *args = (Ciclista*)malloc(sizeof(Ciclista));
        Ciclista *args = &infos_ciclistas[t];

        args->id = t+1;
        args->d = d;

        if ((childpid = pthread_create(&ciclistas[t], NULL, pedalando, (void*)args)) == 0) {
        }
        else{
            fprintf(stderr,"pthread_create :(\n");
            exit(EXIT_FAILURE);
        }

    }

    int aux_volta=0;

    // loop da corrida, enquanto ainda houverem pelo menos dois ciclistas
    while(c_na_pista >=2){
        // Espera todos os ciclistas fazerem suas coisinhas e setarem arrive[i]=1
        for (int t = 0; t < k; t++) {
            sem_wait(&arrive[t]);
        }

        // tem o modo debug
        if(argc == 4 && strcmp(argv[3], "-debug") == 0){
            print_velodromo(d); 
        }

        if(volta_atual_geral>aux_volta){
            aux_volta = volta_atual_geral;
            printf(">> Volta: %ld\n", volta_atual_geral);

            for(int i=0; i<k; i++){
                if(infos_ciclistas[i].on){
                    if(infos_ciclistas[i].volta < volta_atual_geral){
                        printf("    Ciclista %d  |  Posição x: %d [RET]\n",infos_ciclistas[i].id, infos_ciclistas[i].posicao.x);
                    }
                    else{
                        printf("    Ciclista %d  |  Posição x: %d\n",infos_ciclistas[i].id, infos_ciclistas[i].posicao.x);
                    }
                }
            }

            printf("\n");
        }
        // para testes
        //sleep(2);
        //print_velodromo(d);


        // Todos fizeram suas coisinhas então podem continuar
        for (int t = 0; t < k; t++) {
            sem_post(&continue_s[t]);
        }        

    }
    // terminou a corrida
    FIM=1;
    // Para não haver deadlock e as threads de ciclistas conseguirem continuar o loop e verem que chegou ao FIM da corrida 
    for (int t = 0; t < k; t++) {
        sem_post(&continue_s[t]);
    } 

    for (int t = 0; t < k; t++) {
        pthread_join(ciclistas[t], NULL);
    }

    // FIM DA SIMULAÇÃO - printa o relatório  

    // printa o placar final
    printf("+----------------------------------------------------------------+\n\n");
    printf(">> Placar:\n\n");  

    for(int i=0; i<infos_centrais->q_placares; i++){
        printf("̣• Ciclista %d\n", infos_centrais->placares[i].id_ciclista);
        printf("    Posição: %d\n", infos_centrais->placares[i].posicao);
        printf("    Instante: %dms\n\n", infos_centrais->placares[i].instante*60);
    }

    printf("+----------------------------------------------------------------+\n\n");

    if(infos_centrais->q_quebrados>0){
        // printa as infos dos quebrados    
        printf(">> Ciclistas quebrados durante a simulação:\n\n");

        for(int i=0; i<infos_centrais->q_quebrados; i++){
            printf("̣• Ciclista %d\n", infos_centrais->quebrados[i].id_ciclista);
            printf("    Volta: %d\n", infos_centrais->quebrados[i].volta);
            printf("    Instante: %dms\n\n", infos_centrais->quebrados[i].instante*60);
        }

        printf("+----------------------------------------------------------------+\n");
    }

    free_coisas(k);

    exit(0);
}