
/* ESTRUTURA DE DADOS BÁSICAS */

/* Guarda as informações de cada processo (retiradas da tracefile) */
typedef struct process_info{
    /* No máx. 16 caracteres ASCII */
    char name[17];
    /* Instante de tempo até o qual o usuário gostaria que aquele processo terminasse */
    int deadline; 
    /* Instante de tempo em segundos quando o processo chega no sistema */
    int t0;
    /* Quanto de tempo real dos núcleos de processamento deve ser destinado para aquele processo */
    int dt;
    /* Instante que o processo começou a ser executado (utilizado pelo RR e esc. por prior)*/
    int t0_aux;
}process_info;

/*Estrutura de dados que guarda todos os processos*/
typedef struct {
    process_info *processes;
    int p_quant;
    int max;
}processes_info;

/* Estrutura de dados que guarda as informações de finalização de cada processo */
typedef struct {
    /* No máx. 16 caracteres ASCII */
    char name[17];
    /* Instante em que o processo terminou sua execução */
    int tf;
    /* Tempo "de relógio" que o processo levou para executar, ou seja, tf-t0 */    
    int tr;
}process_end_info;  

/* Estrutura de dados que guarda as informações que serão gravadas no arquivo de saída*/
typedef struct{
    /* Quantidade de processos */
    int quant;
    /* Informação de finalização de cada thread */
    process_end_info *processes;
}processes_end_info;

/*FUNÇÕES BÁSICAS*/

/* Realiza a leitura da tracefile */
void read_tracefile(char *name);
/* Escreve no arquivo indicado pelo usuário */
void write_file(char *name);
/*Aloca estrutura que guarda as infos iniciais de cada processo*/
void init_processes();
/* Inicializa a fila que vai ser utilizada pelo escalonador*/
void init_queue();
/* Realoca a estrutura infos iniciais de processos */
void realloc_processes();
/* Comparação dos nomes dos processos para salvar em ordem no arquivo */
int compare_str(const void* i, const void* j);

/*ESCALONADORES*/

/* Escalonador Shortest Job First */
void esc_SJF();
/* Cuida da fila do SJF */
void *queue_SJF();
/* Escalonador Round-Robin */
void esc_RR();
/* Cuida da fila do RR */
void *queue_RR();
/* Escalonador com prioridade (utiliza a deadline para definir a quant. de quantums dada a cada processo) */
void esc_prior();
/* Comparação utilizada para ordenar a fila SJF*/
int compare_SJF(const void* i, const void* j);
/* Comparação somente pelo t0, utilizada pelo RR e esc. por prior.*/
int compare_normal(const void* i, const void* j);

/* Nó da lista ligada circular */
typedef struct queue_node{
    struct queue_node *next;
    struct queue_node *ant;
    process_info *p_info;
}queue_node;   

/* Estrutura de dados lista ligada circular (utilizada pelos escalonadores) */
typedef struct {
    queue_node *queue_head;
    int q_size;    
}queue;

