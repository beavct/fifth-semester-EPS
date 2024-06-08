#include <stdio.h>
#include "ep3.h"

/*Para as funções de shell*/
#include <readline/readline.h>
#include <readline/history.h>

#include <time.h> 
#include <sys/types.h> /*uid_t*/
#include <stdlib.h> /*free*/
#include <string.h> /*strtok*/

/* Variáveis globais */
Sistema_de_arquivos* fs_geral = NULL;

// arrumar essa função aqui pra printar mais bonito
void printa_arvore(Arquivo* root, int prof) {
    if (root == NULL) return;

    // Imprime a identação para a profundidade atual
    for (int i = 0; i < prof - 1; i++) {
        if (i == prof - 2) {
            printf("├── ");
        } else {
            printf("│   ");
        }
    }

    // Imprime o nome do arquivo/diretório
    if (prof > 0) {
        if (root->irmao == NULL) {
            printf("└── ");
        } else {
            printf("├── ");
        }
    }
    printf("%s%s\n", root->nome, root->ehDir && !root->root ? "/" : "");

    // Chama recursivamente para os filhos e irmãos
    printa_arvore(root->filho, prof + 1);
    printa_arvore(root->irmao, prof);
}

void salva_arquivos(Arquivo* arq, FILE* file){
    if (arq == NULL) {
        int flag_filho = 0;
        fwrite(&flag_filho, sizeof(int), 1, file);
        return;
    }

    printf("salvando %s\n", arq->nome);

    int flag_filho = 1;
    fwrite(&flag_filho, sizeof(int), 1, file);

    int nome_len = strlen(arq->nome)+1;
    fwrite(&nome_len, sizeof(int), 1, file);
    fwrite(arq->nome, sizeof(char), nome_len, file);

    fwrite(&arq->tamanho_bytes, sizeof(int), 1, file);
    fwrite(&arq->tempo_criacao, sizeof(time_t), 1, file);
    fwrite(&arq->tempo_ult_mod, sizeof(time_t), 1, file);
    fwrite(&arq->tempo_ult_acess, sizeof(time_t), 1, file);
    fwrite(&arq->ehDir, sizeof(int), 1, file);
    fwrite(&arq->root, sizeof(int), 1, file);

    // Recursivamente salva filhos e irmãos
    salva_arquivos(arq->filho, file);
    salva_arquivos(arq->irmao, file);

}

Arquivo* carrega_arquivos(FILE* file){
    int flag_filho;
    fread(&flag_filho, sizeof(int), 1, file);

    if (flag_filho == 0) {
        return NULL;
    }

    Arquivo* arq = (Arquivo*)malloc(sizeof(Arquivo));
    int nome_len;
    fread(&nome_len, sizeof(int), 1, file);
    fread(arq->nome, sizeof(char), nome_len, file);
    arq->nome[nome_len-1] = '\0';  // Garantir a terminação do nome

    fread(&arq->tamanho_bytes, sizeof(int), 1, file);
    fread(&arq->tempo_criacao, sizeof(time_t), 1, file);
    fread(&arq->tempo_ult_mod, sizeof(time_t), 1, file);
    fread(&arq->tempo_ult_acess, sizeof(time_t), 1, file);
    fread(&arq->ehDir, sizeof(int), 1, file);
    fread(&arq->root, sizeof(int), 1, file);

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
    fs->nome = (char*)malloc(strlen(arquivo) + 1);
    strcpy(fs->nome, arquivo);

    //salva_sistema_de_arquivos(fs, arquivo);

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
    
    fs->nome = (char*)malloc(strlen(arquivo) + 1);
    strcpy(fs->nome, arquivo);
    
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

    fs_geral = fs;
}

/*
testar
copia ~/Desktop/fifth-semester-EPS/operating-systems-mac0422/EP3/README /oie1

*/
void copia(const char* origem, const char* destino){
// Abrir o arquivo de origem no sistema de arquivos real
    FILE* origem_file = fopen(origem, "r");
    if (origem_file == NULL) {
        fprintf(stderr,"fopen :(\n");
        return;
    }

   // Abrir o arquivo de destino no sistema de arquivos simulado para escrita
    FILE* destino_file = fopen(destino, "wb");
    if (destino_file == NULL) {
        fprintf(stderr,"fopen :(\n");
        fclose(origem_file);
        return;
    }

    // Ler o conteúdo do arquivo de origem e escrevê-lo no arquivo de destino
    char buffer[1024];
    size_t bytes_lidos;
    while ((bytes_lidos = fread(buffer, 1, sizeof(buffer), origem_file)) > 0) {
        fwrite(buffer, 1, bytes_lidos, destino_file);
    }

    // Fechar os arquivos
    fclose(origem_file);
    fclose(destino_file);

    printf("Arquivo copiado com sucesso de %s para %s\n", origem, destino);   
}

// ta criando o diretorio, não sei se precisa salvar mais infos
void criadir(char* diretorio){
    Arquivo* cur_diretorio = fs_geral->root;

    char* path_auxiliar1 = strtok(diretorio, "/");
    char* path_auxiliar2 = strtok(NULL, "/");

    // percorre os diretórios 
    while(path_auxiliar2 != NULL){
        Arquivo* cur_auxiliar = cur_diretorio->filho;

        while(strcmp(path_auxiliar1,cur_auxiliar->nome) && cur_auxiliar != NULL){
            cur_auxiliar = cur_auxiliar->irmao;
        }

        cur_diretorio = cur_auxiliar;

        path_auxiliar1 = path_auxiliar2;
        path_auxiliar2 = strtok(NULL, "/");
    }

    Arquivo* novo_diretorio = (Arquivo*)malloc(sizeof(Arquivo));
    strcpy(novo_diretorio->nome, path_auxiliar1);
    novo_diretorio->irmao= NULL;
    novo_diretorio->filho= NULL;
    novo_diretorio->ehDir = 1;
    novo_diretorio->root = 0;
    novo_diretorio->tamanho_bytes = 0;
    novo_diretorio->tempo_criacao = time(NULL);
    novo_diretorio->tempo_ult_acess = novo_diretorio->tempo_criacao;
    novo_diretorio->tempo_ult_mod = novo_diretorio->tempo_criacao;

    // Encontrar um bloco livre no bitmap
    int bloco_livre = -1;
    for (int i = 0; i < MAX_BLOCKS; ++i) {
        if (fs_geral->bitmap[i] == 0) {
            bloco_livre = i;
            fs_geral->bitmap[i] = 1; // Marcar como usado no bitmap
            break;
        }
    }

    if (bloco_livre == -1) {
        printf("Não há blocos livres para criar o diretório :(.\n");
        free(novo_diretorio);
        return;
    }

    // Atualizar o FAT com o bloco livre
    fs_geral->fat[bloco_livre] = -1; // Como é um diretório, o valor no FAT é -1

    if(cur_diretorio->filho == NULL)
        cur_diretorio->filho = novo_diretorio;
    else{
        cur_diretorio = cur_diretorio->filho;

        while(cur_diretorio->irmao!=NULL)
            cur_diretorio = cur_diretorio->irmao;
        
        cur_diretorio->irmao = novo_diretorio;
    }

    printf("Diretório %s criado com sucesso :).\n", novo_diretorio->nome);

}

// não sei se ta atualizando o fat e bitmap de forma correta
void apaga_arquivos(Arquivo* arq) {
    if (arq == NULL) return;

    // Recursivamente apaga os filhos e irmãos
    apaga_arquivos(arq->filho);
    apaga_arquivos(arq->irmao);

    // Liberar a memória alocada para o arquivo
    free(arq);
}

// não sei se ta atualizando o fat e bitmap de forma correta
void apagadir(char* diretorio) {
    // Copiar o caminho para uma string modificável
    char* diretorio_copia = strdup(diretorio);

    // Separar o caminho em tokens
    char* path_auxiliar1 = strtok(diretorio_copia, "/");
    char* path_auxiliar2 = strtok(NULL, "/");


    // Percorre os diretórios do caminho fornecido
    // Não é possível apagar o diretório "/" 
    Arquivo* cur_diretorio = fs_geral->root->filho;

    // Ponteiro para o nó anterior enquanto percorremos a lista de irmãos
    Arquivo* anterior = fs_geral->root;

    // Flag para saber se o anterior é irmão ou pai
    int flag_parentesco = 1; // 1: pai, 2: irmao  

    while (path_auxiliar2 != NULL) {
        Arquivo* cur_auxiliar = cur_diretorio->filho;
        anterior = cur_diretorio;


        // Percorre os filhos do diretório atual para encontrar o próximo diretório no caminho
        while (cur_auxiliar != NULL && strcmp(path_auxiliar2, cur_auxiliar->nome) != 0) {
            anterior = cur_auxiliar;
            cur_auxiliar = cur_auxiliar->irmao;
        }

        // Move para o próximo diretório no caminho
        cur_diretorio = cur_auxiliar;

        // Atualiza os tokens
        path_auxiliar1 = path_auxiliar2;
        path_auxiliar2 = strtok(NULL, "/");
    }

    while(strcmp(path_auxiliar1, cur_diretorio->nome) != 0 && cur_diretorio != NULL){
        anterior = cur_diretorio;
        cur_diretorio = cur_diretorio->irmao;

        flag_parentesco = 2;
    }

    // Verificar se o diretório a ser excluído está vazio
    if (cur_diretorio->filho == NULL) {
        // Remover o diretório da lista de irmãos do diretório pai
        if (anterior == NULL) {
            // O diretório a ser excluído é o primeiro filho do diretório pai
            fs_geral->root->filho = cur_diretorio->irmao;
        } else {
            if(flag_parentesco == 1){
                anterior->filho = cur_diretorio->irmao;
            }
            else{
                anterior->irmao = cur_diretorio->irmao;
            }
        }

        printf("Diretório %s foi apagado :)\n", diretorio);
    } else {
        // Se o diretório não estiver vazio, podemos excluí-lo e todo o seu conteúdo
        // Chamada para excluir todos os arquivos e subdiretórios sob o diretório a ser excluído
        apaga_arquivos(cur_diretorio->filho);

        // Remover o diretório da lista de irmãos do diretório pai
        if (anterior == NULL) {
            // O diretório a ser excluído é o primeiro filho do diretório pai
            fs_geral->root->filho = cur_diretorio->irmao;
        } else {
            if(flag_parentesco == 1){
                anterior->filho = cur_diretorio->irmao;
            }
            else{
                anterior->irmao = cur_diretorio->irmao;
            }
        }

        // Não libere a memória para o diretório, pois isso já foi feito no loop de exclusão de arquivos

        printf("Diretório %s e todo o seu conteúdo foram apagados :)\n", diretorio);
    }

    // Liberar a memória alocada para a cópia do diretório
    free(diretorio_copia);

    // Liberar a memória alocada para o diretório
    free(cur_diretorio);
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
    salva_sistema_de_arquivos(fs_geral, fs_geral->nome);
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


        printa_arvore(fs_geral->root, 0);
    }

}

int main(){

    main_loop();

    return 0;
}