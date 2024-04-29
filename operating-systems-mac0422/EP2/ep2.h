/* ESTRUTURAS DE DADOS */

typedef struct{
    int x;
    int y;
}Coordenadas;

/* ESTRUTURA DO CICLISTA */
typedef struct{
    int velocidade; // em m/s
    int volta;
    int colocação;
    Coordenadas posicao;
    int id;
    int d;
}Ciclista;

void* pedalando(void* args);
void init_ciclista(Ciclista *ciclista);

/* VARIÁVEL COMPARTILHADA DO VELÓDROMO */
typedef int** Velodromo; 

void init_velodromo(int d);
void print_velodromo(int d);
void free_coisas(int k);
void pegar_espaco(int k);

/* ESTRUTURA CENTRAL */
typedef struct{
    // matriz circular
    //char** velodromo;
    //int largura;
    //int comprimento;
    // relogio??
}Central;
