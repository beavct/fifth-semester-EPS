
/* Guarda as informações de cada processo (retiradas da tracefile) */
typedef struct processes{
    /* No máx. 16 caracteres ASCII */
    char name[17];
    /* Instante de tempo até o qual o usuário gostaria que aquele processo terminasse */
    long long deadline; 
    /* Instante de tempo em segundos quando o processo chega no sistema */
    long long t0;
    /* Quanto de tempo real dos núcleos de processamento deve ser destinado para aquele processo */
    long long dt;
}processes;

/* Realiza a leitura da tracefile */
void read_tracefile(char *name);
/* Escreve no arquivo indicado pelo usuário */
void write_file(char *name);
/* Escalonador Shortest Job First */
void esc_SJF();
/* Escalonador Round-Robin */
void esc_RR();
/* Escalonador com prioridade (utiliza a deadline para definir a quant. de quantums dada a cada processo) */
void esc_prior();


