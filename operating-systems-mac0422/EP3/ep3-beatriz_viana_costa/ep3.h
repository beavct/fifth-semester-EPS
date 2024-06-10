/* Bibliotecas */
#include <stdio.h>
#include <stdlib.h> 
#include <time.h>

/* Defines */
#define MAX_NAME 256
#define BLOCK_SIZE 4096  // 4KB
#define MAX_BLOCKS 25600 // 100MB / 4KB
#define MAX_FILE_CONTENT_SIZE 

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
    char* conteudo;
}Arquivo;

/* Estrutura do sistema de arquivos */
typedef struct {
    Arquivo* root;
    int fat[MAX_BLOCKS];
    int bitmap[MAX_BLOCKS];
    char* nome;
    size_t espaco_livre;
    size_t espaco_desperdicado;
    int quant_dir;
    int quant_arq;
}Sistema_de_arquivos;

typedef struct Banco_de_dados{
    char* nome;
    struct Banco_de_dados* filho;
    struct Banco_de_dados* irmao;
}Banco_de_dados;


/* FUNÇÕES PRINCIPAIS */
void printa_arvore(Arquivo* root, int prof, int ehUlt);

/* COMANDOS DE ARQUIVO */
void monta(const char* arquivo);
void copia(char* origem,char* destino);
void criadir(char* diretorio);
void apagadir(char* diretorio);
void mostra(char* arquivo);
void toca(char* arquivo);
void apaga(char* arquivo);
void lista(char* diretorio);
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

/* Funções auxiliares do desmonta  */
void libera_arvore(Arquivo *arq);

/* Funções auxiliares do lista */
void printa_recursivo(Arquivo *arq);

/* Funções auxiliares de banco de dados*/
void apagadb_recursivo(Banco_de_dados* bd);
Banco_de_dados* atualizadb_recursivo(Arquivo *arq);

/* Funções auxiliares da busca */
void busca_recursivo(Banco_de_dados* bd, const char* string, char* caminho_atual);

/* Função auxiliar geral*/
void libera_espaco(Arquivo* arq);

