/* Bibliotecas */
#include <stdio.h>
#include <stdlib.h> 
#include <time.h>

/* Defines */
#define MAX_NAME 256
#define BLOCK_SIZE 4096  // 4KB
#define MAX_BLOCKS 25600 // 100MB / 4KB

/* FUNÇÕES DO SHELL*/
/* Loop principal de leitura de comandos enviados pelo usuário*/
void main_loop();

/* Estruturas de dados utilizadas */

/* Estrutura de um arquivo, pode ser arquivo regular ou diretório*/
typedef struct Arquivo{
    char nome[MAX_NAME];
    int tamanho_bytes;
    time_t tempo_criacao;
    time_t tempo_ult_mod;
    time_t tempo_ult_acess;
    struct Arquivo* filho;
    struct Arquivo* irmao;
    int ehDir;
    int root;
}Arquivo;

/* Estrutura do sistema de arquivos */
typedef struct {
    Arquivo* root;
    int fat[MAX_BLOCKS];
    int bitmap[MAX_BLOCKS];
    char* nome;
    size_t freeSpace;
}Sistema_de_arquivos;


/* FUNÇÕES PRINCIPAIS */
void printa_arvore(Arquivo* root, int prof);

/* COMANDOS DE ARQUIVO */
void monta(const char* arquivo);
void copia(const char* origem,const char* destino);
void criadir(char* diretorio);
void apagadir(char* diretorio);
void mostra(const char* arquivo);
void toca(const char* arquivo);
void apaga(const char* arquivo);
void lista(const char* diretorio);
void atualizadb();
void busca(const char* string);
void status();
void desmonta();
void sai();

/* Funções do sistema de arquivos - criar e carregar */
Sistema_de_arquivos* inicia_sistema_de_arquivos(const char* arquivo);
Sistema_de_arquivos* carrega_sistema_de_arquivos(const char* arquivo);
void salva_sistema_de_arquivos(Sistema_de_arquivos *fs, const char *arquivo);
void salva_arquivos(Arquivo* arq, FILE* file);
Arquivo* carrega_arquivos(FILE* file);

/* Funções auxiliares de diretório */
void apaga_arquivos(Arquivo* arq);

