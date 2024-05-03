/* ESTRUTURAS DE DADOS */

typedef struct{
    int x;
    int y;
}Coordenadas;

/* ESTRUTURA DO CICLISTA */
typedef struct{
    unsigned int seed;
    int velocidade; // em km/h
    int volta;
    int colocação;
    Coordenadas posicao;
    int id;
    int d;
    int quebrou; 
    int iteracoes; // quantas iterações já participou
    double metros; // quantos metros pode andar
    int on; // se o ciclista ainda está na pista
}Ciclista;

void* pedalando(void* args);
void init_ciclista(Ciclista *ciclista);
void rand_velocidade(Ciclista *ciclista);
int rand_quebrar(Ciclista *ciclista);

/* VARIÁVEL COMPARTILHADA DO VELÓDROMO */
typedef int** Velodromo; 

void init_velodromo(int d);
void print_velodromo(int d);
void free_coisas(int k);
void pegar_espaco(int k);

/* ESTRUTURA DO PLACAR */
typedef struct{
    int id_ciclista;
    int posicao;
    int instante;
    int volta;
}placar;

/* ESTRUTURA DOS QUEBRADOS */
typedef struct{
    int id_ciclista;
    int volta;
    int instante;
}quebrado;

/* ESTRUTURA CENTRAL */
typedef struct{
    placar *placares;
    int q_placares;
    quebrado *quebrados;
    int q_quebrados;
}Central;

void init_Central();
