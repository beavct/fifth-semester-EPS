
/* ESTRUTURA DE DADOS BÁSICAS */

/* Guarda as informações de cada processo (retiradas da tracefile) */
typedef struct process{
    /* No máx. 16 caracteres ASCII */
    char name[17];
    /* Instante de tempo até o qual o usuário gostaria que aquele processo terminasse */
    int deadline; 
    /* Instante de tempo em segundos quando o processo chega no sistema */
    int t0;
    /* Quanto de tempo real dos núcleos de processamento deve ser destinado para aquele processo */
    int dt;
    /*Utilizado para fila, próximo*/
    struct process *next_p;
    /*Utilizado para fila, anterior*/
    struct process *ant_p;
}process;

/*Estrutura de dados que guarda todos os processos*/
typedef struct {
    process *processes;
    int p_quant;
    int max;
}processes_info;

/* Estrutura de dados que guarda as informações de finalização de cada processo */
typedef struct {
    /* No máx. 16 caracteres ASCII */
    char name[17];
    /* Instante em que o processo terminou sua execução */
    double long tf;
    /* Tempo "de relógio" que o processo levou para executar, ou seja, tf-t0 */    
    double long tr;
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
/* Realoca a estrutura infos iniciais de processos */
void realloc_processes();
/* Inicializa a fila, PRECISA DISSO ???? */
void init_queue();

/*ESCALONADORES*/

/* Escalonador Shortest Job First */
void esc_SJF();
/* Escalonador Round-Robin */
void esc_RR();
/* Escalonador com prioridade (utiliza a deadline para definir a quant. de quantums dada a cada processo) */
void esc_prior();
/* Ordena a fila do Shortest Job First PRECISA DISSO ???*/
void sort_SJF();
/* Comparação utilizada para ordenar a fila SJF*/
int compare_STJ(const void* i, const void* j);

/*AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA*/

typedef struct {
    process *queueHead;    
}queue;

/*typedef struct {
    process *queueHead;
}Round_Robin;*/
