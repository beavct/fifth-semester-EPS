#define _GNU_SOURCE 

#include <stdio.h>
#include <stdlib.h> /* qsort() */
#include <string.h> /* strtok() */
#include <pthread.h>
#include <time.h> /* clock() */
#include <sched.h> /* CPU */
#include <unistd.h> /* sleep() */
#include "ep1.h"

/* Quantum do Round-Robin */
#define q_RR 3
/* Quantum do Escalonamento por prioridade */
#define q_prior 3

/* Variáveis globais */

/* Guarda as informações iniciais de cada processo */
processes_info *proc_info;
/* Guarda as informações finais de cada processo */
processes_end_info *proc_end_info;
/* Fila utilizada pelo escalonador*/
queue *p_queue;
/* Guarda a quantidade de mudanças de contexto */
long cont_chances=0;
/* Momento em que o código começou a ser executado */
time_t init_time;
/* Quantos processos foram finalizados */
int fin_proc=0;
/* Mutex */
pthread_mutex_t mutex;
/* Afinidade de CPU */
cpu_set_t cpuset;


void init_queue(){
    p_queue = (queue*)malloc(sizeof(queue));
    p_queue->queue_head = NULL;
    p_queue->q_size = 0;
}

int compare_str(const void* i, const void* j){ 
    process_end_info *pi = (process_end_info *)i;
    process_end_info *pj = (process_end_info *)j;

    return strcmp(pi->name, pj->name);
}

int compare_normal(const void* i, const void* j){ 
    process_info *pi = (process_info *)i;
    process_info *pj = (process_info *)j;

    if(pi->t0 > pj->t0){  
        return 1;  
    }  
    else if(pi->t0 < pj->t0){  
        return -1;  
    }
    return 0;      
}

void esc_SJF(){
    pthread_t threads[2];
    int t=0;
    pid_t childpid;

    pthread_mutex_init(&mutex, NULL);
    init_time = time(NULL);

    /* Thread que cuida da fila*/
    if ((childpid = pthread_create(&threads[t], NULL, queue_SJF, NULL)) == 0) {
        t++;
    }
    else{
        fprintf(stderr,"pthread_create :(\n");
        exit(1);
    }
    /* Seta a thread para rodar somente na CPU indicada */
    if(pthread_setaffinity_np(threads[0], sizeof(cpu_set_t), &cpuset)){
        fprintf(stderr,"pthread_setaffinity_np :(\n");
        exit(1);
    }


    /* Simula o tempo do processo */
    while(fin_proc != proc_info->p_quant){
        if(p_queue->queue_head != NULL){
            long aux = p_queue->queue_head->p_info->dt;

            time_t t0 = time(NULL);
            sleep(aux);
            time_t tf = time(NULL);

            strcpy(proc_end_info->processes[proc_end_info->quant].name, p_queue->queue_head->p_info->name);
            proc_end_info->processes[proc_end_info->quant].tf = tf-init_time;
            proc_end_info->processes[proc_end_info->quant].tr = tf-t0;
            proc_end_info->quant++;

            fin_proc++;

            pthread_mutex_lock(&mutex);
             
            p_queue->queue_head= p_queue->queue_head->next;

            pthread_mutex_unlock(&mutex);

            cont_chances++;
        }
    }
    cont_chances--;

    /* Espera todas as threads terminarem */
    pthread_join(threads[0], NULL);
}

void *queue_SJF(){
    pthread_t SJF_threads[proc_info->p_quant]; 
    pid_t childpid;

    for(int i=0; i<proc_info->p_quant; i++){
        /* Thread que cuida da inserção de cada processo individualmente */
        if ((childpid = pthread_create(&SJF_threads[i], NULL, SJF_thread, (void *)&proc_info->processes[i])) == 1) {
            fprintf(stderr,"pthread_create :(\n");
            exit(1);
        }
        /* Seta a thread para rodar somente na CPU indicada */
        if(pthread_setaffinity_np(SJF_threads[i], sizeof(cpu_set_t), &cpuset)){
            fprintf(stderr,"pthread_setaffinity_np :(\n");
            exit(1);
        }        

    }
    for(int i=0; i<proc_info->p_quant; i++){
        pthread_join(SJF_threads[i], NULL);
    }

    return NULL;
}

void *SJF_thread(void *proc){
    process_info *aux = (process_info *)proc;


    /* Enquanto o tempo ainda é menor do que o t0 do processo, espera*/
    while(time(NULL) < init_time + aux->t0){
        
    }

    /* Adiciona o processo na fila de processos */
    queue_node *new_node = (queue_node*)malloc(sizeof(queue_node));
    new_node->p_info = aux;
    new_node->next = NULL;
    new_node->ant = NULL;

    /* Se a fila ainda não tem cabeça, então o novo processo é a cabeça*/
    if(p_queue->queue_head == NULL){
        p_queue->queue_head = new_node;
    }
    /* Se a fila já tem cabeça, então colocamos o novo processo no fim */
    else{
        pthread_mutex_lock(&mutex);

        queue_node *current = p_queue->queue_head;
        while(current->next != NULL){
            if(current->next->p_info->dt > new_node->p_info->dt)
                break;

            current = current->next;
        }
        new_node->next = current->next;
        current->next = new_node;  

        pthread_mutex_unlock(&mutex);

    }
    /* Incrementamos o tamanho da fila */
    p_queue->q_size++;  

    return NULL;
}

void esc_RR(){
    pthread_t threads[2];
    int t=0;
    pid_t childpid;

    pthread_mutex_init(&mutex, NULL);
    init_time = time(NULL);

    /* Thread que cuida da fila*/
    if ((childpid = pthread_create(&threads[t], NULL, queue_RR, NULL)) == 0) {
        t++;
    }
    else{
        fprintf(stderr,"pthread_create :(\n");
        exit(1);
    }
    /* Seta a thread para rodar somente na CPU indicada */
    if(pthread_setaffinity_np(threads[(long)0], sizeof(cpu_set_t), &cpuset)){
        fprintf(stderr,"pthread_setaffinity_np :(\n");
        exit(1);
    }

    /* Simula o tempo do processo */
    while(fin_proc != proc_info->p_quant){

        if(p_queue->queue_head != NULL){
            long aux_dt = p_queue->queue_head->p_info->dt;

            time_t t0 = time(NULL);

            int t_aux;

            if(aux_dt < q_RR)
                t_aux=aux_dt;
            else 
                t_aux = q_RR;

            sleep(t_aux);
            time_t tf = time(NULL);


            /* Se o processo foi executado pela primeira vez, salvamos o t0 em que começou*/
            if(p_queue->queue_head->p_info->t0_aux==-1)
                p_queue->queue_head->p_info->t0_aux=t0;

            /* Atualizamos quanto tempo falta para o processo terminar */
            p_queue->queue_head->p_info->dt -= t_aux;

            cont_chances++;    
        
            /* Se o processo terminou, salvamos suas informações no arquivo de saída e o tiramos da fila*/
            if(p_queue->queue_head->p_info->dt == 0){
                /* Salvando as informações no arquivo */
                strcpy(proc_end_info->processes[proc_end_info->quant].name, p_queue->queue_head->p_info->name);
                proc_end_info->processes[proc_end_info->quant].tf = tf-init_time;
                proc_end_info->processes[proc_end_info->quant].tr = tf-p_queue->queue_head->p_info->t0_aux;
                proc_end_info->quant++;

                fin_proc++;

                pthread_mutex_lock(&mutex);

                /* Removendo o processo da fila ligada */
                if(p_queue->q_size == 1){
                    p_queue->queue_head = NULL;
                }
                else{
                    queue_node *q_aux1 = p_queue->queue_head->ant;
                    queue_node *q_aux2 = p_queue->queue_head->next;

                    q_aux1->next = q_aux2;
                    q_aux2->ant = q_aux1;

                }

                p_queue->q_size--;

                pthread_mutex_unlock(&mutex);

            }

            pthread_mutex_lock(&mutex);

            queue_node *node_aux = p_queue->queue_head;
            
            if(node_aux!=NULL){
                p_queue->queue_head= p_queue->queue_head->next;
            }

            pthread_mutex_unlock(&mutex);
        }
    }
    cont_chances--;

    /* Espera todas as threads terminarem */
    pthread_join(threads[0], NULL);
}

void *queue_RR(){
    pthread_t RR_threads[proc_info->p_quant]; 
    pid_t childpid;

    for(int i=0; i<proc_info->p_quant; i++){

        /* Thread que cuida da inserção de cada processo individualmente */
        if ((childpid = pthread_create(&RR_threads[i], NULL, RR_thread, (void *)&proc_info->processes[i])) == 1) {
            fprintf(stderr,"pthread_create :(\n");
            exit(1);
        }
        /* Seta a thread para rodar somente na CPU indicada */
        if(pthread_setaffinity_np(RR_threads[i], sizeof(cpu_set_t), &cpuset)){
            fprintf(stderr,"pthread_setaffinity_np :(\n");
            exit(1);
        }        

    }
    for(int i=0; i<proc_info->p_quant; i++){
        pthread_join(RR_threads[i], NULL);
    }
  

    return NULL;
}

void *RR_thread(void *proc){
    process_info *aux = (process_info *)proc;

    /* Enquanto o tempo ainda é menor do que o t0 do processo, espera*/
    while(time(NULL) < init_time + aux->t0){
        
    }

    /* Adiciona o processo na fila de processos */
    queue_node *new_node = (queue_node*)malloc(sizeof(queue_node));
    new_node->p_info = aux;
    new_node->next = NULL;
    new_node->ant = NULL;

    pthread_mutex_lock(&mutex);

    /* Se a fila ainda não tem cabeça, então o novo processo é a cabeça*/
    if(p_queue->queue_head == NULL){
        p_queue->queue_head = new_node;
        p_queue->queue_head->ant = new_node;
        p_queue->queue_head->next = new_node;
    }
    /* Se a fila já tem cabeça, então colocamos o novo processo no fim */
    else{
        queue_node *head = p_queue->queue_head;
        queue_node *head_ant = head->ant;

        head_ant->next = new_node;
        new_node->ant = head_ant;
        head->ant = new_node;
        new_node->next = head;
    }

    /* Incrementamos o tamanho da fila */
    p_queue->q_size++;   

    pthread_mutex_unlock(&mutex);    
    
    return NULL;
}

void esc_prior(){
    pthread_t threads[2];
    int t=0;
    pid_t childpid;

    pthread_mutex_init(&mutex, NULL);
    init_time = time(NULL);

    /* Thread que cuida da fila*/
    if ((childpid = pthread_create(&threads[t], NULL, queue_prior, NULL)) == 0) {
        t++;
    }
    else{
        fprintf(stderr,"pthread_create :(\n");
        exit(1);
    }
    /* Seta a thread para rodar somente na CPU indicada */
    if(pthread_setaffinity_np(threads[(long)0], sizeof(cpu_set_t), &cpuset)){
        fprintf(stderr,"pthread_setaffinity_np :(\n");
        exit(1);
    }

    /* Simula o tempo do processo */
    while(fin_proc != proc_info->p_quant){

        if(p_queue->queue_head != NULL){
            long aux_dt = p_queue->queue_head->p_info->dt;

            time_t t0 = time(NULL);

            int t_aux;

            if(aux_dt < q_prior)
                t_aux=aux_dt;
            else 
                t_aux = q_prior;

            sleep(t_aux);
            time_t tf = time(NULL);

            /* Se o processo foi executado pela primeira vez, salvamos o t0 em que começou*/
            if(p_queue->queue_head->p_info->t0_aux==-1)
                p_queue->queue_head->p_info->t0_aux=t0;

            /* Atualizamos quanto tempo falta para o processo terminar */
            p_queue->queue_head->p_info->dt -= t_aux;
            
            cont_chances++;  

            pthread_mutex_lock(&mutex);

            /* Se o processo terminou, salvamos suas informações no arquivo de saída e o tiramos da fila*/
            if(p_queue->queue_head->p_info->dt == 0){
                /* Salvando as informações no arquivo */
                strcpy(proc_end_info->processes[proc_end_info->quant].name, p_queue->queue_head->p_info->name);
                proc_end_info->processes[proc_end_info->quant].tf = tf-init_time;
                proc_end_info->processes[proc_end_info->quant].tr = tf-p_queue->queue_head->p_info->t0_aux;
                proc_end_info->quant++;

                fin_proc++;

                /* Removendo o processo da fila ligada */
                if(p_queue->q_size == 1){
                    p_queue->queue_head = NULL;
                }
                else{
                    queue_node *q_aux1 = p_queue->queue_head->ant;
                    queue_node *q_aux2 = p_queue->queue_head->next;

                    q_aux1->next = q_aux2;
                    q_aux2->ant = q_aux1;

                    /* Atualiza a cabeça da lista */
                    p_queue->queue_head=q_aux2;

                }

                p_queue->q_size--;


            }
            /* Se o processo não terminou, precisa atualizar a prioridade e arrumar a fila*/
            else{

                /* Atualiza as prioridades de todos os processos e depois os ordena */
                queue_node *aux = p_queue->queue_head;
                int flag=1;

                while(aux!=p_queue->queue_head || flag){
                    aux->p_info->prior = calc_prior(aux->p_info->deadline);
                    flag=0;
                    aux=aux->next;
                }
                sort_prior();
            }
            
            pthread_mutex_unlock(&mutex);

            /*pthread_mutex_lock(&mutex);
            printf("TESTE1\n");
            queue_node *aux = p_queue->queue_head;
            int flag=1;

            while(aux != p_queue->queue_head || flag){
                printf("%s   %d | ", aux->p_info->name, aux->p_info->prior);
                aux=aux->next;
                flag=0;
            }
            printf("\n\n");

            pthread_mutex_unlock(&mutex);*/
        }
    }
    cont_chances--;

    /* Espera todas as threads terminarem */
    pthread_join(threads[0], NULL);    
}

void sort_prior() {
    queue_node *current = p_queue->queue_head;
    queue_node *index = NULL;

    if(p_queue->queue_head == NULL)
        return;

    while(current->next != p_queue->queue_head){
        index = current->next;
        while(p_queue->queue_head != index){
            if(current->p_info->prior > index->p_info->prior){
                process_info *aux = current->p_info;
                current->p_info = index->p_info;
                index->p_info = aux;
            }
            index=index->next;
        }

        current=current->next;
    }
}

void *queue_prior(){
    pthread_t prior_threads[proc_info->p_quant]; 
    pid_t childpid;

    for(int i=0; i<proc_info->p_quant; i++){

        /* Thread que cuida da inserção de cada processo individualmente */
        if ((childpid = pthread_create(&prior_threads[i], NULL, prior_thread, (void *)&proc_info->processes[i])) == 1) {
            fprintf(stderr,"pthread_create :(\n");
            exit(1);
        }
        /* Seta a thread para rodar somente na CPU indicada */
        if(pthread_setaffinity_np(prior_threads[i], sizeof(cpu_set_t), &cpuset)){
            fprintf(stderr,"pthread_setaffinity_np :(\n");
            exit(1);
        }        

    }
    for(int i=0; i<proc_info->p_quant; i++){
        pthread_join(prior_threads[i], NULL);

    }    

    return NULL;
}

void *prior_thread(void *proc){
    process_info *aux = (process_info *)proc;

    /* Enquanto o tempo ainda é menor do que o t0 do processo, espera*/
    while(time(NULL) < init_time + aux->t0){
        
    }

    /* Adiciona o processo na fila de processos */
    queue_node *new_node = (queue_node*)malloc(sizeof(queue_node));
    new_node->p_info = aux;
    new_node->next = NULL;
    new_node->ant = NULL;
    new_node->p_info->prior = calc_prior(aux->deadline);

    pthread_mutex_lock(&mutex);

    /* Se a fila ainda não tem cabeça, então o novo processo é a cabeça*/
    if(p_queue->queue_head == NULL){
        p_queue->queue_head = new_node;
        p_queue->queue_head->ant = new_node;
        p_queue->queue_head->next = new_node;
    }
    /* Se a fila já tem cabeça, então colocamos o novo processo no fim */
    else{
        queue_node *head = p_queue->queue_head;
        queue_node *current = p_queue->queue_head;

        /* Maior prioridade: -20, menor prioridade: +19*/
        while(current->next != head && current->next != NULL && current->next->p_info->prior <= new_node->p_info->prior){
            current=current->next;
        }

        queue_node *aux = current->next;
        current->next = new_node;
        new_node->ant = current;
        new_node->next = aux;
        aux->ant = new_node;

    }

    /* Incrementamos o tamanho da fila */
    p_queue->q_size++;   

    pthread_mutex_unlock(&mutex);   

    return NULL;
}

int calc_prior(int deadline){
    int prior;

    /* O quão "atrasado" está um processo */
    prior = (deadline - (time(NULL)-init_time));

    if(prior>19)    
        return 19;
    else if(prior< -20)
        return -20;

    return prior;
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

        /* Inicializa t0_aux com -1 */
        proc_info->processes[proc_info->p_quant].t0_aux = -1;
        /* Inicializa a prioridade com 0 */
        proc_info->processes[proc_info->p_quant].prior = 0;

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

    if(proc_end_info->quant==0)
        return;

    qsort(proc_end_info->processes, proc_end_info->quant, sizeof(process_end_info), compare_str);

    for(int i=0; i<proc_end_info->quant; i++){
        fprintf(fptr, "%s %d %d\n", proc_end_info->processes[i].name, proc_end_info->processes[i].tf, proc_end_info->processes[i].tr);
    }
    fprintf(fptr, "%ld\n", cont_chances);

    fclose(fptr);     

    /* Para testes */
    /*int atrasados = 0;
    int aux;

    fptr = fopen("resultados.txt", "w");

    for(int i=0; i<proc_end_info->quant; i++){
        fprintf(fptr, "%s ", proc_end_info->processes[i].name);
        aux =  proc_end_info->processes[i].tf - proc_info->processes[i].deadline;
        fprintf(fptr, "%d\n", aux);
        if(aux>0)
            atrasados++;
    }
    fprintf(fptr,"%d\n", atrasados);

    fclose(fptr);*/
}

int main(int argc, char **argv){

    /* Mensagem de erro caso os argumentos não tenham sido dados da maneira correta*/
    if (argc < 4) {
        fprintf(stderr,"Uso: ./ep1 <# escalonador> <trace file> <output file>\n");
        fprintf(stderr,"Vai rodar um simulador de processos utilizando o escalonador <# escalonador> e os dados de <trace file>, os resultados serão salvos em <output file>\n");
        exit(1);
    }

    init_processes();
    read_tracefile(argv[2]);
    init_queue();

    int esc=atoi(argv[1]);

    /* Configs para rodar as threads no mesmo núcleo */
    CPU_ZERO(&cpuset);
    CPU_SET(0, &cpuset);

    /* Ordena os processos pelo t0*/
    qsort(proc_info->processes, proc_info->p_quant, sizeof(process_info), compare_normal);

    if(esc==1){
        esc_SJF();
    }
    else if(esc==2){
        esc_RR();
    }
    else if(esc==3){
        esc_prior();
    }

    write_file(argv[3]);

    free(proc_info->processes);
    free(proc_info);
    free(proc_end_info->processes);
    free(proc_end_info);
    free(p_queue);

    exit(0);
}