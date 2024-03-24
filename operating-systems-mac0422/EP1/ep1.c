#include <stdio.h>
#include <stdlib.h> /* quicksort, pode usar qsort da lib?*/
#include <string.h> /* strtok*/
#include <pthread.h>
#include "ep1.h"

/* Variáveis globais */
processes_info *proc_info;
processes_end_info *proc_end_info;
queue *p_queue;

/* PRECISA DESSA MERDA AQ ? */
void init_queue(){
    p_queue = (queue*)malloc(sizeof(queue));
    p_queue->queueHead = &proc_info->processes[0];
}

int compare_STJ(const void* i, const void* j){ 
    process *pi = (process *)i;
    process *pj = (process *)j;

    if(pi->dt > pj->dt){  
        return 1;  
    }  
    else if(pi->dt < pj->dt){  
        return -1;  
    }  
    return 0;      
}

void sort_SJF(){

    /* Quicksort*/
    qsort(proc_info->processes, proc_info->p_quant, sizeof(process), compare_STJ);
    p_queue->queueHead=&proc_info->processes[0];

    int i;
    for(i=0; i<proc_info->p_quant-1; i++){
        proc_info->processes[i].next_p = &proc_info->processes[i+1];
    }

    /* Teste*/
    printf("%d\n", proc_info->p_quant);
    struct process *aux=p_queue->queueHead; 
    while(aux!=NULL){
        printf("%s %d %d %d\n", aux->name, aux->deadline, aux->t0, aux->dt);
        aux=aux->next_p;
    }
}

void esc_SJF(){

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

    process *p_aux = (process*)malloc(sizeof(process)*proc_info->max);
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


    proc_info->processes = (process*)malloc(sizeof(process)*proc_info->max);

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

        /*Ponteiros que vão utilizanos na fila*/
        proc_info->processes[proc_info->p_quant].next_p = NULL;
        proc_info->processes[proc_info->p_quant].ant_p = NULL;

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

    init_processes();
    read_tracefile(argv[1]);
    init_queue();

    int esc=atoi(argv[0]);
    if(esc==1){
        sort_SJF();

    }
    else if(esc==2){
        printf("RR, n fiz ainda :(\n");
    }
    else if(esc==3){
        printf("esc. com priopridade, n fiz ainda :(\n");
    }

    write_file(argv[2]);

    return 0;
}