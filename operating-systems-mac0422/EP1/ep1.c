#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h> /* quicksort, pode usar qsort da lib?*/
#include <string.h> /* strtok*/
#include <pthread.h>
#include <time.h> /* clock() */
#include <sched.h> /* CPU */
#include <unistd.h> /* sleep() */
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
/* Quantos processos foram finalizados */
long fin_proc=0;

void init_queue(){
    p_queue = (queue*)malloc(sizeof(queue));
    p_queue->queue_head = NULL;
    p_queue->q_size = 0;
}

int compare_SJF(const void* i, const void* j){ 
    process_info *pi = (process_info *)i;
    process_info *pj = (process_info *)j;

    if(pi->t0 > pj->t0){  
        return 1;  
    }  
    else if(pi->t0 < pj->t0){  
        return -1;  
    }
    else{
        if(pi->dt > pj->dt){
            return 1;
        }
        else if(pi->dt < pj->dt){
            return -1;
        }
    }
    return 0;      
}

void esc_SJF(){
    pthread_t threads[2];
    int t=0;
    pid_t childpid;

    init_time = time(NULL);
    
    /* Thread que cuida da fila*/
    if ((childpid = pthread_create(&threads[t], NULL, queue_SJF, NULL)) == 0) {
        t++;
    }
    else{
        fprintf(stderr,"pthread_create :(\n");
        exit(1);
    }


    /* Simula o tempo do processo */
    while(fin_proc != proc_info->p_quant){
        //printf("entrou aq3\n");
        if(p_queue->queue_head != NULL){
            long aux = p_queue->queue_head->p_info->dt;

            //printf("%s vai rodar\n", p_queue->queue_head->p_info->name);

            time_t t0 = time(NULL);
            sleep(aux);
            time_t tf = time(NULL);
            
            strcpy(proc_end_info->processes[proc_end_info->quant].name, p_queue->queue_head->p_info->name);
            proc_end_info->processes[proc_end_info->quant].tf = tf-init_time;
            proc_end_info->processes[proc_end_info->quant].tr = tf-t0;
            proc_end_info->quant++;

            fin_proc++;
            p_queue->queue_head= p_queue->queue_head->next;
            cont_chances++;

        }
    }

    /* Espera todas as threads terminarem */
    for(long i = 0; i < t; i++) {
        pthread_join(threads[i], NULL);
    }
}

void *queue_SJF(){
    for(int i=0; i<proc_info->p_quant; i++){
        /* Enquanto o tempo ainda é menor do que o t0 do processo, espera*/
        while(time(NULL) < init_time + proc_info->processes[i].t0){
            
        }

        /* Adiciona o processo na fila de processos */
        queue_node *new_node = (queue_node*)malloc(sizeof(queue_node));
        new_node->p_info = &proc_info->processes[i];
        new_node->next = NULL;

        /* Se a fila ainda não tem cabeça, então o novo processo é a cabeça*/
        if(p_queue->queue_head == NULL){
            p_queue->queue_head = new_node;
        }
        /* Se a fila já tem cabeça, então colocamos o novo processo no fim */
        else{
            queue_node *current = p_queue->queue_head;
            while(current->next != NULL){
                current = current->next;
            }
            current->next = new_node;   
        }

        /* Incrementamos o tamanho da fila */
        p_queue->q_size++;       
    }

    return NULL;
}

void esc_RR(){

}

void esc_prior(){


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

    //fprintf(fptr, "oiee\n");
    if(proc_end_info->quant==0)
        return;

    for(int i=0; i<proc_end_info->quant; i++){
        fprintf(fptr, "%s %d %d\n", proc_end_info->processes[i].name, proc_end_info->processes[i].tf, proc_end_info->processes[i].tr);
    }
    fprintf(fptr, "%ld\n", cont_chances);

    fclose(fptr);     
}

int main(int argc, char **argv){

    /* Mensagem de erro caso os argumentos não tenham sido dados da maneira correta*/
    if (argc < 3) {
        fprintf(stderr,"Uso: ./ep1 <# escalonador> <trace file> <output file>\n");
        fprintf(stderr,"Vai rodar um simulador de processos utilizando o escalonador <# escalonador> e os dados de <trace file>, os resultados serão salvos em <output file>\n");
        exit(1);
    }

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

    if(esc==1){
        /* Ordena os processos pelo t0 */
        qsort(proc_info->processes, proc_info->p_quant, sizeof(process_info), compare_SJF);
        
        esc_SJF();
    }
    else if(esc==2){
        esc_RR();
    }
    else if(esc==3){
        esc_prior();
    }

    printf("escreveu no arquivo\n");
    write_file(argv[2]);

    exit(0);
}