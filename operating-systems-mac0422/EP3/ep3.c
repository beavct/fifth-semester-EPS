#include <stdio.h>
#include "ep3.h"

/*Para as funções de shell*/
#include <readline/readline.h>
#include <readline/history.h>

#include <time.h> 
#include <sys/types.h> /*uid_t*/
#include <stdlib.h> /*free*/
#include <string.h> /*strtok*/

// arrumar essa função aqui pra printar mais bonito
void printa_arvore(Arquivo* root, int prof) {
    if (root == NULL) return;
    for (int i = 0; i < prof; i++) printf("  ");
    printf("%s%s\n", root->nome, root->ehDir ? "/" : "");
    printa_arvore(root->filho, prof + 1);
    printa_arvore(root->irmao, prof);
}

void salva_arquivos(Arquivo* arq, FILE* file){
    if (arq == NULL) {
        int flag_filho = 0;
        fwrite(&flag_filho, sizeof(int), 1, file);
        return;
    }

    int flag_filho = 1;
    fwrite(&flag_filho, sizeof(int), 1, file);

    fwrite(arq, sizeof(Arquivo), 1, file);

    // Recursively save child and sibling
    salva_arquivos(arq->filho, file);
    salva_arquivos(arq->irmao, file);
}

Arquivo* carrega_arquivos(FILE* file){
    Arquivo* arq_auxiliar;

    if(fread(&arq_auxiliar, sizeof(Arquivo), 1, file) != 1)
        return NULL;

    Arquivo *arq = (Arquivo *)malloc(sizeof(Arquivo));
    fread(arq, sizeof(Arquivo), 1, file);

    arq->filho = carrega_arquivos(file);
    arq->irmao = carrega_arquivos(file);

    return arq;
}

void salva_sistema_de_arquivos(Sistema_de_arquivos *fs, const char *arquivo){
    FILE* file = fopen(arquivo, "wb");

    if(file == NULL){
        fprintf(stderr,"fopen :(\n");
        return;
    }

    fwrite(fs->fat, sizeof(int), MAX_BLOCKS, file);
    fwrite(fs->bitmap, sizeof(int), MAX_BLOCKS, file);

    salva_arquivos(fs->root, file);
    fclose(file);
}

Sistema_de_arquivos* inicia_sistema_de_arquivos(const char* arquivo){
    Sistema_de_arquivos* fs = (Sistema_de_arquivos*)malloc(sizeof(Sistema_de_arquivos));
    
    fs->root = (Arquivo*)malloc(sizeof(Arquivo)); 
    strcpy(fs->root->nome, "/");
    fs->root->tamanho_bytes = 0;
    fs->root->tempo_criacao = time(NULL);
    fs->root->tempo_ult_acess = fs->root->tempo_criacao;
    fs->root->tempo_ult_mod = fs->root->tempo_criacao;
    fs->root->root = 1;
    fs->root->ehDir = 1;
    fs->root->irmao = NULL;
    fs->root->filho = NULL;

    for(int i=0; i<MAX_BLOCKS; i++){
        fs->fat[i] = -1;
        fs->bitmap[i] = 0;
    }

    fs->freeSpace = MAX_BLOCKS * BLOCK_SIZE;

    salva_sistema_de_arquivos(fs, arquivo);

    return fs;
}

Sistema_de_arquivos* carrega_sistema_de_arquivos(const char* arquivo){
    FILE *file;

    file = fopen(arquivo, "rb");

    if(file == NULL)
        return NULL;

    Sistema_de_arquivos *fs = (Sistema_de_arquivos*)malloc(sizeof(Sistema_de_arquivos));

    fread(fs->fat, sizeof(int), MAX_BLOCKS, file);
    fread(fs->bitmap, sizeof(int), MAX_BLOCKS, file);

    fs->root = carrega_arquivos(file);
    fclose(file);
    return fs;

}

void monta(const char* arquivo){
    Sistema_de_arquivos* fs = carrega_sistema_de_arquivos(arquivo);

    if(fs == NULL){
        fs = inicia_sistema_de_arquivos(arquivo);
        printf("Sistema de arquivos %s criado.\n", arquivo);
    }
    else
        printf("Sistema de arquivos montado a partir do arquivo %s.\n", arquivo);

    printa_arvore(fs->root, 0);
}

void copia(const char* origem, const char* destino){
    
}

void criadir(const char* diretorio){
    
}

void apagadir(const char* diretorio){
    
}

void mostra(const char* arquivo){
    
}

void toca(const char* arquivo){
    
}

void apaga(const char* arquivo){
    
}

void lista(const char* diretorio){
    
}

void atualizadb(){
    
}

void busca(const char* string){
    
}

void status(){
    
}

void desmonta(){
    
}

void sai(){
    exit(0);
}

void main_loop(){
    static char *line_read = (char *)NULL;

    /* Initialize history */
    using_history();  

    char prompt[8] = "{ep3}: ";

    while((line_read = readline(prompt))){

        add_history(line_read);

        char *firstArg = strtok(line_read, " ");

        /* Comandos internos */
        if(!strcmp(firstArg, "monta")){
            
            char* arquivo = strtok(NULL, " ");
            monta(arquivo);

        }
        else if(!strcmp(firstArg, "copia")){

            char* origem = strtok(NULL, " ");
            char* destino = strtok(NULL, " ");
            copia(origem, destino);
        
        }
        else if(!strcmp(firstArg, "criadir")){

            char* diretorio = strtok(NULL, " ");
            criadir(diretorio);

        }
        else if(!strcmp(firstArg, "apagadir")){

            char* diretorio = strtok(NULL, " ");
            apagadir(diretorio);

        }
        else if(!strcmp(firstArg, "mostra")){

            char* arquivo = strtok(NULL, " ");
            mostra(arquivo);

        }
        else if(!strcmp(firstArg, "toca")){

            char* arquivo = strtok(NULL, " ");
            toca(arquivo);
        
        }
        else if(!strcmp(firstArg, "apaga")){

            char* arquivo = strtok(NULL, " ");
            apaga(arquivo);

        }
        else if(!strcmp(firstArg, "lista")){

            char* diretorio = strtok(NULL, " ");
            lista(diretorio);

        }
        else if(!strcmp(firstArg, "atualizadb")){

            atualizadb();

        }
        else if(!strcmp(firstArg, "busca")){

            char* str = strtok(NULL, " ");
            busca(str);

        }
        else if(!strcmp(firstArg, "status")){

            status();

        }
        else if(!strcmp(firstArg, "desmonta")){

            desmonta();

        }
        else if(!strcmp(firstArg, "sai")){

            sai();

        }
        else
            printf("{ep3}: comando não encontrado: %s\n", firstArg);

        free(line_read);

    }

}

int main(){

    main_loop();

    return 0;
}