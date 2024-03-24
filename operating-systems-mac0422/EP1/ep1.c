#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h> /* quicksort, pode usar qsort da lib?*/
#include <string.h> /* strtok*/
#include <pthread.h>
#include <time.h> /* clock() */
#include <sched.h> /* CPU */
#include "ep1.h"

#define NUM_THREADS 1024

/* Variáveis globais */

/* Guarda as informações iniciais de cada processo */
processes_info *proc_info;
/* Guarda as informações finais de cada processo */
processes_end_info *proc_end_info;
queue *p_queue;
/* Guarda a quantidade de mudanças de contexto */
long cont_chances=0;
/* Momento em que o código começou a ser executado */
time_t init_time;

void init_queue(){
    p_queue = (queue*)malloc(sizeof(queue));
    p_queue->queue_head = NULL;
    p_queue->q_size = 0;
}

int compare_STJ(const void* i, const void* j){ 
    process_info *pi = (process_info *)i;
    process_info *pj = (process_info *)j;

    if(pi->dt > pj->dt){  
        return 1;  
    }  
    else if(pi->dt < pj->dt){  
        return -1;  
    }  
    return 0;      
}

void esc_SJF(){

}

void esc_RR(){

}

void esc_prior(){


}

time_t convertIntToTime(int seconds){
    time_t currentTime = time(NULL);
    struct tm *timeInfo = localtime(&currentTime);
    timeInfo->tm_sec += seconds;
    time_t convertedTime = mktime(timeInfo);

    return convertedTime;
}

void *single_process(void *args){
    thread_proc_args *args_aux = (thread_proc_args*)args;

    printf("oie, %s\n", args_aux->proc_info->name);

    time_t t0 = convertIntToTime(args_aux->proc_info->t0);

    while (time(NULL) < t0) {
        
    }

    printf("finalmente deu o t0, %s\n", args_aux->proc_info->name);

    if(args_aux->esc==1){
        printf("SJF, n fiz ainda :(\n");
    }
    else if(args_aux->esc==2){
        printf("RR, n fiz ainda :(\n");
    }
    else if(args_aux->esc==3){
        printf("esc. com priopridade, n fiz ainda :(\n");
    }

    return NULL;
}

void init_processes(){
    proc_info = (processes_info*)malloc(sizeof(processes_info));
    proc_info->p_quant=0;
    proc_info->max=0;   
}

void realloc_processes(){
    proc_info->max*=2;

    process_info *p_aux = (process_info*)malloc(sizeof(process_info)*proc_info->max);
    int i;

    for(i=0; i<proc_info->p_quant; i++){
        p_aux[i] = proc_info->processes[i];
    }

    proc_info->processes=p_aux;
}

void read_tracefile(char *name){
    FILE *fptr;

    fptr = fopen(name, "r");

    char myString[1024];

    proc_info->p_quant=0;
    proc_info->max=2;


    proc_info->processes = (process_info*)malloc(sizeof(process_info)*proc_info->max);

    while(fgets(myString, 1024, fptr) != NULL){
        if(proc_info->p_quant==proc_info->max){
            realloc_processes();
        }

        char *aux = strtok(myString, " ");
        /*proc_info->processes[proc_info->p_quant].name = aux;*/
        strcpy(proc_info->processes[proc_info->p_quant].name, aux);

        aux=strtok(NULL, " ");
        proc_info->processes[proc_info->p_quant].deadline = atoi(aux);

        aux=strtok(NULL, " ");
        proc_info->processes[proc_info->p_quant].t0 = atoi(aux);

        aux=strtok(NULL, " ");
        proc_info->processes[proc_info->p_quant].dt = atoi(aux);

        proc_info->p_quant++;
    }

    fclose(fptr);   

    /* Já aloca espaço para guardar as infos de finalização de cada processo */
    proc_end_info=(processes_end_info*)malloc(sizeof(processes_end_info));
    proc_end_info->processes=(process_end_info*)malloc(sizeof(process_end_info)*proc_info->p_quant);
    proc_end_info->quant=0;

    /*Para testes*/
    /*int i=0;
    printf("%d\n", proc_info->p_quant);
    for(i=0; i<proc_info->p_quant; i++){
        printf("%s %d %d %d\n", proc_info->processes[i].name, proc_info->processes[i].deadline, proc_info->processes[i].t0, proc_info->processes[i].dt);
    }*/
}

void write_file(char *name){
    FILE *fptr;

    fptr = fopen(name, "w");

    fprintf(fptr, "oiee\n");

    fclose(fptr);     
}

int main(int argc, char **argv){

    /* Mensagem de erro caso os argumentos não tenham sido dados da maneira correta*/
    if (argc < 3) {
        fprintf(stderr,"Uso: ./ep1 <# escalonador> <trace file> <output file>\n");
        fprintf(stderr,"Vai rodar um simulador de processos utilizando o escalonador <# escalonador> e os dados de <trace file>, os resultados serão salvos em <output file>\n");
        exit(1);
    }

    init_time = time(NULL);

    init_processes();
    read_tracefile(argv[1]);
    init_queue();

    int esc=atoi(argv[0]);

    /* Configs para rodar as threads no mesmo núcleo */
    cpu_set_t cpuset;
    CPU_ZERO(&cpuset);
    CPU_SET(0, &cpuset);

    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setaffinity_np(&attr, sizeof(cpu_set_t), &cpuset);

    pthread_t threads[NUM_THREADS];
    long t = 0;
    pid_t childpid;

    /* Cria uma thread para cada processo */
    for(long i=0; i<proc_info->p_quant; i++){
        thread_proc_args *args=(thread_proc_args*)malloc(sizeof(thread_proc_args));
        if(args == NULL){
            fprintf(stderr,"malloc :(\n");
            exit(1);
        }
        args->proc_info = (process_info*)malloc(sizeof(process_info));

        args->esc=esc;
        args->proc_info=&(proc_info->processes[i]);

        /* Pthread_create retorna 0 quando a thread é criada corretamente */  
        if((childpid = pthread_create(&threads[t], NULL, single_process, args)) == 0){
            /* Incrementa a quantidade de threads */
            t++;
        }      
        else{
            fprintf(stderr,"pthread_create :(\n");
        }
    }

    /* Espera todas as threads terminarem */
    for(long i = 0; i < t; i++) {
        pthread_join(threads[i], NULL);
    }

    write_file(argv[2]);

    exit(0);
}